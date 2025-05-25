PREFIX?=/asis
CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX)

all: 
	make -C init/
	$(CC) $(CFLAGS) -c alien/*.c alien/ctype/*.c alien/string/*.c \
alien/regex/*.c alien/multibyte/*.c init/init.c src/*.c
	$(CC) $(CFLAGS) -g -fPIC -nostdlib -shared *.o init/tls.a -o libac.so
	ar rcs libac.a *.o init/*.o
	
clean:
	make -C init/ clean
	rm -f *.o *.a *.so
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	install init/crt.o $(DESTDIR)$(PREFIX)/lib/crt.o
	install init/tls.a $(DESTDIR)$(PREFIX)/lib/tls.a
	install init/crtstub.a $(DESTDIR)$(PREFIX)/lib/crtstub.a
	install libac.so $(DESTDIR)$(PREFIX)/lib/libac.so
	install libac.a $(DESTDIR)$(PREFIX)/lib/libac.a
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r include_stub/* $(DESTDIR)$(PREFIX)/usr/include/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr
	cp -r include $(DESTDIR)$(PREFIX)/usr/
	cp -r include_stub/* $(DESTDIR)$(PREFIX)/usr/include/
	cp -r alien/include $(DESTDIR)$(PREFIX)/usr/
