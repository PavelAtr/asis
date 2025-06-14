PREFIX?=/asis
EXTENTION?=
CFLAGS?= -g -fPIC -fomit-frame-pointer
LDFLAGS?=-nostdlib $(PREFIX)/lib/crt.o -lac
SYSROOT?=--sysroot=$(PREFIX)

all:
	mkdir -p build
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC shell.c $(LDFLAGS) -o build/shell$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC hello.c $(LDFLAGS) -o build/hello$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC ls.c  $(LDFLAGS) -o build/ls$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC stat.c $(LDFLAGS) -o build/stat$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC mkdir.c $(LDFLAGS) -o build/mkdir$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC touch.c  $(LDFLAGS) -o build/touch$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC unlink.c $(LDFLAGS) -o build/unlink$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC wallpaper.c -Wno-int-to-pointer-cast $(LDFLAGS) -o build/wallpaper$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC id.c  $(LDFLAGS) -o build/id$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC chmod.c $(LDFLAGS) -o build/chmod$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC chown.c  $(LDFLAGS) -o build/chown$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC testfork.c  $(LDFLAGS) -shared -o build/testfork$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC segfault.c  $(LDFLAGS)  -o build/segfault$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC passdb.c  $(LDFLAGS) -lpwd -shared -o build/passdb$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC grpdb.c  $(LDFLAGS) -lpwd -shared -o build/grpdb$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC _exit.c $(LDFLAGS) -o build/_exit$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC jmp.c $(LDFLAGS) -o build/jmp$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC fds.c  $(LDFLAGS) -o build/fds$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC mycat.c $(LDFLAGS) -o build/mycat$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC fifo.c  $(LDFLAGS) -o build/fifo$(EXTENTION)
	$(CC) $(SYSROOT) $(CFLAGS) -fPIC thread.c $(LDFLAGS) -lathread -shared -o build/thread$(EXTENTION)

#	$(CC) -g test1.c -o test1
#	$(CC) -g -I../libpwd/include/ ../libpwd/libpwd.a test2.c -o test2
#	$(CC) -g test3.c -o test3
#	$(CC) -g mycat.c -o mycat_native
#	$(CC) -g jmp.c -o test4

clean:
	rm -f build/*

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install build/shell$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/shell$(EXTENTION)
	install build/hello$(EXTENTION) $(DESTDIR)$(PREFIX)/bin//hello$(EXTENTION)
	install build/ls$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/ls$(EXTENTION)
	install build/stat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/stat$(EXTENTION)
	install build/mkdir$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mkdir$(EXTENTION)
	install build/touch$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/touch$(EXTENTION)
	install build/unlink$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/unlink$(EXTENTION)
	install build/wallpaper$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/wallpaper$(EXTENTION)
	install wallpaper.raw $(DESTDIR)$(PREFIX)/wallpaper.raw
	install planet.raw $(DESTDIR)$(PREFIX)/planet.raw
	install build/id$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/id$(EXTENTION)
	install build/chmod$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chmod$(EXTENTION)
	install build/chown$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/chown$(EXTENTION)
	install build/testfork$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/testfork$(EXTENTION)
	install build/segfault$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/segfault$(EXTENTION)
	install build/passdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/passdb$(EXTENTION)
	install build/grpdb$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/grpdb$(EXTENTION)
	install build/_exit$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/_exit$(EXTENTION)
	install build/jmp$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/jmp$(EXTENTION)
	install build/fds$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/fds$(EXTENTION)
	install build/mycat$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/mycat$(EXTENTION)
	install build/fifo$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/fifo$(EXTENTION)
	install build/thread$(EXTENTION) $(DESTDIR)$(PREFIX)/bin/thread$(EXTENTION)





