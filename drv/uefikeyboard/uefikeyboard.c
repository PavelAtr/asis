#include "../../config.h"
#include "../../core/uefi/uefi.h"
#include "uefikeyboard.h"
#include "linux/input.h"
#include "../../userspace/alibc/include/errno.h"
#undef errno


#ifndef BOOLEAN
#define BOOLEAN unsigned char
#endif

// Минимальное сопоставление UEFI ScanCode -> Linux KEY_*
// Linux keycodes для латиницы и цифр
#define KEY_A 30
#define KEY_B 48
#define KEY_C 46
#define KEY_D 32
#define KEY_E 18
#define KEY_F 33
#define KEY_G 34
#define KEY_H 35
#define KEY_I 23
#define KEY_J 36
#define KEY_K 37
#define KEY_L 38
#define KEY_M 50
#define KEY_N 49
#define KEY_O 24
#define KEY_P 25
#define KEY_Q 16
#define KEY_R 19
#define KEY_S 31
#define KEY_T 20
#define KEY_U 22
#define KEY_V 47
#define KEY_W 17
#define KEY_X 45
#define KEY_Y 21
#define KEY_Z 44

#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_0 11

typedef struct {
    efi_status_t (*Reset)(void *This, BOOLEAN ExtendedVerification);
    efi_status_t (*ReadKeyStroke)(void *This, efi_input_key_t *Key);
    void *WaitForKey;
} efi_simple_text_input_protocol_t;

static  efi_simple_text_input_protocol_t *kbd_proto = NULL;

// Пример простой таблицы сопоставления (расширьте по необходимости)
static int uefi_scancode_to_keycode(short scan) {
    switch (scan) {
        case 0x1E: return KEY_A;
        case 0x30: return KEY_B;
        case 0x2E: return KEY_C;
        case 0x20: return KEY_D;
        case 0x12: return KEY_E;
        case 0x21: return KEY_F;
        case 0x22: return KEY_G;
        case 0x23: return KEY_H;
        case 0x17: return KEY_I;
        case 0x24: return KEY_J;
        case 0x25: return KEY_K;
        case 0x26: return KEY_L;
        case 0x32: return KEY_M;
        case 0x31: return KEY_N;
        case 0x18: return KEY_O;
        case 0x19: return KEY_P;
        case 0x10: return KEY_Q;
        case 0x13: return KEY_R;
        case 0x1F: return KEY_S;
        case 0x14: return KEY_T;
        case 0x16: return KEY_U;
        case 0x2F: return KEY_V;
        case 0x11: return KEY_W;
        case 0x2D: return KEY_X;
        case 0x15: return KEY_Y;
        case 0x2C: return KEY_Z;

        case 0x02: return KEY_1;
        case 0x03: return KEY_2;
        case 0x04: return KEY_3;
        case 0x05: return KEY_4;
        case 0x06: return KEY_5;
        case 0x07: return KEY_6;
        case 0x08: return KEY_7;
        case 0x09: return KEY_8;
        case 0x0A: return KEY_9;
        case 0x0B: return KEY_0;
        default: return 0;
    }
}

efi_guid_t gEfiSimpleTextInProtocolGuid = { 0x387477c1, 0x69c7, 0x11d2,
    { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }
};

int kbd_evdev_init(void) {
    efi_status_t status = BS->LocateProtocol(
        &gEfiSimpleTextInProtocolGuid,
        NULL,
        (void**)&kbd_proto
    );
    return EFI_ERROR(status) ? -1 : 0;
}


len_t uefikbd_read(void* devsb, void* buf, len_t count)
{
    if (!kbd_proto || count < sizeof(struct input_event)) return -1;

    efi_input_key_t key;
    efi_status_t status;

    // Ждём появления события клавиатуры (блокирующий режим)
    while (1) {
        status = kbd_proto->ReadKeyStroke(kbd_proto, &key);
        if (!EFI_ERROR(status)) break;
        BS->Stall(10000); // 10 мс
    }

/*    struct timeval tv;
    gettimeofday(&tv, NULL); */
    struct timeval tv = {0, 0}; // если нет gettimeofday

    struct input_event ev[3];
    int n = 0;

    int keycode = uefi_scancode_to_keycode(key.ScanCode);
    if (keycode) {
        // Нажатие клавиши
        ev[n++] = (struct input_event){tv, EV_KEY, keycode, 1};
        // Отпускание клавиши (эмулируем сразу после нажатия)
        ev[n++] = (struct input_event){tv, EV_KEY, keycode, 0};
    }

    // Синхронизация
    ev[n++] = (struct input_event){tv, EV_SYN, 0, 0};

    size_t bytes = n * sizeof(struct input_event);
    if (bytes > count) bytes = count;
    memcpy(buf, ev, bytes);

    return bytes;
}

len_t uefikbd_write(void* devsb, const void* ptr, len_t size)
{
   return 0;
}

void uefikbd_seek(void* devsb, len_t offset)
{
}

errno_t uefikbd_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4)
{
   return ENOTSUP;
}
