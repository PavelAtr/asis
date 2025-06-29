PREFIX?=/
CFLAGS?=-g -fPIC  -I../include
LDFLAGS?=

all: 
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -D__BSD_VISIBLE -fPIC -c ../src/*.c
	cd build; $(CCLD) $(SYSROOT) -fPIC $(LDFLAGS) -shared *.o -o libglob.so
	cd build; ar rcs libglob.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install build/libglob.so $(DESTDIR)$(PREFIX)/lib/libglob.so
	install build/libglob.a $(DESTDIR)$(PREFIX)/lib/libglob.a
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
