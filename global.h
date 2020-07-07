/** @file global.h
 * 
 * @author Abderraouf Adjal
 * @brief This global header should be always included first.
 * @bug No known bugs.
 */

#ifndef GLOBAL_H
#define GLOBAL_H

/* To make sure the setup is for ATmega328P */
#ifndef __AVR_ATmega328P__
# error "This system is made for ATmega328P."
#endif

/* CPU Frequency in Hz (16 MHz): */
#define F_CPU 16000000UL
#define UNCHANGEABLE_F_CPU 1

#define VCC_V 5
#define ADC_REF_V 5

/* UART baud rate: */
#define BAUD 9600UL

#define NO_INIT_ATTR __attribute__ ((section (".noinit")))
#define ZERO_OPTIMIZE_ATTR __attribute__ ((optimize("O0")))

#ifndef NO_INIT_ATTR
/* NOTE: Because of the Harvard architecture of the AVR devices, manually
 * add 0x800000 to the address you pass to the linker the start of the section.
 * Otherwise, the linker thinks you want to put the .noinit section into
 * the .text section instead of .data/.bss and will complain.
 * - Ref: <https://www.nongnu.org/avr-libc/user-manual/mem_sections.html>
 */
# define NO_INIT_ATTR __attribute__ ((section (".bss")))
#endif

/* Check if compiler conforms to ISO Standard C99 (ISO/IEC 9899:1999) */
#if ((__STDC__ != 1) || (__STDC_VERSION__ != 199901L))
# error "ERROR: STD C != C99"
#endif

/* Prevent random F_CPU modification */
#if ((UNCHANGEABLE_F_CPU == 1) && (F_CPU != 16000000UL))
# error "ERROR: F_CPU expected to be 16000000UL"
#endif

#include <stdint.h>

/* Global error flag structure: [m4 m3 m2 m1  e4 e3 e2 e1] (8-bits)
 * - Each part/module of the system should set one of 'm' bits uniquely.
 * - The error or issue type rised by the part/module
 *   should set one of 'e' bits uniquely.
 */
#define G_ERROR_NONE 0x00U

#define G_ERROR_EEPROM_ADDR 0x10U

#define G_ERROR_USART_UPE 0x20U
#define G_ERROR_USART_DOR 0x21U
#define G_ERROR_USART_FE  0x22U


/* Global flag in ".noinit" memory section. */
NO_INIT_ATTR extern volatile uint8_t g_error_flag;

#endif /* GLOBAL_H */

/* =================================== EOF ================================== */
