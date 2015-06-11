/** @file startup.h
 *  @brief Startup header file for STM32M4Discovery board.
 *
 *  @author Suraj Deuja
 */

#include "addr.h"
#include "flash.h"
#include "rcc.h"
#include "startup.h"

/// Interrupt vector table
unsigned int INTERRUPT_VECTOR[] __attribute__((section(".isr_vector"))) = {
    (unsigned int) &_estack,
    (unsigned int) reset_handler,
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
void relocate_vector_table(void)
{
        volatile unsigned int * const vtor = (unsigned int *)VTOR_BASE;
        *vtor = (unsigned int)&_isr_vector;
}

void start_sys_clk(void) {
    struct rcc_reg *rcc = (struct rcc_reg *) RCC_BASE;
    struct flash_reg *flash = (struct flash_reg *) FLASH_BASE;

    rcc->cr |= RCC_CR_HSEON; // Enable HSE clock

    while(!(rcc->cr & RCC_CR_HSERDY)); // Wait until the HSE is ready

    rcc->apb1en |= RCC_APB1ENR_PWREN;   // Enable clock for power interface
  //  rcc->cr |= PWR_CR_PMODE;
    rcc->cfgr |= RCC_CFGR_HPRE_DIV1;       // Set prescalars to 1 (168 MHz)
    rcc->cfgr |= RCC_CFGR_PPRE_DIV2;      // Set high speed APB2 prescalar to 2 (84 MHz)
    rcc->cfgr |= RCC_CFGR_PPRE_DIV4;     // Set low speed APB1 prescalar to 4 (42 MHz)
    rcc->pllcfgr |= PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16)| (RCC_PLLCFGR_PLLSRC_HSE) | PLL_Q << 24;

    rcc->cr |= RCC_CR_PLLON;		// Enable PLL

    while(!(rcc->cr & RCC_CR_PLLRDY));	// Wait until PLL ready

    flash->acr = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

    rcc->cfgr &= (unsigned int)~(RCC_CFGR_SW);	// Enable Pll as system clock
    rcc->cfgr |= RCC_CFGR_SW_PLL;

    while((rcc->cfgr & 0xc) != 0x8); // Wait until pll is system clock

}

static void intialize_sections(void)
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

}

/**
 * @brief Handles return from main
 */
static void exit_handler(void)
{
    /// returned from the main function. Nothing to do so just sit here
	while(1);
}

void reset_handler(void) {
    relocate_vector_table();
    intialize_sections();
    start_sys_clk();
    main();
    exit_handler();
}



/**
 * @brief Handler for all undefined exception handler
 */
void default_handler(void)
{
    /// default handler for all isr routine
	while(1);
}
