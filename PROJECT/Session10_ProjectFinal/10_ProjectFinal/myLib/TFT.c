#include "TFT.h"

extern SPI_HandleTypeDef hspi1;

// Send CMD
void TFT_writeCMD(uint8_t cmd) {
  HAL_GPIO_WritePin(PORT_CS, PIN_CS, 0); // CS = 0
  HAL_GPIO_WritePin(PORT_A0, PIN_A0, 0); // A0 = 0 => gui CMD
  HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000);
  HAL_GPIO_WritePin(PORT_CS, PIN_CS, 1); // CS = 1
}

// Send Data
void TFT_writeData(uint8_t data) {
  HAL_GPIO_WritePin(PORT_CS, PIN_CS, 0); // CS = 0
  HAL_GPIO_WritePin(PORT_A0, PIN_A0, 1); // A0 = 1 => gui Data
  HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
  HAL_GPIO_WritePin(PORT_CS, PIN_CS, 1); // CS = 1
}

// gui cmd, so luong data tuong ung voi cm, gia tri data
void sendCMDList(const uint8_t *cmdList) {
  uint8_t index = 0;
  uint8_t cmd = 0;
  uint8_t num = 0;

  // lay cmd tuong ung, xac dinh so luong data can gui, gui so luong data tuong ung
  // su dung kien thuc ve con tro, di chuyen con tro trong mang
  while(1) {
    cmd = *cmdList++;
    num = *cmdList++;
    if(cmd == LCD_CMD_END) {
      break;
    } else {
      TFT_writeCMD(cmd);
      for(index = 0 ; index < num ; index++) {
        TFT_writeData(*cmdList++);
      }
    }
  }
}

// set column, row of TFT
void TFT_setPosition(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  // row
  TFT_writeCMD(0x2A);
  TFT_writeData(0x00);
  TFT_writeData(x1);
  TFT_writeData(0x00);
  TFT_writeData(x2);

  // column
  TFT_writeCMD(0x2B);
  TFT_writeData(0x00);
  TFT_writeData(y1);
  TFT_writeData(0x00);
  TFT_writeData(y2);
}

// hien thi mau RGB - 565 - len man hinh
void TFT_fullDisplay(uint16_t color) {
  TFT_writeCMD(0x2C); // write data into RAM of TFT
  int i;
  for(i = 0 ; i < 128*160 ; i++) {
    TFT_writeData(color & 0xFF); // gui 8 bit thap truoc
    TFT_writeData(color >> 8); // gui 8 bit cao
  }
}

// ve pixe len man TFT
void drawPixel (uint8_t x, uint8_t y, uint16_t color) {
  if(x >= 128 || y >= 160) {
    return;
  }
  TFT_setPosition(x, y, x+1, y+1);
    // truy cap vao RAM
    TFT_writeCMD(0x2C);
    // Ve 1 pixel
    TFT_writeData(color & 0xFF);
    TFT_writeData(color >> 8);
}

// Init TFT
void TFT_Init() {
  // Reset Hardware
  HAL_GPIO_WritePin(PORT_RESET, PIN_RESET, 0);
  HAL_Delay(20);
  HAL_GPIO_WritePin(PORT_RESET, PIN_RESET, 1);
  HAL_Delay(200);

  // Reset SW
  TFT_writeCMD(0x01);
  HAL_Delay(200);
  // Sleep Out
  TFT_writeCMD(0x11);
  HAL_Delay(200);

  // gui cmd va data tuong ung
  sendCMDList(u8IntCmdList);

  // Memory Data Access Control
  TFT_writeCMD(0x36);
  // write data
  TFT_writeData(0x08);

  // Interface Pixel Format
  TFT_writeCMD(0x3A);
  // write data
  TFT_writeData(0x05);

  // Display inversion off
  TFT_writeCMD(0x20);

  // set kich thuoc muon hien thi tren man hinh
  TFT_setPosition(0,0,128,160);

  // Enable Display
  TFT_writeCMD(0x29);
  HAL_Delay(100);
}

// ve ban do len man hinh
void drawMap() {
  for(uint8_t x = 0 ; x < 128 ; x++) { // ve vien ben ngoai
    drawPixel(x, 0, 0x001F); // vien tren mau xanh la
    drawPixel(x, 159, 0x001F); // vien duoi mau xanh la
  }

  for(uint8_t y = 0 ; y < 160 ; y++) { // ve vien ben ngoai
    drawPixel(0, y, 0x001F); // vien trai mau xanh la
    drawPixel(127, y, 0x001F); // vien phai mau xanh la
  }

  // ve mau nen
  for(uint8_t x = 1; x < 127 ; x++) {
    for(uint8_t y = 1 ; y < 159 ; y++) {
      if(x < 64) { // nua man ben trai mau den
        drawPixel(x, y, 0x0000);
      } else { // nua ma ben phai mau trang
        drawPixel(x, y, 0xFFFF);
      }
    }
  }
}

// ve doi tuong diem anh tren man hinh tuong trung cho vat the
void drawBlinkingPoint(uint8_t x, uint8_t y){
  static uint8_t lastX = 2;
  static uint8_t lastY = 80;

  if(x == 0 || x == 127 || y == 0 || y == 159) {
    return;
  }

  uint16_t oldColor = (lastX < 64) ? 0x0000 : 0xFFFF;

  // tao 1 diem anh bang 5 pixel va clear diem anh cu di
  for(int dx = -2 ; dx <= 2 ; dx++) {
    for(int dy = -2 ; dy <= 2 ; dy++) {
      drawPixel(lastX + dx, lastY + dy, oldColor);
    }
  }

  uint16_t newColor = 0xF800; // mau do

  // tao diem anh moi o vi tri khac
  for(int dx = -2 ; dx <= 2 ; dx++) {
    for(int dy = -2 ; dy <= 2 ; dy++) {
      drawPixel(x + dx, y + dy, newColor);
    }
  }

  // bat LED (buzzer) canh bao neu vao vung den - vung khong an toan
  if (x <= 64) {
    HAL_GPIO_WritePin(PORT_LED, PIN_LED, 1);
  } else {
    HAL_GPIO_WritePin(PORT_LED, PIN_LED, 0);
  }

  // cap nhat lai vi tri cho diem anh
  lastX = x;
  lastY = y;
}
