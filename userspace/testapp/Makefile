PREFIX?=/tinysys
#CFLAGS?=-fPIC -I$(PREFIX)/usr/include -fomit-frame-pointer
CFLAGS?=-g -fPIC --sysroot=$(PREFIX) -fomit-frame-pointer
LDFLAGS=-nostdlib $(PREFIX)/lib/crt.o $(PREFIX)/lib/libc.so -shared
#LDFLAGS=-nostdlib -Wl,-Ttinysys.ld $(PREFIX)/lib/libc.a

all:
	$(CC) $(CFLAGS) -fPIC shell.c $(LDFLAGS) -o shell
	$(CC) $(CFLAGS) -fPIC hello.c $(LDFLAGS) -o hello
	$(CC) $(CFLAGS) -fPIC ls.c $(LDFLAGS) -o ls
	$(CC) $(CFLAGS) -fPIC stat.c $(LDFLAGS) -o stat
	$(CC) $(CFLAGS) -fPIC mkdir.c $(LDFLAGS) -o mkdir
	$(CC) $(CFLAGS) -fPIC touch.c $(LDFLAGS) -o touch
	$(CC) $(CFLAGS) -fPIC unlink.c $(LDFLAGS) -o unlink
	$(CC) $(CFLAGS) -fPIC wallpaper.c $(LDFLAGS) -o wallpaper
	$(CC) $(CFLAGS) -fPIC id.c $(LDFLAGS) -o id
	$(CC) $(CFLAGS) -fPIC chmod.c $(LDFLAGS) -o chmod
	$(CC) $(CFLAGS) -fPIC chown.c $(LDFLAGS) -o chown
	$(CC) $(CFLAGS) -fPIC testfork.c $(LDFLAGS) -o testfork
	$(CC) $(CFLAGS) -fPIC segfault.c $(LDFLAGS)  -o segfault
	$(CC) $(CFLAGS) -fPIC passdb.c $(LDFLAGS) $(PREFIX)/lib/libpwd.so -o passdb
	$(CC) $(CFLAGS) -fPIC grpdb.c $(LDFLAGS) $(PREFIX)/lib/libpwd.so -o grpdb
	$(CC) $(CFLAGS) -fPIC _exit.c $(LDFLAGS) -o _exit
	$(CC) $(CFLAGS) -fPIC jmp.c $(LDFLAGS) -o jmp

	$(CC) -g -I../libpwd/include/ ../libpwd/libpwd.a test1.c -o test1
	$(CC) -g -I../libpwd/include/ ../libpwd/libpwd.a test2.c -o test2
#	$(CC) -g test3.c -o test3
	$(CC) -g jmp.c -o test4

clean:
	rm -f shell hello test touch wallpaper ls stat unlink id mkdir chown chmod testfork segfault passdb grpdb _exit test1 test2 test3 jmp

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install shell $(DESTDIR)$(PREFIX)/bin/shell
	install hello $(DESTDIR)$(PREFIX)/bin//hello
	install ls $(DESTDIR)$(PREFIX)/bin/ls
	install stat $(DESTDIR)$(PREFIX)/bin/stat
	install mkdir $(DESTDIR)$(PREFIX)/bin/mkdir
	install touch $(DESTDIR)$(PREFIX)/bin/touch
	install unlink $(DESTDIR)$(PREFIX)/bin/unlink
	install wallpaper $(DESTDIR)$(PREFIX)/bin/wallpaper
	install wallpaper.raw $(DESTDIR)$(PREFIX)/wallpaper.raw
	install id $(DESTDIR)$(PREFIX)/bin/id
	install chmod $(DESTDIR)$(PREFIX)/bin/chmod
	install chown $(DESTDIR)$(PREFIX)/bin/chown
	install testfork $(DESTDIR)$(PREFIX)/bin/testfork
	install segfault $(DESTDIR)$(PREFIX)/bin/segfault
	install passdb $(DESTDIR)$(PREFIX)/bin/passdb
	install grpdb $(DESTDIR)$(PREFIX)/bin/grpdb
	install _exit $(DESTDIR)$(PREFIX)/bin/_exit
	install jmp $(DESTDIR)$(PREFIX)/bin/jmp





