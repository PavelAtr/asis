PREFIX?=/asis
ARCH?=x86_64

CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX) -DELF64
LDLAGS?= --sysroot=$(PREFIX) -lac -Wl,-fno-undefined -nostdlib 

all: 
	$(CC) $(CFLAGS) -fPIC -c $(ARCH)/*.c *.c
	$(CC) $(CFLAGS) -fPIC  $(LDFLAGS) -nostdlib -shared *.o -o libdl.so
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
