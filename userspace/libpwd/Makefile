PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer -I$(PREFIX)/usr/include
LDLAGS?= $(PREFIX)/usr/lib/libc.so

all: 
	$(CC) $(CFLAGS) -g -fPIC -c src/*.c
	$(CC) $(CFLAGS) -g -fPIC  $(LDFLAGS) -nostdlib -shared *.o -o libpwd.so
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
