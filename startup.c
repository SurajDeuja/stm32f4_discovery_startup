/** @file startup.h
 *  @brief Startup header file for STM32M4Discovery board.
 *
 *  @author Suraj Deuja
 */
#include "reg.h"
#include "startup.h"
#include "rcc.h"
#include "flash.h"

/// Interrupt vector table
unsigned int INTERRUPT_VECTOR[] __attribute__((section(".isr_vector"))) = {
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
 void __relocate_vector_table(void)
{
	__REG(__VTOR) = (unsigned int) &_isr_vector;
}

void __start_sys_clk(void) {
    struct reg_rcc *rcc = (struct reg_rcc *) REG_RCC_ADDR;
    struct flash_reg *flash = (struct flash_reg *) FLASH_BASE;

    rcc->cr |= RCC_CR_HSEON; // Enable HSE clock

    while(!(rcc->cr & RCC_CR_HSERDY)); // Wait until the HSE is ready

    rcc->apb1en |= RCC_APB1ENR_PWREN;   // Enable clock for power interface
    rcc->cr |= PWR_CR_PMODE;
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
}

void __reset_handler(void) {
    __relocate_vector_table();
    __start();
    __start_sys_clk();
    main();
    __exit();
}

/**
 * @brief Handles return from main
 */
void __exit(void)
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
