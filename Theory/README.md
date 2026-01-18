# Memory Map I/O của STM32F103C8T6

Đây là lộ trình học tập từ A đến Z cùng với tất cả tài liệu chính thức từ STMicroelectronics (ST) và các nguồn tham khảo uy tín khác.

## Bước 1: Hiểu Tổng Quan về STM32F103C8T6 (Blue Pill)

Trước tiên, cần biết rõ vi điều khiển mình đang học:

- Dòng sản phẩm: STM32F1 Series, cụ thể là dòng Hiệu năng Thường (Performance Line).

- Nhân: ARM Cortex-M3.

- Flash: 64 KB (thực tế STM32F103C8T6 có 128KB, nhưng chỉ 64KB được công bố chính thức).

- SRAM: 20 KB.

- Clock: Tối đa 72 MHz.

## Bước 2: Tải Tài Liệu Chính Thức từ ST

Tất cả tài liệu dưới đây đều có sẵn trên trang chủ của ST. Có thể tìm kiếm bằng mã sản phẩm `STM32F103C8T6` hoặc `STM32F103x8/B`.

### 1. Datasheet (Tài liệu sản phẩm)

Tên tài liệu: STM32F103x8/B Datasheet (DS5319)

Nội dung: Cung cấp thông tin về chân, điện áp, dòng điện, đặc tính điện và package.

[Link tải: STM32F103x8/B Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)

### 2. Reference Manual (Sổ tay tham khảo - Tài liệu QUAN TRỌNG NHẤT)

Tên tài liệu: STM32F10x Reference Manual (RM0008)

Nội dung: Mô tả chi tiết tất cả các thanh ghi, bộ nhớ, ngoại vi và cách lập trình. Đây là tài liệu "gối đầu giường" cho bất kỳ lập trình viên STM32 nào.

[Link tải: STM32F10x Reference Manual](https://www.keil.com/dd/docs/datashts/st/stm32f10xxx.pdf)

### 3. Programming Manual (Sổ tay lập trình)

Tên tài liệu: Cortex-M3 Technical Reference Manual (của ARM) và STM32F10x Programming Manual (PM0056)

Nội dung: Giải thích tập lệnh, kiến trức bộ nhớ chung của Cortex-M3 và các hướng dẫn lập trình cụ thể cho STM32F10x.

Link tải:

[Cortex-M3 Technical Reference Manual](https://documentation-service.arm.com/static/5e8e107f88295d1e18d34714?token=)

[STM32F10x Programming Manual](https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortexm3-programming-manual-stmicroelectronics.pdf)

### 4. Errata Sheet (Tài liệu lỗi)

Tên tài liệu: STM32F103x8/B Errata Sheet (ES0172)

Nội dung: Liệt kê các lỗi đã biết của chip và cách khắc phục.

[Link tải: STM32F103x8/B Errata Sheet](https://www.st.com/resource/en/errata_sheet/es096-stm32f101x8b-stm32f102x8b-and-stm32f103x8b-mediumdensity-device-limitations-stmicroelectronics.pdf)

## Bước 3: Hiểu về Memory Map I/O

**Khái niệm**: Memory Map I/O là phương pháp ánh xạ các thanh ghi điều khiển ngoại vi (như GPIO, UART, SPI,...) vào không gian địa chỉ bộ nhớ. Điều này cho phép ta đọc/ghi các thanh ghi này giống như đọc/ghi bộ nhớ thông qua con trỏ.

**Trong STM32F103C8T6**:

- Không gian địa chỉ bộ nhớ là 4GB (32-bit).

- Các ngoại vi được ánh xạ vào các vùng địa chỉ cụ thể, chủ yếu nằm trong khoảng `0x40000000` đến `0x5FFFFFFF` (Peripheral Bus).

**Cách tra cứu Memory Map**:

- Mở Reference Manual (RM0008).

- Tìm Chương 4: Memory Map (trang 34 trong bản Rev 20).

  - Hình 11: Memory map cho biết địa chỉ bắt đầu của mỗi ngoại vi.

  - Ví dụ: `GPIO Port A (GPIOA)` có địa chỉ cơ sở là `0x40010800`.

- Với mỗi ngoại vi, tra **Chương tương ứng** để biết chi tiết các thanh ghi.

  - Ví dụ: `GPIO` có các thanh ghi như `GPIOx_CRL`, `GPIOx_CRH`, `GPIOx_IDR`, `GPIOx_ODR`, v.v.

  - Offset của mỗi thanh ghi so với địa chỉ cơ sở được cho trong bảng thanh ghi.

## Bước 4: Học Cách Truy Cập Thanh Ghi bằng C

Ví dụ: Bật chân `PA5` (LED trên board Blue Pill thường nối vào `PA5`).

### 1. Tìm địa chỉ thanh ghi

- `GPIOA base address`: `0x40010800` (theo Memory Map).

- `GPIOx_CRL offset`: `0x00` (`thanh ghi cấu hình chân 0-7`).

`GPIOx_ODR offset`: `0x0C` (`thanh ghi xuất dữ liệu`).

Vậy:

- Địa chỉ `GPIOA_CRL` = `0x40010800` + `0x00` = `0x40010800`

- Địa chỉ `GPIOA_ODR` = `0x40010800` + `0x0C` = `0x4001080C`

### 2. Khai báo con trỏ

```c
#define GPIOA_CRL (*(volatile uint32_t *)(0x40010800))
#define GPIOA_ODR (*(volatile uint32_t *)(0x4001080C))
```

### 3. Lập trình

- Cấu hình `PA5` là đầu ra (trong `GPIOA_CRL`).

- `Set (1/HIGH)`  hoặc `reset (0/LOW)` `bit 5` trong `GPIOA_ODR` để `bật/tắt` LED.

Code mẫu:

```c
#include <stdint.h>

// Định nghĩa địa chỉ thanh ghi
#define GPIOA_BASE 0x40010800UL
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

#define RCC_BASE 0x40021000UL
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

int main(void) {
    // Bật clock cho GPIOA
    RCC_APB2ENR |= (1 << 2);

    // Cấu hình PA5 là đầu ra tổng quát (push-pull, tốc độ 2 MHz)
    GPIOA_CRL &= ~(0xF << (5 * 4)); // Xóa cấu hình cũ
    GPIOA_CRL |= (0x1 << (5 * 4));  // Output mode, max speed 10 MHz
    GPIOA_CRL &= ~(0x2 << (5 * 4)); // General purpose output push-pull

    while (1) {
        GPIOA_ODR ^= (1 << 5); // Đảo trạng thái PA5
        for (int i = 0; i < 1000000; i++); // Delay đơn giản
    }
}
```

- Giải thích chi tiết từng thành phần trong code STM32 này và lý do phải dùng các thanh ghi cụ thể:

  - **1. Clock Configuration (RCC - Reset and Clock Control)**

  ```c
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  ```

  - Tại sao phải bật clock?

    - STM32 có kiến trúc clock gating - tất cả ngoại vi đều bị tắt clock mặc định để tiết kiệm năng lượng

    - Không bật clock thì: GPIOA sẽ không hoạt động, mọi thao tác với GPIOA đều không có tác dụng

    - Quan hệ với thanh ghi: Lệnh này ghi vào thanh ghi RCC_APB2ENR (APB2 Peripheral Clock Enable Register)

  - **2. GPIO Configuration Structure**

  ```c
  GPIO_InitTypeDef GPIO_InitStruct;
  ```

  - Các thành phần và thanh ghi tương ứng:

    - **GPIO_Pin = GPIO_Pin_5**

      - Chọn chân PA5 (Pin 5 của Port A)

      - Thanh ghi tương ứng: `GPIOx_CRL` hoặc `GPIOx_CRH` (Configuration Register)

      - Không cấu hình thì: Không biết chân nào được cấu hình

    - **GPIO_Mode = GPIO_Mode_Out_PP**

      - Chế độ `Output Push-Pull`

      - Thanh ghi tương ứng: `2 bits` trong `GPIOx_CRL/CRH` (`CNF[1:0]` và `MODE[1:0]`)

      - Giá trị: `CNF=00`, `MODE=01` (2MHz)

      - Không cấu hình thì: `Chân ở chế độ mặc định` (thường là `Input floating`)

    - **GPIO_Speed = GPIO_Speed_2MHz**

      - Tốc độ chuyển mức `2MHz`

      - Thanh ghi tương ứng: Cùng `2 bits` `MODE[1:0]` trong `GPIOx_CRL/CRH`

      - Không cấu hình thì: `Tốc độ không xác định`, có thể gây vấn đề về `EMC`

  - **3. GPIO Initialization**

  ```c
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  ```

  - Hàm này thực hiện:

    - Đọc thanh ghi cấu hình hiện tại

    - Xóa bits cần thay đổi

    - Set bits mới theo cấu hình

    - Ghi lại thanh ghi

  - **4. GPIO Write Operation**

  ```c
  GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
  ```

  - Thanh ghi tương ứng:

    - `ODR` (Output Data Register): `Ghi trực tiếp giá trị output`

    - `BSRR` (Bit Set/Reset Register): `Set/reset từng bit` an toàn hơn

    - Không dùng thì: `Không thể thay đổi trạng thái chân PA5`

  - **5. Tổng quan về quan hệ các thanh ghi:**

  ```text
  RCC_APB2ENR (Clock Control)
       ↓
  GPIOA được cấp clock
       ↓
  GPIOA_CRL/CRH (Configuration)
       ↓
  GPIOA_ODR/BSRR (Data Output)
       ↓
  Chân PA5 thay đổi trạng thái
  ```

## Bước 5: Sử dụng thư viện chuẩn của ST (STM32 Standard Peripheral Library) hoặc HAL

Để lập trình dễ dàng hơn, ST cung cấp `thư viện chuẩn (Standard Peripheral Library)` và `thư viện HAL (Hardware Abstraction Layer)`.

- `Standard Peripheral Library (SPL)`: Thư viện cũ, nhưng rất phù hợp để học vì gần với thanh ghi.

  - Tải về: STM32F10x Standard Peripheral Library

- `HAL/LL`: Thư viện mới, được dùng với `STM32CubeMX`.

  - Tải về: STM32CubeF1

Ví dụ với `Standard Peripheral Library`:

```c
#include "stm32f10x.h"

int main(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    // Bật clock cho GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Cấu hình PA5
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    while (1) {
        GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
        Delay(500000);
        GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
        Delay(500000);
    }
}
```

Ví dụ với `HAL`:

```c
#include "stm32f1xx_hal.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // led default HIGH, active LOW

  while (1) {
    // Blink LED on-board
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);  // Toggle state
    HAL_Delay(500); // Delay 500ms
  }
}

// Hàm cấu hình System Clock (thường được sinh tự động bởi CubeMX)
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Cấu hình HSE/HSI, PLL, v.v.
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  // Cấu hình clock cho CPU, AHB, APB1, APB2
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void) {
  // Khai báo biến toàn cục cho handle GPIO
  GPIO_InitTypeDef GPIO_InitStruct = {0};

   // Bật clock cho GPIO
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Reset chân về trạng thái ban đầu lý tưởng (0/LOW)
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  // Cấu hình chân GPIOA 13 (PA13)
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void Error_Handler(void) {
  __disable_irq();
  while (1) {
  
  }
}
```

Ví dụ với `LL`:

```c
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"

// Hàm delay đơn giản (blocking delay)
void Delay(uint32_t count) {
    for(volatile uint32_t i = 0; i < count; i++);
}

int main(void) {
    // Cấu hình System Clock (ví dụ đơn giản, dùng HSI 8MHz)
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_SetSystemCoreClock(8000000);  // 8MHz
    
    // Bật clock cho GPIOA
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    
    // Cấu hình PA5
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_NO);
    
    while (1) {
        // Bật LED - SET bit
        LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
        Delay(500000);
        
        // Tắt LED - RESET bit
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
        Delay(500000);
        
        // Hoặc có thể dùng hàm toggle
        // LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        // Delay(500000);
    }
}

// Phiên bản sử dụng LL_Delay (nếu có Systick)
int main_LL_Delay(void) {
    // Khởi tạo Systick cho LL_Delay
    LL_InitTick(8000000, 1000);  // 8MHz, 1ms tick
    
    // Bật clock cho GPIOA
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    
    // Cấu hình PA5
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_LOW);
    
    while (1) {
        // Toggle LED
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        LL_mDelay(500);  // Delay 500ms sử dụng LL
    }
}
```

## Bước 6: Thực Hành và Mở Rộng

### 1. Thực hành

- Viết chương trình `nháy LED` bằng cách `truy cập trực tiếp thanh ghi`.

- `Đọc trạng thái nút nhấn` (ví dụ PA0) bằng `thanh ghi IDR`.

- `Cấu hình các ngoại vi` khác như `UART`, `SPI`, `I2C`, `ADC` bằng `thanh ghi`.

### 2. Công cụ

- `STM32CubeMX`: Công cụ `cấu hình ngoại vi` và `sinh code` cho cấu hình.

- `IDE`: `Keil uVision`, `STM32CubeIDE`, `PlatformIO`.

- `Debugger`: `ST-Link`, `J-Link`.

### 3. Tài liệu bổ sung

- `Application Notes (AN)`: Các ghi chú ứng dụng cụ thể.

- `User Manual (UM)`: Hướng dẫn sử dụng board mạch.

- `Community`: Diễn đàn ST, Stack Overflow.
