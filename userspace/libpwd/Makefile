PREFIX?=/asis
CFLAGS?=-g -fPIC -I../include
LDFLAGS=-nostdlib -Wl,-fno-undefined
LD=$(CC)

all: 
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -fPIC -c ../src/*.c
	cd build; $(LD) $(SYSROOT) -fPIC $(LDFLAGS) -shared *.o -o libpwd.so
	cd build; ar rcs libpwd.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install build/libpwd.so $(DESTDIR)$(PREFIX)/lib/libpwd.so
	install build/libpwd.a $(DESTDIR)$(PREFIX)/lib/libpwd.a
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
