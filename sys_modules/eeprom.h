/** @file eeprom.h
 * 
 * @author Abderraouf Adjal
 * @brief A header file for "eeprom.c".
 * @bug No known bugs.
 */

#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/atomic.h>

/* ATmega328P EEPROM size: 1024 byte. */
#define EEPROM_SIZE 1024U
#define EEPROM_PAGE_SIZE 4U
#define EEMEM_ATTR __attribute__((section(".eeprom")))

extern bool EEPROM_is_ready(void);
extern uint8_t EEPROM_read_u8(uint16_t address_u16);
extern void EEPROM_write_u8(uint16_t address_u16, uint8_t data_u8);
extern void EEPROM_update_u8(uint16_t address_u16, uint8_t data_u8);

#endif /* EEPROM_H */

/* =================================== EOF ================================== */
