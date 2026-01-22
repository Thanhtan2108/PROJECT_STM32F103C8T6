# Phát triển Bootloader và Application để cập nhật OTA

## Khó khăn

Do không dùng chung 1 mức điện áp giữa 2 MCU có 2 nguồn riêng biệt nên việc giao tiếp UART không thực hiện thành công giữa 2 MCU vì chênh lệch mức điện áp

Dùng 2 nguồn riêng biệt có thể dẫn đến không chung GND hoặc GND loop

Chênh lệch điện áp

Nhiễu trên dây RX TX

## Sửa chữa

Dùng chung 1 mức điện áp giữa 2 MCU để giao tiếp UART thành công

## Wiring

| ESP32 | STM32 |
| --- | --- |
| RX2(GPIO16) | PA9(UART1) |
| TX2(GPIO17) | PA10(UART1) |
| GND | GND |
| 3.3V | 3.3V |

> Lưu ý: mức điện áp dùng chung VCC phải bằng mức điện áp trên dây RX TX
