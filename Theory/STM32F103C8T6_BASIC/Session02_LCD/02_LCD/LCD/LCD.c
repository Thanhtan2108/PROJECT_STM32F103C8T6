#include "LCD.h"

LCD myLCD;

// xay dung cho cac ham nguyen mau
void LCD_Write_Byte(uint8_t data, uint8_t mode) {
    if (mode == 0x01) { // 1
        // data
        HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.RS, 1); // RS = 1
    } else if (mode == 0x00) { // 0
        // cmd
        HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.RS, 0); // RS = 0
    }

    // ghi data ra chân GPIO
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D0, (data & 0x01) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D1, (data & 0x02) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D2, (data & 0x04) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D3, (data & 0x08) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D4, (data & 0x10) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D5, (data & 0x20) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D6, (data & 0x40) ? 1 : 0);
    HAL_GPIO_WritePin(myLCD.PORT_DATA, myLCD.D7, (data & 0x80) ? 1 : 0);

    // delay 1 khoảng theo datasheet để truyền data
    HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.En, 0);
    HAL_Delay(1);
    HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.En, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.En, 0);
    HAL_Delay(1);
}

void LCD_Write_data(uint8_t data) {
    LCD_Write_Byte(data, 1);
}

void LCD_Write_cmd(uint8_t data) {
    LCD_Write_Byte(data, 0);
}

void LCD_Init() {
		// Allow Read/Write
    HAL_GPIO_WritePin(myLCD.PORT_R, myLCD.RW, 0);	
	
    HAL_Delay(50);
    LCD_Write_cmd(0x38); // set 8 bit 2 lines 5*7 pixels
    HAL_Delay(5);
    LCD_Write_cmd(0x0C); // cursor hidden
    HAL_Delay(5);
    LCD_Write_cmd(0x01); // clear screen
    HAL_Delay(5);
    LCD_Write_cmd(0x06); // display from left to
}

void LCD_Print(char *str) {
    while(*str) { // stop if NULL
        LCD_Write_data(*str++);
    }
}
