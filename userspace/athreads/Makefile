PREFIX?=/asis
CFLAGS?=-g -fPIC -I../include
LDFLAGS?=

all: install_headers
	mkdir -p build
	cd build; $(CC) $(SYSROOT) $(CFLAGS) -fPIC -c ../src/*.c
	cd build; $(CCLD) $(SYSROOT) -fPIC -shared *.o $(LDFLAGS) -o libathread.so
	cd build; ar rcs libathread.a *.o
	
clean:
	rm -f build/*
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib/pkgconfig
	install build/libathread.so $(DESTDIR)$(PREFIX)/lib/libathread.so
	install build/libathread.a $(DESTDIR)$(PREFIX)/lib/libathread.a
	cp src/pthread.pc $(DESTDIR)$(PREFIX)/lib/pkgconfig/
	make install_headers

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr || true
	cp -r include $(DESTDIR)$(PREFIX)/usr/ || true
