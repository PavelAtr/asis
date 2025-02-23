#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>

int main(int argc, char** argv)
{
   void* hndl = dlopen("libpng16.so.16", RTLD_NOW | RTLD_LOCAL| RTLD_DEEPBIND);
   assert(hndl);
   void* hndl2 = dlopen("libpng16.so.16", RTLD_NOW | RTLD_LOCAL| RTLD_DEEPBIND);
   assert(hndl2);
   dlclose(hndl);
   dlclose(hndl2);


   return 0;
}