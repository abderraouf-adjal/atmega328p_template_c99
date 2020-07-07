/** @file usart.c
 * 
 * @author Abderraouf Adjal
 * @brief Project minimal UART API.
 * @bug No known bugs.
 * 
 * TODO:
 *   - Setup C STD IO FILE stream.
 *   - Receiver Error Flags API (G_ERROR_USART*).
 *   - Code docs and comments.
 */

#include "../global.h"
#include "usart.h"


/**
 * @brief Configure USART.
 * @param void.
 * @return void.
 * 
 */
void USART_init(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* USE_2X: If USART has to be configured to run in double speed mode. */
#if USE_2X
    UCSR0A |= 1 << U2X0;
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    /* Clear USART error flags: ATmega328P datasheet (7810D–AVR–01/15) 19.7.4 */
    UCSR0A &= ~(1 << UPE0);
    UCSR0A &= ~(1 << DOR0);
    UCSR0A &= ~(1 << FE0);

    /* (UDREn) flag indicates whether the transmit buffer
     * is ready to receive new data. 
     * 
     * ATmega328P datasheet (7810D–AVR–01/15) 19.6.3:
     * UDREn, For compatibility with future devices, always write
     * this bit to zero when writing the UCSRnA register.
     */
    UCSR0A &= ~(1 << UDRE0);

    /* Set frame format: 8-bit data, 1 stop bit, parity disabled */
    UCSR0C = ((1 << UCSZ01) | (1 << UCSZ00))
           | (0 << USBS0)
           | (0 << UPM00);

    /* Enable/Disable USART RX and/or TX. */
#if (USART_TX_ENABLED == 1)
    UCSR0B |= (1 << TXEN0);
#else
    UCSR0B &= ~(1 << TXEN0);
#endif

#if (USART_RX_ENABLED == 1)
    UCSR0B |= (1 << RXEN0);
#else
    UCSR0B &= ~(1 << RXEN0);
#endif
    } /* ATOMIC_BLOCK End. */
}


inline bool USART_tx_is_ready(void)
{
    return ((UCSR0A & (1 << UDRE0)) ? true : false);
}

inline bool USART_tx_is_transmitted(void)
{
    return ((UCSR0A & (1 << TXC0)) ? true : false);
}

inline bool USART_rx_is_ready(void)
{
    return ((UCSR0A & (1 << RXC0)) ? true : false);
}


inline void USART_tx_u8(uint8_t data_u8)
{
#if (USART_ADD_CARRIAGE_RETURN_CHAR == 1)
    if (data_u8 == '\n') {
        USART_tx_u8('\r');
    }
#endif
    /* Loop until a ready flag. */
    while (USART_tx_is_ready() == false)
    { ; }

    UDR0 = data_u8;
}

inline uint8_t USART_rx_u8(void)
{
    /* Loop until a ready flag. */
    while (USART_rx_is_ready() == false)
    { ; }
    
    /* Check the parity error flag.
     * If parity check is not enabled the UPEn bit will always be read zero.
     * The parity checker is active when the high USART parity mode
     * (UPMn1) bit is set in UCSRnA.
     */
    if (UCSR0A & (1 << UPE0)) {
        g_error_flag |= G_ERROR_USART_UPE;
    }
    /* Check the frame error flag. */
    if (UCSR0A & (1 << FE0)) {
        g_error_flag |= G_ERROR_USART_FE;
    }
    /* Check the data overrun flag. */
    if (UCSR0A & (1 << DOR0)) {
        g_error_flag |= G_ERROR_USART_DOR;
    }

    return UDR0;
}


inline void USART_tx_interrupt_enable(void)
{
    UCSR0B |= (1 << UDRIE0);
}

inline void USART_tx_interrupt_disable(void)
{
    UCSR0B &= ~(1 << UDRIE0);
}

inline void USART_rx_interrupt_enable(void)
{
    UCSR0B |= (1 << RXCIE0);
}

inline void USART_rx_interrupt_disable(void)
{
    UCSR0B &= ~(1 << RXCIE0);
}

/* =================================== EOF ================================== */
