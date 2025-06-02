PREFIX?=/asis
LDLAGS=-Wl,-fno-undefined -nostdlib
CFLAGS?=-g -fPIC -fomit-frame-pointer
SYSROOT?=--sysroot=$(PREFIX)

all: 
	make -C init/
	mkdir -p build
	
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -Wno-pointer-to-int-cast -c ../alien/*.c ../alien/ctype/*.c ../alien/string/*.c \
../alien/regex/*.c ../alien/multibyte/*.c ../src/*.c
	cd build; $(LD) $(SYSROOT) -shared -nostdlib *.o -o libac.so
	cd build; ar rcs libac.a *.o ../init/*.o
	
clean:
	make -C init/ clean
	cd build; rm -f *.o *.a *.so
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install init/crt.o $(DESTDIR)$(PREFIX)/lib/crt.o
	install init/crtstub.a $(DESTDIR)$(PREFIX)/lib/crtstub.a
	install build/libac.so $(DESTDIR)$(PREFIX)/lib/libac.so
	install build/libac.a $(DESTDIR)$(PREFIX)/lib/libac.a
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r include_stub/* $(DESTDIR)$(PREFIX)/usr/include/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/
