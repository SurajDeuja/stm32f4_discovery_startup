ENTRY(Reset_Handler)

/* Stack is placed in the 64KB CCM memory */
/* NB. CCM memory cannot be accessed by peripherals or DMA! */
/* Always use static/global variables with peripherals/DMA. */
_estack = 0x10000000 + 64K;

MEMORY
{
	FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K
	RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
	/* Reset Vector */
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} >FLASH

	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)

		. = ALIGN(4);
		_etext = .;
		_exit = .;
	} >FLASH

	_sidata = .;

	.data : AT ( _sidata )
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} >RAM

	. = ALIGN(4);
	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
	} >RAM

}
