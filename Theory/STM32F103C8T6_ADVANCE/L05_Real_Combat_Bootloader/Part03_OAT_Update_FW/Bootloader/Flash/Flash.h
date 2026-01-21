#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

void flash_unlock();
void flash_lock();
void flash_erase(uint32_t addr);
void flash_write(uint32_t addr, uint8_t *mData, uint16_t len);
void flash_read(uint32_t addr, uint8_t *mData, uint16_t len);

#endif
