OUTPUT_ARCH( "riscv" )

MEMORY
{
	FLASH   : ORIGIN = 0xC0000000,                              LENGTH = 0x10000
	SRAM    : ORIGIN = 0xa0000000,                              LENGTH = 0x40000
	DDR     : ORIGIN = 0x80000000,                              LENGTH = 0x100000

}

ENTRY( reset_vector )

SECTIONS
{

  /*--------------------------------------------------------------------*/
  /* Code and read-only segment                                         */
  /*--------------------------------------------------------------------*/

  /* Begining of code and text segment */

  _ftext = .;
  PROVIDE( eprol = . );

  .entry :
  {
  	. = ALIGN(32);
    *(.text.init)
    . = ALIGN(32);
  } > SRAM

  /* text: Program code section */
  .text : AT ( (LOADADDR (.entry) + SIZEOF(.entry) + 31) & ~ (32-1))
  {
  	. = ALIGN(32);
  	__text_s = .;
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    . = ALIGN(32);
    __text_e = .;
  } > SRAM

  /* rodata: Read-only data */
  .rodata : AT ( (LOADADDR (.text) + SIZEOF(.text) + 31) & ~ (32-1))
  {
  	. = ALIGN(32);
	__rodata_s = .;
    *(.rdata)
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(32);
	__rodata_e = .;
  } > SRAM



  /* End of code and read-only segment */
  PROVIDE( etext = . );
  _etext = .;

  /*--------------------------------------------------------------------*/
  /* Initialized data segment                                           */
  /*--------------------------------------------------------------------*/

  /* Start of initialized data segment */
  . = ALIGN(16);
   _fdata = .;

  /* data: Writable data */
  .data : AT ( (LOADADDR(.rodata) + SIZEOF(.rodata) + 31) & ~ (32-1) )
  {
  	. = ALIGN(32);
	__data_s = .;
    *(.data)
    *(.data.*)
    *(.sdata)
    *(.srodata*)
    *(.gnu.linkonce.d.*)
    *(.comment)
    . = ALIGN(32);
	__data_e = .;
  } >SRAM

   __data_lma_s = LOADADDR(.data);
   __data_lma_e = ( (LOADADDR(.data) + SIZEOF(.data) + 31) & ~ (32-1) );


  /* End of initialized data segment */
  . = ALIGN(4);
  PROVIDE( edata = . );
  _edata = .;

  /*--------------------------------------------------------------------*/
  /* Uninitialized data segment                                         */
  /*--------------------------------------------------------------------*/

  /* Start of uninitialized data segment */
  . = .;
  _fbss = .;

  /* sbss: Uninitialized writeable small data section */
  . = .;

  /* bss: Uninitialized writeable data section */
  . = .;
  _bss_start = .;
  .bss : AT ( (LOADADDR(.data) + SIZEOF(.data) + 31) & ~ (32-1) )
  {
  	. = ALIGN(32);
  	__bss_s = .;
    *(.bss)

    *(.bss.*)
    *(.sbss*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(32);
 	 __bss_e = .;
  } >SRAM

  .sbi :
  {
    *(.sbi)
  }

  .payload :
  {
    *(.payload)
  }

  _end = .;
}
