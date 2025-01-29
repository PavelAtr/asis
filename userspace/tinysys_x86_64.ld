SECTIONS {
    .text :
    {
        . += 0;
        syscall = .;
        . += 8;
        fds = .;
        . += 8;
        environ = .;
        . += 8;
        progname = .;
        . += 8;
        _start = .;
        . += 8;
        *(.text .text.*)
    }
    .data :
    {
        *(.data .data.*)
    }
    .rodata :
    {
        *(.rodata .rodata.*)
    }
    .bss :
    {
        *(.bss .bss.*)
    }
}
