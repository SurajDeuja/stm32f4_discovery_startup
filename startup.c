/** @file startup.h
 *  @brief Startup header file for STM32M4Discovery board.
 *
 *  @author Suraj Deuja
 */
#include "startup.h"

/// Interrupt vector table
__attribute__((section(".isr_vector"))) 
unsigned int INTERRUPT_VECTOR[] = { (unsigned int) &_estack, 
                                     (unsigned int) __reset_handler,
                                     0, /* NMI */
                                     0, /* Hard fault */
                                     0, /* Memory management fault */
                                     0, /* Bus fault */
                                     0, /* Usage fault */
                                     0, /* Reserved */
                                     0, /* Reserved */
                                     0, /* Reserved */
                                     0, /* Reserved */
                                     0, /* SVCall */
                                     0, /* Reserved for debug */
                                     0, /* Reserved */
                                     0, /* PendSV */
                                     0, /* Systick */
                                     0, /* IRQ0 */
                                     0, /* IRQ1 */}; 

void __reset_handler(void)
{
	int i;
	int *pisr_start = &_sisr_vector;
    int *psidata = &_sidata;
    int *psdata = &_sdata;
    int *pedata = &_edata;
    int *psbss = &_sbss;
    int *pebss = &_ebss;

	/// Copy the interrupt table from memory to ISR vector table.
	for (i = 0; i < sizeof(INTERRUPT_VECTOR)/sizeof(INTERRUPT_VECTOR[0]); i++) {
		*pisr_start++ = INTERRUPT_VECTOR[i]; 
	}

    /// Initialize data section
    while (psdata < pedata) {
        *psdata++ = *psidata++;
    }

    /// Zero fill bss section
    while(psbss < pebss) {
        *psbss++ = 0;
    }

    ///@todo Do more initialization of system clock and GPIO here 

    /// Now call the main function
    main();
    __exit();
}

void __exit(void)
{
    /// returned from the main function. Nothing to do so just sit here
	while(1);
}

void __default_handler(void)
{
    /// default handler for all isr routine
	while(1);
}
