/** @file usart.h
 * 
 * @author Abderraouf Adjal
 * @brief A header file for "uart.c".
 * @bug No known bugs.
 */

#ifndef USART_H
#define USART_H

/* <util/setbaud.h> require defined F_CPU and BAUD. */
#ifndef F_CPU
# error "F_CPU is NOT defined."
#endif

#ifndef BAUD
# error "BAUD is NOT defined."
#endif

/* Define baud rate tolerance: 2% */
/* #define BAUD_TOL 2 */


/* Enable/Disable USART RX and/or TX. */
#define USART_TX_ENABLED 1
#define USART_RX_ENABLED 0

#define USART_ADD_CARRIAGE_RETURN_CHAR 0

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <util/setbaud.h>


extern void USART_init(void);

extern bool USART_tx_is_ready(void);
extern bool USART_tx_is_transmitted(void);
extern bool USART_rx_is_ready(void);

extern void USART_tx_u8(uint8_t data_u8);
extern uint8_t USART_rx_u8(void);

extern void USART_tx_interrupt_enable(void);
extern void USART_tx_interrupt_disable(void);
extern void USART_rx_interrupt_enable(void);
extern void USART_rx_interrupt_disable(void);

#endif /* USART_H */

/* =================================== EOF ================================== */
