include .config

all:
	make -C core -f Makefile.linux

menuconfig:
	kconfig-mconf KConfig
	cat .config | grep -v "#" | tr '=' ' ' | tr '=' ' ' | tr -s '\n' | sed 's/\(,*\)/#define \1/' > config.h
