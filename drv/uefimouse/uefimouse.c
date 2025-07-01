#include "../../config.h"
#include "../../core/uefi/uefi.h"
#include "uefimouse.h"
#include "linux/input.h"

static  efi_simple_pointer_protocol_t *mouse_proto = NULL;

efi_guid_t gEfiSimplePointerProtocolGuid = { 0x31878c87, 0xb75, 0x11d5,
    { 0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d }
};

int mouse_evdev_init(void) {
    efi_status_t status = BS->LocateProtocol(
        &gEfiSimplePointerProtocolGuid,
        NULL,
        (void**)&mouse_proto
    );
    return EFI_ERROR(status) ? -1 : 0;
}



len_t uefimouse_read(void* devsb, void* buf, len_t count)
{
    if (!mouse_proto || count < sizeof(struct input_event)) return -1;

    efi_simple_pointer_state_t state;
    efi_status_t status;

    // Ждём появления события мыши (блокирующий режим)
    while (1) {
        status = mouse_proto->GetState(mouse_proto, &state);
        if (!EFI_ERROR(status)) break;
        BS->Stall(10000); // 10 мс
    }

/*    struct timeval tv;
    gettimeofday(&tv, NULL); */
    struct timeval tv = {0, 0}; // если нет gettimeofday

    struct input_event ev[6];
    int n = 0;

    if (state.RelativeMovementX)
        ev[n++] = (struct input_event){tv, EV_REL, REL_X, (int32_t)state.RelativeMovementX};
    if (state.RelativeMovementY)
        ev[n++] = (struct input_event){tv, EV_REL, REL_Y, (int32_t)state.RelativeMovementY};

    ev[n++] = (struct input_event){tv, EV_KEY, BTN_LEFT, state.LeftButton ? 1 : 0};
    ev[n++] = (struct input_event){tv, EV_KEY, BTN_RIGHT, state.RightButton ? 1 : 0};
    ev[n++] = (struct input_event){tv, EV_KEY, BTN_MIDDLE, 0};

    ev[n++] = (struct input_event){tv, EV_SYN, 0, 0};

    size_t bytes = n * sizeof(struct input_event);
    if (bytes > count) bytes = count;
    memcpy(buf, ev, bytes);

    return bytes;
}

len_t uefimouse_write(void* devsb, const void* ptr, len_t size)
{
   return 0;
}

void uefimouse_seek(void* devsb, len_t offset)
{
}

errno_t uefimouse_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4)
{
   return 7;
}
