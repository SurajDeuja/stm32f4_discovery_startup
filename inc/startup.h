/**
 * @file startup.h
 * @brief Startup header file for STM32f4Discovery board
 *
 * @author Suraj Deuja
 */
#ifndef __STARTUP_H
#define __STARTUP_H

/// Some extern variables
extern int _estack;
extern int _sidata;
extern int _sdata;
extern int _edata;
extern int _sbss;
extern int _ebss;
extern int _isr_vector;

/**
 * @brief Enable irq
 */
void enable_irq(void);

/**
 * @brief Disable irq
 */
void disable_irq(void);

/**
 * @brief Main entry point for bootloader
 */
void reset_handler(void);

/**
 * @brief IRQ0 handler
 */
void irq0_handler(void) __attribute((weak, alias("default_handler")));

/**
 * @brief Default handler from all function
 */
void default_handler(void);

/**
 * @brief declaration for user main function
 */
int main(void);

#endif /* End of __STARTUP_H */
