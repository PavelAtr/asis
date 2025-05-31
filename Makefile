include .config

export PREFIX=/asis
ifeq ($(CONFIG_X86_64), y)
    export ARCH=x86_64
endif
ifeq ($(CONFIG_LINUX), y)
    export CFLAGS= -fPIC -g -fomit-frame-pointer
    export CFLAGS_CORE= -fPIC -g -fomit-frame-pointer
    export LDFLAGS_CORE=-o ../build/asis.linux
    export SYSROOT=--sysroot=$(PREFIX)
    export LD=$(CC)
    export CC_CORE=$(CC)
    export LD_CORE=$(CC)
endif

ifeq ($(CONFIG_UEFI), y)
    export CFLAGS= -fPIC -g -fomit-frame-pointer -DUEFI_KERNEL
    export CFLAGS_CORE= -Wall -Wextra --ansi -O0 -Wno-unused-parameter -DUEFI\
                        -fomit-frame-pointer -I/asis/usr/include -I/usr/include/x86_64-linux-gnu/ \
                        -fshort-wchar -fno-strict-aliasing -ffreestanding -fno-stack-protector \
                        -fno-stack-check -I. -I./uefi -I/usr/include -I/usr/include/efi \
                        -I/usr/include/efi/protocol -I/usr/include/efi/x86_64 -D__x86_64__ \
                        -DHAVE_USE_MS_ABI -mno-red-zone --target=x86_64-pc-win32-coff \
                        -Wno-builtin-requires-header -Wno-incompatible-library-redeclaration \
                        -Wno-long-long -Wno-comment
    export LDFLAGS_CORE= -flavor link -subsystem:efi_application -nodefaultlib -dll -entry:uefi_init uefi/*.o -out:../build/asis.uefi
    export SYSROOT=--sysroot=$(PREFIX)
    export LD=$(CC)
    export CC_CORE=clang
    export LD_CORE=lld
endif

all: headers
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
    