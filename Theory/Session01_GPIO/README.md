# GPIO với STM32F103C8T6

[XEM VIDEO](https://www.youtube.com/watch?v=Cc_wOdXHhhI&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=3)

STM32F103C8T6 là kiến trúc ARM Cortex-M3 có khả năng xử lý mạnh mẽ, kết nối các ngoại vi đa dạng, GPIO, tính năng tiết kiệm năng lượng.

## INPUT, OUTPUT

Các chân GPIO: Có chức năng là Input/Output Mode, hoặc các chức năng như UART, I2C, SPI, PWM,...

    1. PORT A

    2. PORT B

    3. PORT C

Để sử dụng các chân GPIO cần dùng thì cần:

    1. Kích hoạt Clock cho GPIO

    2. Cấu hình mode cho chân GPIO

    3. Thiết lập đầu ra (nếu cần)

    4.  Đọc giá trị đầu vào (nếu cần)

## Mode Input Output

### Chế độ GPIO

1. Chế độ Input
    - Floating
        - là trạng thái không phải là mức 1 cũng không phải là mức 0.
    - Full Down
        - chân GPIO đó có 1 điện trở kéo xuống GND để là mức thấp.
    - Full Up
        - chân GPIO đó có 1 điện trở kéo lên VCC để là mức cao.
2. Chế độ Output
    - PushPull
        - là chế độ GPIO có thể xuất ra mức 1 hoặc 0
    - Open Drain
        - là chế độ GPIO chỉ có thể xuất ra mức 0 hoặc Floating
3. Chức năng thay thế
    - UART
    - SPI
    - I2C
    - TIM
4. Chế độ tương tự
    - ADC
    - DAC

## Test Input Output

Để cấu hình cho Clock cho GPIO, làm như sau:

1. Mở phần mềm STM32CuBeMX

2. Chọn Board STM32F103C8T6

3. Chọn vào 1 PORT bất kỳ có thể làm I/O và chọn chức năng cho chân đó là GPIO Input/ GPIO Output

4. Chọn System Core -> GPIO -> Chọn vào chân GPIO -> GPIO Mode -> Output Push Pull để có thể dùng mức 0 và 1 -> GPIO Pull-up /Pull-down -> có thể lựa chọn cấu hình phù hợp

5. Chọn System Core -> RCC để cấu hình Clock cho GPIO

6. Ở tab Pinout & Configuration -> High Speed Clock (HSE) -> Crytal/Ceramic Resonator -> Tab Clock Configuration có input frequence 8 Mhz màu xanh nước.

7. Trong đồ thị ở tab Clock Configuration ô HCLK gõ số 72 nhấn Enter

8. Ở tab Pinout & Configuration, chọn SYS -> Debug -> Serial Wire để cho phép debug qua ST-LINK V2

9. Sau khi Config xong -> Tab Project Manager -> Mục Project -> Chọn vị trí lưu project tại mục Project Location -> Toolchain/IDE -> MDK-ARM (Keil C)

10. Chuyển sang mục Code Generator -> Copy only the necessary library files

11. Sau khi hoàn tất xong chọn GENERATE CODE trên đầu góc phải để tạo Project -> Chọn Open Project sẽ được mở bằng Keil C.

12. Thư mục làm việc là Application/User/Core. File code chính là main.c

## Các API cơ bản

### Để xuất ra 1 tín hiệu ra chân GPIO, dùng API `HAL_GPIO_WritePin();` chuẩn

- Cú pháp:

```c
HAl_GPIO_WritePin(GPIO_PORT, GPIO_PIN_NUMBER, LEVEL);
```

- Trong đó:

  - GPIO_PORT : là PORT chính quản lý của chân GPIO đó

  - GPIO_PIN_NUMBER : là tên chân GPIO trong PORT đó, ví dụ  `GPIO_PIN_0`

  - LEVEL : 0/1 tương ứng xuất mức LOW/HIGH

### Để khai báo, chỉ định mức LOGIC mặc định ban đầu của chân GPIO, ngôaif việc dùng `HAL_GPIO_WritePin();` sau đó chỉ định mức LOGIC là 0/1 (LOW/HIGH), có thể thay bằng

- Cú pháp:

```c
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN_NUMBER, GPIO_PIN_SET);
```

- Trong đó:

  - `GPIO_PIN_SET` tương ứng với mức HIGH (1)

  - `GPIO_PIN_RESET` tương ứng với mức LOW(0)

### Để liên tục thay đổi trạng thái ngõ ra LOW/HIGH tuần tự, dùng API chuẩn `HAL_GPIO_TogglePin();`

- Cú pháp:

```c
HAL_GPIO_TogglePin(GPIO_PORT, GPIO_PIN_NUMBER);
```

- Trong đó:

  - GPIO_PORT: là PORT quản lý của GPIO đó

  - GPIO_PIN_NUMBER: Chân GPIO nào

### Để đọc tín hiệu Digital từ chân GPIO, dùng API `HAL_GPIO_ReadPin();` chuẩn

- Cú pháp:

```c
HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_NUMBER);
```

- Trong đó:

  - GPIO_PORT : là PORT chính quản lý của chân GPIO đó

  - GPIO_PIN_NUMBER : là tên chân GPIO trong PORT đó, ví dụ  `GPIO_PIN_0`

### Để delay 1 khoảng thời gian, dùng API `HAL_Delay()` chuẩn

- Cú pháp:

```c
HAL_Delay(time_ms);
```

- Trong đó:

  - time_ms : thời gian delay, tính bằng mili giây

>## Lưu ý: nên code trong đoạn chú thích USER CODE BEGIN - USER CODE END để khi có config lại thì code cũng không bị mất
