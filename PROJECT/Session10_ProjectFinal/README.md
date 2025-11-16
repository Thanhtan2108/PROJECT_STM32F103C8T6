# SẢN PHẨM CUỐI KHÓA

## [XEM VIDEO DEMO](https://www.youtube.com/watch?v=4UB3MfNAUHA&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=26)

- Thực hiện sản phẩm dùng cảm biến HC-SR05 để đo khoảng cách, xác định phạm vi an toàn của vật thể và hiển thị phạm vi an toàn cùng với vật thể lên màn hình TFT, nếu vật thể  tiến vào phạm vi không an toàn thì led sáng (có thể thay bằng buzzer)

- Phạm vi tối đa mà cảm biến HCSR05 đo được trong phạm vi project này là 10cm tuong ứng với 128 pixel trên màn TFT

- Phạm vi an toàn là >= 5cm, và phạm vi không an toàn < 5cm

- Tổng thể Project này dùng các ngoại vi:

  - SPI cho màn TFT

  - GPIO điều khiển LED (buzzer)

  - Timer cho HCSR05 (PSC = 71 => t = 1us)

## Phần 1. Đọc cảm biến HCSR05

### [XEM VIDEO](https://www.youtube.com/watch?v=HnUxZDrn4lw&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=27)

### [XEM DATASHEET](../../Doc/M_HY-SRF05_0003.pdf)

## Phần 2. Hiển thị lên màn TFT

### [XEM VIDEO](https://www.youtube.com/watch?v=JWuUxU5vMd8&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=28)

## Phần 3. Viết thư viện từ source code của 2 phần trước để clean project

### [XEM VIDEO](https://www.youtube.com/watch?v=IA85gALABZA&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=29)

## [XEM CODE](./10_ProjectFinal/Core/Src/main.c)
