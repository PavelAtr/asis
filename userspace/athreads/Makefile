PREFIX?=/asis
CFLAGS?=-g -fPIC -I../include
LDFLAGS=-nostdlib -Wl,-fno-undefined
LD=$(CC)

all: 
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -fPIC -c ../src/*.c
	cd build; $(LD) $(SYSROOT) -fPIC $(LDFLAGS) -shared *.o -o libpthread.so
	cd build; ar rcs libpthread.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install build/libpthread.so $(DESTDIR)$(PREFIX)/lib/libpthread.so
	install build/libpthread.a $(DESTDIR)$(PREFIX)/lib/libpthread.a
	cp src/pthread.pc $(DESTDIR)$(PREFIX)/lib/pkgconfig/
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
