ENTRY(kernel_main)

SECTIONS
{
  . = 0x1000;        /* start the kernel at 0x1000 */

  .text : { *(.text) }       /* all code goes here */
  .rodata : { *(.rodata) }   /* read-only data */
  .data : { *(.data) }       /* initialized data */
  .bss : { *(.bss) }         /* uninitialized data */
}
