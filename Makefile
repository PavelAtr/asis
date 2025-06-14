all: headers
#	install cc-asis /usr/local/bin/cc-asis
	make -C core
	make -C userspace

headers:
	make -C core install_headers
	make -C userspace install_headers

menuconfig:
	kconfig-mconf KConfig
	cat .config | grep -v "#" | tr '=' ' ' | tr '=' ' ' | tr -s '\n' | sed 's/\(,*\)/#define \1/' > config.h

clean:
	make -C core clean
	make -C userspace clean
    