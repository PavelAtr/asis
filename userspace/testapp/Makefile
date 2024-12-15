PREFIX?=/tinysys
#CFLAGS?=-fPIC -I$(PREFIX)/usr/include -fomit-frame-pointer
CFLAGS?=-fPIC --sysroot=$(PREFIX) -fomit-frame-pointer
LDFLAGS=-nostdlib $(PREFIX)/lib/crt.o $(PREFIX)/lib/libc.so
#LDFLAGS=-nostdlib -Wl,-Ttinysys.ld $(PREFIX)/lib/libc.a

all:
	$(CC) $(CFLAGS) -fPIC shell.c $(LDFLAGS)  -o shell
	$(CC) $(CFLAGS) -fPIC hello.c $(LDFLAGS)  -o hello
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
	$(CC) $(CFLAGS) -fPIC segfault.c $(LDFLAGS) -o segfault
	$(CC) $(CFLAGS) -fPIC passdb.c $(LDFLAGS) $(PREFIX)/lib/libpwd.so -o passdb
	$(CC) $(CFLAGS) -fPIC grpdb.c $(LDFLAGS) $(PREFIX)/lib/libpwd.so -o grpdb

#	$(CC) -g test.c -o test
	$(CC) -g -include ../libpwd/include/pwd.h  -include ../libpwd/include/grp.h ../tinylibc/stdio/fgets.c  ../tinylibc/stdio/getc.c ../libpwd/src/*.c ../tinylibc/string/strtok.c test.c -o test
	$(CC) -g -include ../libpwd/include/pwd.h  -include ../libpwd/include/grp.h ../tinylibc/stdio/fgets.c  ../tinylibc/stdio/getc.c ../libpwd/src/*.c ../tinylibc/string/strtok.c test2.c -o test2
#	$(CC) -g ../tinylibc/stdlib/mkostemps.c test3.c -o test3

clean:
	rm -f shell hello test touch wallpaper ls stat unlink id mkdir chown chmod testfork segfault passdb grpdb

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




