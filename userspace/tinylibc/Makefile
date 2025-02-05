PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX)

all: 
	make -C init/
	$(CC) $(CFLAGS) -c init/__stack_chk_fail.c stdio/*.c stdlib/*.c unistd/*.c tiny/*.c string/*.c \
dirent/*.c fcntl/*.c mman/*.c time/*.c signal/*.c stat/*.c byteswap/*.c xattr/*.c wait/*.c alien/*.c alien/ctype/*.c alien/string/*.c  \
alien/regex/*.c syslog/*.c socket/*.c termios/*.c arpa/*.c mntent/*.c statvfs/*.c inotify/*.c ioctl/*.c \
setjmp/*.c locale/*.c langinfo/*.c libgen/*.c utsname/*.c times/*.c resource/*.c setjmp/*.c netdb/*.c
	$(CC) $(CFLAGS) -g -fPIC -nostdlib -shared *.o init/tls.o -o libtinyc.so
	ar rcs libtinyc.a *.o init/*.o
	
clean:
	make -C init/ clean
	rm -f *.o *.a *.so
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install init/crt.o $(DESTDIR)$(PREFIX)/lib/crt.o
	install init/tls.o $(DESTDIR)$(PREFIX)/lib/tls.o
	install libtinyc.so $(DESTDIR)$(PREFIX)/lib/libtinyc.so
	install libtinyc.a $(DESTDIR)$(PREFIX)/lib/libtinyc.a
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r include_stub/* $(DESTDIR)$(PREFIX)/usr/include/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r include_stub/* $(DESTDIR)$(PREFIX)/usr/include/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/
