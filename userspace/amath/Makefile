PREFIX?=/asis
CFLAGS?=-g -fPIC -I../include
LDFLAGS?=

all: install_headers
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -fPIC -c ../src/x86_64/*.c ../src/*.c
	cd build; $(CCLD) $(SYSROOT) -fPIC -shared *.o $(LDFLAGS) -o libam.so
	cd build; ar rcs libam.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install build/libam.so $(DESTDIR)$(PREFIX)/lib/libam.so
	install build/libam.a $(DESTDIR)$(PREFIX)/lib/libam.a
	cp src/libm.pc $(DESTDIR)$(PREFIX)/lib/pkgconfig/
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
