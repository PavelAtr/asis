PREFIX?=/asis
EXTENTION?=
CFLAGS?=-g -fPIC -fomit-frame-pointer
LDFLAGS=-nostdlib $(PREFIX)/lib/crt.o $(PREFIX)/lib/tls.o -lac

all:
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC shell.c $(LDFLAGS) -o shell$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC hello.c $(LDFLAGS) -o hello$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC ls.c $(LDFLAGS) -o ls$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC stat.c $(LDFLAGS) -o stat$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC mkdir.c $(LDFLAGS) -o mkdir$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC touch.c $(LDFLAGS) -o touch$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC unlink.c $(LDFLAGS) -o unlink$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC wallpaper.c $(LDFLAGS) -o wallpaper$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC id.c $(LDFLAGS) -o id$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC chmod.c $(LDFLAGS) -o chmod$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC chown.c $(LDFLAGS) -o chown$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC testfork.c $(LDFLAGS) -o testfork$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC segfault.c $(LDFLAGS)  -o segfault$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC passdb.c $(LDFLAGS) -lpwd -o passdb$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC grpdb.c $(LDFLAGS) -lpwd -o grpdb$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC _exit.c $(LDFLAGS) -o _exit$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC jmp.c $(LDFLAGS) -o jmp$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC fds.c $(LDFLAGS) -o fds$(EXTENTION)
	$(CC) --sysroot=$(PREFIX) $(CFLAGS) -fPIC mycat.c $(LDFLAGS) -o mycat$(EXTENTION)

#	$(CC) -g test1.c -o test1
#	$(CC) -g -I../libpwd/include/ ../libpwd/libpwd.a test2.c -o test2
#	$(CC) -g test3.c -o test3
#	$(CC) -g mycat.c -o mycat_native
#	$(CC) -g jmp.c -o test4

clean:
	rm -f shell$(EXTENTION) hello$(EXTENTION) test$(EXTENTION) touch$(EXTENTION) wallpaper$(EXTENTION) \
              ls$(EXTENTION) stat$(EXTENTION) unlink$(EXTENTION) id$(EXTENTION) mkdir$(EXTENTION) chown$(EXTENTION) \
              chmod$(EXTENTION) testfork$(EXTENTION) segfault$(EXTENTION) passdb$(EXTENTION) grpdb$(EXTENTION) _exit$(EXTENTION) \
              test1$(EXTENTION) test2$(EXTENTION) test3$(EXTENTION) jmp$(EXTENTION) fds$(EXTENTION) mycat$(EXTENTION)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install shell$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/shell$(EXTENTION)
	install hello$(EXTENTION) $(DESTDIR)$(PREFIX)/bin//hello$(EXTENTION)
#	install ls$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/ls$(EXTENTION)
#	install stat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/stat$(EXTENTION)
#	install mkdir$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mkdir$(EXTENTION)
#	install touch$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/touch$(EXTENTION)
#	install unlink$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/unlink$(EXTENTION)
	install wallpaper$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/wallpaper$(EXTENTION)
	install wallpaper.raw $(DESTDIR)$(PREFIX)/wallpaper.raw
#	install id$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/id$(EXTENTION)
#	install chmod$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chmod$(EXTENTION)
#	install chown$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chown$(EXTENTION)
	install testfork$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/testfork$(EXTENTION)
	install segfault$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/segfault$(EXTENTION)
	install passdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/passdb$(EXTENTION)
	install grpdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/grpdb$(EXTENTION)
	install _exit$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/_exit$(EXTENTION)
	install jmp$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/jmp$(EXTENTION)
	install fds$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/fds$(EXTENTION)
	install mycat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mycat$(EXTENTION)





