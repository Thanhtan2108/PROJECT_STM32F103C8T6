#

[Xem trước ESP32 WEBSERVER](https://www.youtube.com/watch?v=xtUz0yqLyHg&list=PLbQ6BBf-QSJyWDZ-uEsKhF4HFUr-EqsSo)

## Ý tưởng

Có 2 MCU:

- STM32F1103C8T6:

  - Phân vùng bootloader

  - Phân vùng Application

- ESP32 Devkit V1

  - Get file .bin data

File .bin này được buil ra từ project trên laptop

Cứ có kết nối internet, sẽ gửi file .bin cho ESP32

ESP32 UART STM32, cứ có data sẽ cập nhật vào Application

## Chuyển File .hex thành file .bin

Khi build project thì sẽ tạo ra file.hex nhưng mình cần file.bin chỉ chứa data thôi

=> Cần chuyển

Sử dụng command trên windows để chuyển

Mở CMD tại file.hex

```bash
copy -I ihex - O binary <tên file.hex> <tên_file.bin>
```

## Xây dựng Package UART

Vì nếu dùng UART để truyền dữ liệu, nó là cơ chế bất đồng bộ nên rất dễ lỗi đường truyền làm mất data.

Để khắc phục, xây dựng 1 Package gồm:

- bit start

- len

- data

- CRC

Xây dựng thành các Block để truyền, mỗi Block 256 byte, có cơ chế kiểm tra ACK/NACK

## Phần 02

Chủ yếu phát triển cấu hình cho esp32 làm server, gủi được file.bin từ máy tính lên esp32 thông qua internet
