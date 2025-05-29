PREFIX?=/asis
ARCH?=x86_64

CFLAGS?= -g -fPIC -fomit-frame-pointer -DELF64
LDLAGS?= -lac -Wl,-fno-undefined -nostdlib 
SYSROOT?= --sysroot=$(PREFIX)

all: 
	$(CC) $(SYSROOT) $(CFLAGS) -c $(ARCH)/*.c *.c
	$(CC) $(SYSROOT) $(LDFLAGS) -shared *.o -o libdl.so
	ar rcs libdl.a *.o
	
clean:
	rm -f *.o *.a *.so x86_64/*.o
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install libdl.so $(DESTDIR)$(PREFIX)/lib/libdl.so
	install libdl.a $(DESTDIR)$(PREFIX)/lib/libdl.a
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r dlfcn.h $(DESTDIR)$(PREFIX)/usr/include/

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r dlfcn.h $(DESTDIR)$(PREFIX)/usr/include/
