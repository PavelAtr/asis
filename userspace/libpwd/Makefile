PREFIX?=/asis
CFLAGS?= -g -fPIC -fomit-frame-pointer
LDFLAGS?= -nostdlib -lac -Wl,-fno-undefined -shared
SYSROOT?= --sysroot=$(PREFIX)

all: 
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -fPIC -c ../src/*.c
	cd build; $(CC) $(SYSROOT) -fPIC $(LDFLAGS) *.o -o libpwd.so
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
