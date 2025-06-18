ARCH?=x86_64
PREFIX?=/asis
LDLAGS=-Wl,-fno-undefined -nostdlib 
CFLAGS?=-fPIC -DSTANDALONE

all: 
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -c ../$(ARCH)/*.c ../*.c
	cd build; $(LD) $(SYSROOT) $(LDFLAGS) -shared *.o -o libdl.so
	cd build; ar rcs libdl.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install build/libdl.so $(DESTDIR)$(PREFIX)/lib/libdl.so
	install build/libdl.a $(DESTDIR)$(PREFIX)/lib/libdl.a
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr/include
	cp -r dlfcn.h $(DESTDIR)$(PREFIX)/usr/include/
