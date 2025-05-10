PREFIX?=/tinysys
EXTENTION?=.so
CFLAGS?=-g -fPIC --sysroot=$(PREFIX) -fomit-frame-pointer
#LDFLAGS=--sysroot=$(PREFIX) -Wl,-T../tinysys_x86_64.ld -nostdlib $(PREFIX)/lib/crt.o -ltinyc -shared
LDFLAGS=--sysroot=$(PREFIX) -nostdlib $(PREFIX)/lib/crt.o $(PREFIX)/lib/tls.a -ltinyc -shared

all:
	$(CC) $(CFLAGS) -fPIC shell.c $(LDFLAGS) -o shell$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC hello.c $(LDFLAGS) -o hello$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC ls.c $(LDFLAGS) -o ls$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC stat.c $(LDFLAGS) -o stat$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC mkdir.c $(LDFLAGS) -o mkdir$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC touch.c $(LDFLAGS) -o touch$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC unlink.c $(LDFLAGS) -o unlink$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC wallpaper.c $(LDFLAGS) -o wallpaper$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC id.c $(LDFLAGS) -o id$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC chmod.c $(LDFLAGS) -o chmod$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC chown.c $(LDFLAGS) -o chown$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC testfork.c $(LDFLAGS) -o testfork$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC segfault.c $(LDFLAGS)  -o segfault$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC passdb.c $(LDFLAGS) -lpwd -o passdb$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC grpdb.c $(LDFLAGS) -lpwd -o grpdb$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC _exit.c $(LDFLAGS) -o _exit$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC jmp.c $(LDFLAGS) -o jmp$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC fds.c $(LDFLAGS) -o fds$(EXTENTION)
	$(CC) $(CFLAGS) -fPIC mycat.c $(LDFLAGS) -o mycat$(EXTENTION)

	$(CC) -g test1.c -o test1
#	$(CC) -g -I../libpwd/include/ ../libpwd/libpwd.a test2.c -o test2
	$(CC) -g test3.c -o test3
#	$(CC) -g jmp.c -o test4

clean:
	rm -f shell$(EXTENTION) hello$(EXTENTION) test$(EXTENTION) touch$(EXTENTION) wallpaper$(EXTENTION) \
              ls$(EXTENTION) stat$(EXTENTION) unlink$(EXTENTION) id$(EXTENTION) mkdir$(EXTENTION) chown$(EXTENTION) \
              chmod$(EXTENTION) testfork$(EXTENTION) segfault$(EXTENTION) passdb$(EXTENTION) grpdb$(EXTENTION) _exit$(EXTENTION) \
              test1$(EXTENTION) test2$(EXTENTION)$(EXTENTION) test3$(EXTENTION) jmp$(EXTENTION) fds$(EXTENTION) mycat$(EXTENTION)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install shell$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/shell$(EXTENTION)
	install hello$(EXTENTION) $(DESTDIR)$(PREFIX)/bin//hello$(EXTENTION)
	install ls$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/ls$(EXTENTION)
	install stat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/stat$(EXTENTION)
	install mkdir$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mkdir$(EXTENTION)
	install touch$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/touch$(EXTENTION)
	install unlink$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/unlink$(EXTENTION)
	install wallpaper$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/wallpaper$(EXTENTION)
	install wallpaper.raw $(DESTDIR)$(PREFIX)/wallpaper.raw
	install id$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/id$(EXTENTION)
	install chmod$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chmod$(EXTENTION)
	install chown$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chown$(EXTENTION)
	install testfork$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/testfork$(EXTENTION)
	install segfault$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/segfault$(EXTENTION)
	install passdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/passdb$(EXTENTION)
	install grpdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/grpdb$(EXTENTION)
	install _exit$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/_exit$(EXTENTION)
	install jmp$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/jmp$(EXTENTION)
	install fds$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/fds$(EXTENTION)
	install mycat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mycat$(EXTENTION)





