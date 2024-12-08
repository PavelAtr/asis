#include "../../core/uefi/uefi.h"
#include "../../core/include/sys/types.h"
#include "fbgop.h"



int_t fbgop_init(fbgop* devparams)
{
  efi_status_t status;
  efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  efi_gop_t* gop;
  status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
  devparams->gop = gop;
  if(!EFI_ERROR(status) && devparams->gop) {
    status = gop->SetMode(devparams->gop, gop->Mode->MaxMode - 1);
    ST->ConOut->Reset(ST->ConOut, 0);
    ST->StdErr->Reset(ST->StdErr, 0);
    if(EFI_ERROR(status)) {
      printf("unable to set video mode\n");
      return -1;
    }
  } else {
    printf("unable to get graphics output protocol\n");
    return -1;
  }
  devparams->ramsize = gop->Mode->Information->VerticalResolution *
                       gop->Mode->Information->HorizontalResolution * sizeof(uint32_t);
  printf("fbgop video on. (videoram=%d)\n", devparams->ramsize);
  return 0;
}

len_t fbgop_read(void* devparam, void* ptr, len_t size)
{
  return 0;
}

len_t fbgop_write(void* devparam, const void* ptr, len_t size)
{
  fbgop* fb = devparam;
  efi_gop_t* gop = fb->gop;
  uint32_t* input = (uint32_t*)ptr;
  if (size < fb->ramsize) {
    printf("fbgop: buffer=%d < videoram=%d, skipping\n", size, fb->ramsize);
    return 0;
  }
  gop->Blt(fb->gop, input, EfiBltBufferToVideo, 0, 0, 0, 0,
           gop->Mode->Information->HorizontalResolution,
           gop->Mode->Information->VerticalResolution, 0);
  return size;
}

void fbgop_seek(void* devparam, len_t offset)
{
}

int_t fbgop_ioctl(void* devparam, ulong_t request, ...)
{
  return 0;
}
