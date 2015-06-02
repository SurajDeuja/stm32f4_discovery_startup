/** @file startup.h
 *  @brief Startup header file for STM32M4Discovery board.
 *
 *  @author Suraj Deuja
 */
#include "reg.h"
#include "startup.h"
#include "rcc.h"

#define PLL_N   336
#define PLL_M   8
#define PLL_P   0
#define PLL_Q   7

/// Interrupt vector table
unsigned int INTERRUPT_VECTOR[] __attribute__section((section(".isr_vector")))= { 
    (unsigned int) &_estack, 
    (unsigned int) __reset_handler,
    0,                                                      /* NMI */
    0,                                                      /* Hard fault */
    0,                                                      /* Memory management fault */
    0,                                                      /* Bus fault */
    0,                                                      /* Usage fault */
    0,                                                      /* Reserved */
    0,                                                      /* Reserved */
    0,                                                      /* Reserved */
    0,                                                      /* Reserved */
    0,                                                      /* SVCall */
    0,                                                      /* Reserved for debug */
    0,                                                      /* Reserved */
    0,                                                      /* PendSV */
    0,                                                      /* Systick */
    0,                                                      /* IRQ0 */
    0,                                                      /* IRQ1 */}; 

/** 
 * @brief Relocates the vector table offset to
 * the symbol defined in linker script. 
 */
static void __relocate_vector_table(void)
{
	__REG(__VTOR) = (unsigned int) &_isr_vector;
}

void __rst_sys_clk(void) {
    struct reg_rcc *rcc = (struct reg_cc *) REG_RCC_ADDR;
    rcc->cr |= 1<<16; // Enable HSE clock

    while(rcc->cr & 1<<17); // Wait until the HSE is ready

    rcc->apb1en |= 1<<28;   // Enable clock for power interface
    rcc->cfgr |= 0x0;       // Set prescalars to 1 (168 MHz)
    rcc->cfgr |= 1<15;      // Set high speed APB2 prescalar to 2 (84 MHz)
    rcc->cfgr |= 5<<10;     // Set low speed APB1 prescalar to 4 (42 MHz)
    rcc->pllcfgr |= (PLL_M | PLL_N << 6 | PLL_P << 22 | PLL_Q << 24);

    rcc->cr |= 1 << 28;

    while(rcc->cr & 1<<29);

    :


}

void __start_sys_clk(void) {

}

static void __start(void)
{
    int *psidata = &_sidata;
    int *psdata = &_sdata;
    int *pedata = &_edata;
    int *psbss = &_sbss;
    int *pebss = &_ebss;

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

void __reset_handler(void) {
    __relocate_vector_table();
    __start();
}

/**
 * @brief Handles return from main
 */
static void __exit(void)
{
    /// returned from the main function. Nothing to do so just sit here
	while(1);
}

/**
 * @brief Handler for all undefined exception handler
 */
void __default_handler(void)
{
    /// default handler for all isr routine
	while(1);
}
