/** @file eeprom.c
 * 
 * @author Abderraouf Adjal
 * @brief Project minimal EEPROM API.
 * @bug No known bugs.
 */

#include "../global.h"
#include "eeprom.h"


/**
 * @brief Check if EEPROM is ready to use.
 * @param void.
 * @return `true` if EEPROM is ready to use, `false` otherwise.
 */
inline bool EEPROM_is_ready(void)
{
    if ((EECR & (1 << EEPE)) || (SPMCSR & (1 << SELFPRGEN))) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Read 8-bits from internal EEPROM.
 * @param address_u16: uint16_t variable.
 * @return An uint8_t from internal EEPROM.
 */
inline uint8_t EEPROM_read_u8(uint16_t address_u16)
{
    /* Check against non-existing EEPROM address. */
    if (address_u16 >= EEPROM_SIZE) {
        g_error_flag |= G_ERROR_EEPROM_ADDR;
        return 0xFF;
    }

    /* Wait for previous operation completion without disabling interrupts. */
    while (EEPROM_is_ready() == false)
    { ; }
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        /* A loop incase of EEPROM usage before the ATOMIC_BLOCK */
        while (EEPROM_is_ready() == false)
        { ; }
        EEAR = address_u16;
        EECR |= (1 << EERE); /* Trigger the EEPROM read. */
    } /* ATOMIC_BLOCK End. */
    return EEDR;
}

/**
 * @brief Write 8-bits in internal EEPROM.
 * @param address_u16: uint16_t variable.
 * @param data_u8: uint8_t variable.
 * @return void.
 */
inline void EEPROM_write_u8(uint16_t address_u16, uint8_t data_u8)
{
    /* Check against non-existing EEPROM address. */
    if (address_u16 >= EEPROM_SIZE) {
        g_error_flag |= G_ERROR_EEPROM_ADDR;
        return ;
    }

    /* Wait for previous operation completion without disabling interrupts. */
    while (EEPROM_is_ready() == false)
    { ; }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        /* A loop incase of EEPROM usage before the ATOMIC_BLOCK */
        while (EEPROM_is_ready() == false)
        { ; }
        EEAR = address_u16;
        EEDR = data_u8;
        EECR |= (1 << EEMPE);
        EECR |= (1 << EEPE);
    } /* ATOMIC_BLOCK End. */
}

/**
 * @brief Only if content differ write 8-bits in internal EEPROM.
 * @param address_u16: uint16_t variable.
 * @param data_u8: uint8_t variable.
 * @return void.
 */
inline void EEPROM_update_u8(uint16_t address_u16, uint8_t data_u8)
{
    /* Check against non-existing EEPROM address. */
    if (address_u16 >= EEPROM_SIZE) {
        g_error_flag |= G_ERROR_EEPROM_ADDR;
        return ;
    }

    /* Wait for previous operation completion without disabling interrupts. */
    while (EEPROM_is_ready() == false)
    { ; }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        /* A loop incase of EEPROM usage before the ATOMIC_BLOCK */
        while (EEPROM_is_ready() == false)
        { ; }
        EEAR = address_u16;
        EECR |= (1 << EERE); /* Trigger the EEPROM read. */
        
        if (EEDR != data_u8) {
            /* Check if EEPROM is ready for write. */
            while (EEPROM_is_ready() == false)
            { ; }

            EEAR = address_u16;
            EEDR = data_u8;
            EECR |= (1 << EEMPE);
            EECR |= (1 << EEPE);
        }
    } /* ATOMIC_BLOCK End. */
}

/* =================================== EOF ================================== */
