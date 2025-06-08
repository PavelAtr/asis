#include "../../core/uefi/uefi.h"
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
   devparams->width = gop->Mode->Information->HorizontalResolution;
   devparams->height = gop->Mode->Information->VerticalResolution;
   devparams->x1 = 0;
   devparams->y1 = 0;
   devparams->x2 =  devparams->width - 1;
   devparams->y2 =  devparams->height - 1;
   printf("fbgop video on. (%dX%d)\n", devparams->width, devparams->height);
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
   gop->Blt(fb->gop, input, EfiBltBufferToVideo, 0, 0, fb->x1, fb->y1,
      fb->x2 - fb->x1, fb->y2 - fb->y1, 0);
   return size;
}

void fbgop_seek(void* devparam, len_t offset)
{
}

int_t fbgop_ioctl(void* devparam, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4)
{
    fbgop* gop = devparam;
    int* ret = (int*)arg1;
    switch(request)
    {
      case GETWIDTH:
	      *ret = gop->width;
	      return 0;
      case GETHEIGHT:
	      *ret = gop->height;
	      return 0;
      case SETX:
	      gop->x1 = (int) arg1;
	      printf("fbgop: x1=%d\n", gop->x1);
	      break;
      case SETY: 
	      gop->y1 = (int) arg1;
	      printf("fbgop: y1=%d\n", gop->y1);
	      break;
      case SETX2:
	      gop->x2 = (int) arg1;
	      printf("fbgop: x2=%d\n", gop->x2);
	      break;
      case SETY2:
	      gop->y2 = (int) arg1;
	      printf("fbgop: y2=%d\n", gop->y2);
	      break;
    }
   return 0;
}
