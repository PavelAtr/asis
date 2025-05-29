PREFIX?=/asis
CFLAGS= -g -fPIC -fomit-frame-pointer
LDFLAGS= -nostdlib -lac -Wl,-fno-undefined -shared

all: 
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC -c src/*.c
	$(CC) --sysroot=$(PREFIX)  -fPIC  $(LDFLAGS) *.o -o libpwd.so
	ar rcs libpwd.a *.o
	
clean:
	rm -f *.o *.a *.so
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install libpwd.so $(DESTDIR)$(PREFIX)/lib/libpwd.so
	install libpwd.a $(DESTDIR)$(PREFIX)/lib/libpwd.a
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
