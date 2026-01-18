#include "Flash.h"

void flash_unlock() {
    HAL_FLASH_Unlock();
}

void flash_lock() {
    HAL_FLASH_Lock();
}

void flash_erase(uint32_t addr) {
    FLASH_EraseInitTypeDef pErase;
    pErase.NbPages = 1;
    pErase.PageAddress = addr;
    pErase.TypeErase = FLASH_TYPEERASE_PAGES;
    uint32_t pError;
    HAL_FLASHEx_Erase(&pErase, &pError);
}

void flash_write(uint32_t addr, uint8_t *mData, uint16_t len) {
    for(uint32_t i = 0 ; i < len ; i += 2) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr + i, *(mData + i) | (uint16_t)(*(mData + i + 1) << 8));
    }
}

void flash_read(uint32_t addr, uint8_t *mData, uint16_t len) {
    for(uint32_t i = 0 ; i < len ; i += 2) {
        volatile uint32_t *address = (volatile uint32_t *)(addr + i);
        uint16_t data_temp = *address;
        mData[i] = (uint8_t)data_temp;
        mData[i + 1] = (uint8_t)(data_temp >> 8);
    }
}