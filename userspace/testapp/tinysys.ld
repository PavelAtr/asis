PHDRS
{
    rx    PT_LOAD FLAGS(5); /* 0b101 - read + execute */
    ro    PT_LOAD FLAGS(4); /* 0b100 - read  */
    rw    PT_LOAD FLAGS(6); /* 0b110 - read + write */
    other    PT_NOTE FLAGS(4); /* 0b100 - read  */
}
SECTIONS {
    .text ALIGN(1) : ALIGN(1)
    {
        *(.text .text.*)
    } : rx

    .rodata ALIGN(1) : ALIGN(1)
    {
        *(.rodata .rodata.*)
    } : ro

    .data ALIGN(1) : ALIGN(1)
    {
        *(.data .data.*)
    } : rw

    .bss ALIGN(1) : ALIGN(1)
    {
        *(.bss .bss.*)
    } : rw

    .other  ALIGN(1) : ALIGN(1)
    {
        *(.note.*)
        *(.comment .comment.*)
        *(.eh_frame*)
        *(.got .got.*)
    } : other
}
