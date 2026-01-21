# BOOTLOADER là gì?

- Là chương trình đầu tiên chạy vào

- Có thể update được FW do mình nạp vào

- Chia làm 2 kiểu chính như sau:

  - Trong quá trình dev:

    - Trong 1 MCU có 1 phân vùng bộ nhớ lưu trữ code là ROM. code là file bin được nạp vào ROM.

    - Sau đó code sẽ được bootloader đọc ra và ghi đè vào phân vùng application để chạy.

  - Trong quá trình product: (OTA)

    - Lưu file bin sẽ được lưu trên cluod/server/laptop nào đó trên internet

    - Dùng MCU nào đó (ESP32 - vai trò như là server) để get dữ liệu file bin này về.

    - Giao tiếp MCU vs ESP32 bằng giao thức nào đó để bootloader đọc được file này, sau đó cập nhật cho application
