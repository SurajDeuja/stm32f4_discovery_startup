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

/**
 * @brief Main entry point for bootloader
 */
void __reset_handler(void);


/**
 * @brief Handles return from main
 */
void __exit(void);


/**
 * @brief IRQ0 handler
 */
void irq0_handler(void) __attribute((weak, alias("__default_handler")));


/**
 * @brief Default handler from all function
 */
void __default_handler(void);


/**
 * @brief declaration for user main function
 */
int main(void);
#endif /* End of __STARTU_H */
