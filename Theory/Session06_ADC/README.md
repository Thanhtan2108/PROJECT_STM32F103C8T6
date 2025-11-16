# ADC TRÊN STM32

## [XEM VIDEO](https://www.youtube.com/watch?v=zVqZtW_oYhU&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=15)

## 1. Giới thiệu

- ADC là 1 thành phần quan trọng giúp chuyển đổi tín hiệu analog từ thế giới bên ngoài (ví dụ tín hiệu từ cảm biến) thành tín hiệu số mà VĐK có thể xử lý được

- Độ phân giải

  - Thường đo bằng số bit (8 bit, 10 bit, 12 bit, ...)
  
  - Độ phân giải càng cao, khả năng biểu diễn tín hiệu càng chính xác

- Điện áp tham chiếu

  - Vref = 3.3V (STM32F103C8T6)

- Tốc độ lấy mẫu càng cao thì lấy càng chuẩn

## 2. Code

- Khởi tạo việc bắt đầu đọc tín hiệu ADC

```c
HAL_ADC_Start(&hadc1);
```

- Set timeout cho việc đọc ADC

```c
HAL_ADC_PollForConversion(&hadc1, timeout);
```

- Đọc giá trị ADC từ bên ngoài

```c
HAL_ADC_GetValue(&hadc1);
```

- Kết thúc quá trình đọc ADC

```c
HAL_ADC_Stop(&hadc1);
```

>Việc code bằng các API chuẩn trên chỉ đọc được giá trị ADC tương đối chứ chưa thật sự hoàn toàn chính xác. Muốn chính xác, hãy xem cách code dưới đây để hiệu chỉnh đúng giá trị ADC với lý thuyết thực tế

```c
HAL_ADCEx_Calibration_Start(&hadc1);
```

>Calibration prerequisite: ADC must be disabled (execute this function before HAL_ADC_Start() or after HAL_ADC_Stop() ).

- Sau khi đã đọc được giá trị ADC chính xác, cần Convert sang giá trị số để VĐK xử lý

```c
void ADCToVolt(uint16_t ADCRaw) {
  return (ADCRaw * 3.3) / 4095;
}
```

>Xử lý Convert trước khi Stop ADC

## [XEM CODE](./06_ADC/Core/Src/main.c)
