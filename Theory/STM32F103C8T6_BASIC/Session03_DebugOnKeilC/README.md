# DEBUG TRÊN KEIL C

[XEM VIDEO](https://www.youtube.com/watch?v=0IR7PS6K8GE&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=8)

>## Để debug được trên Keil C, cần cắm mạch nạp ST-Link vào cổng COM trên laptop

## Kết nối như mô tả và phải có driver cho ST-Link thì mới debug được, driver này chính là driver cài dùng để nạp được code

- Đèn báo trên ST-Link sẽ nháy xanh nước và đỏ liên tục để báo hiệu chế dộ debug

## Quy trình Debug

- Đầu tiên, cần phải build code

- Nạp code xuống board

- Sau đó, nhấn vào biểu tượng debug (kính lúp có chữ d nhỏ màu đỏ) hoặc nhấn Ctrl + F5

- Để kiểm tra xem chương trình trong main() có nhảy vào hàm được gọi không, đặt 1 breakpoint ngay chỗ xây dựng function được gọi và run, nếu mũi tên trỏ đến hàm thì hàm được gọi thành công.

- Muốn xem giá trị của 1 biến để debug, chuột phải vào biến đó -> chọn Add "biến" to... -> Watch 1 (Lưu ý: chỉ có thể debug các biến global, không thể debug các biến được khai báo trong hàm)

- Mặc định giá trị biến debug là HEX, có thể chuyển sang DEC để dễ quan sát bằng cách chuột phải vào biến đó trong Watch 1, bỏ tích HEX.

- Để degub xem giá trị thanh ghi của các GPIO, chọn tab Peripherals -> System Viewer -> GPIO -> GPIO_PORT, 1 bảng thanh ghi xủa GPIO hiện ra, muốn debug thì nhấn run sẽ hiện giá trị.

- Quan sát thanh ghi ODR, đây là thanh ghi OUTPUT của chân GPIO, nếu có tick thì là mức cao, không tick thi mức thấp

>### Nếu gặp lỗi không thể mở để debug thanh ghi, [XEM VIDEO FIX LỖI](https://www.youtube.com/watch?v=t9i8EaXvIcA&list=PLbQ6BBf-QSJyMTHJihioiEOWs-FG2YxXa&index=9)
