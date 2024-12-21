PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer -I$(PREFIX)/usr/include

all: 
	make -C init/
	$(CC) $(CFLAGS) -c init/__stack_chk_fail.c stdio/*.c stdlib/*.c unistd/*.c tiny/*.c string/*.c dirent/*.c fcntl/*.c mman/*.c time/*.c signal/*.c stat/*.c byteswap/*.c wait/*.c alien/*.c
	$(CC) $(CFLAGS) -g -fPIC -nostdlib -shared *.o -o libtinyc.so
	ar rcs libtinyc.a *.o init/*.o
	
clean:
	make -C init/ clean
	rm -f *.o *.a *.so
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install init/crt.o $(DESTDIR)$(PREFIX)/lib/crt.o
	install libtinyc.so $(DESTDIR)$(PREFIX)/lib/libc.so
	install libtinyc.a $(DESTDIR)$(PREFIX)/lib/libc.a
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/
