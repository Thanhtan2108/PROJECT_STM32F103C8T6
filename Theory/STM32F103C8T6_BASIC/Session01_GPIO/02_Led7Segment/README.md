# STM32F103C8T6 GIAO TIẾP VỚI LED 7 ĐOẠN

## Tìm hiểu led 7 đoạn

- Led 7 đoạn và ký hiệu của từng thanh

![led 7 segment](./image/led%207%20segment.png)

- Phân loại: có 2 loại

  - Led anode chung: các chân anode của các led nối chung với nhau và nối lên VCC, các chân cathode nối với chân vi điều khiển. Led sáng cần truyền mức 0

  - Led cathode chung: các chân cathode của các led nối chung với nhau và nối xuống GND, các chân anode nối với vi điều khiển. Led sáng cần truyền mức 1

![type led 7 segment](./image/type%20led%207%20segment.png)

- Bảng mã HEX cho các số hiển thị lên led: được chia thành 2 loại:

  - Anode chung:

  ![anode chung](./image/anode%20chung.png)

  - Cathode chung:

  ![cathode chung](./image/cothode%20chung.png)
