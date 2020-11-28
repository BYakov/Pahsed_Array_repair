/*------------------------------------------------------------------------------
 *      Linker script for running in internal SRAM on the AT91SAM3U4
 *----------------------------------------------------------------------------*/

/* Vector Definition */
_vect_start = 0x20000000;

/* Memory Spaces Definitions */
MEMORY
{
    sram0 (W!RX) : ORIGIN = 0x20000000, LENGTH = 0x00008000 /* Sram0, 32K */
    sram1 (W!RX) : ORIGIN = 0x20080000, LENGTH = 0x00004000 /* Sram1, 16K */
}

SECTIONS
{
    .fixed :
    {
        . = ALIGN(4);
        _sfixed = .;
        KEEP(*(.vectors))
        *(.text*)
        *(.ramfunc)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        . = ALIGN(4);
        _efixed = .;            /* End of text section */
    } > sram0

    .relocate : AT (_efixed)
    {
        . = ALIGN(4);
        _srelocate = .;
        *(.data)
        . = ALIGN(4);
        _erelocate = .;
    } >sram1

    .bss (NOLOAD) : {
        . = ALIGN(4);
        _szero = .;
        *(.bss)
        . = ALIGN(4);
        _ezero = .;
    } >sram1

    /* eh_frame is needed for GCC 4.4.1 */
    . = ALIGN(4);
    .eh_frame :
    {
        KEEP (*(.eh_frame))
    } >sram1


    /* Stack in the end of SRAM1 */
    _estack = 0x20083FFC;
}
end = .;
