/*
Thư viện cho led 7 đoạn
*/

#ifndef LED_7_SEGMENT_H
#define LED_7_SEGMENT_H

#ifdef __cplusplus
extern "C" {
#endif

// include thư viện HAL
#include "stm32f1xx_hal.h"

/*
Chuẩn thư viện cần xây dựng 1 enum dùng để làm kiểu dữ liệu return cho hàm
*/

/*
Các thuộc tính quan trọng của đối tượng
LED 7 đoạn: Chân GPIO, Type
*/
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} led7Segment_GPIO_t;

typedef enum {
    LED_ANODE,
    LED_CATHODE
} led7Segment_Type_t;

/*
Tạo struct chính cho đối tượng gồm các thuộc tính đã được tạo ra
*/ 
typedef struct {
    led7Segment_GPIO_t segment[7];
    led7Segment_Type_t type;
} led7Segment_Object_t;


/*
Khởi tạo hàm Init có chức năng khởi tạo cho đối tượng

- Kiểu dữ liệu trả về của hàm có thể là void hoặc enum đã được xây dựng trước đó

- Tham số truyền vào là đối tượng kiểu struct được xây dựng nhưng là con trỏ, các thuộc tính là các biến dùng để kết nối ban đầu/khởi tạo đối tượng 
*/

void led7Segment_Init(led7Segment_Object_t *hLed,
                    led7Segment_GPIO_t segment_a,
                    led7Segment_GPIO_t segment_b,
                    led7Segment_GPIO_t segment_c,
                    led7Segment_GPIO_t segment_d,
                    led7Segment_GPIO_t segment_e,
                    led7Segment_GPIO_t segment_f,
                    led7Segment_GPIO_t segment_g,
                    led7Segment_Type_t );

/*
Xây dựng hàm Handler để xử lý 1 task cụ thể của đối tượng 

- Tham số truyền vào là con trỏ có kiểu dữ liệu của struct đối tượng được xây dựng ở trên và các tham số phục vụ cần thiết cho hàm thực hiện task
*/

void led7Segment_Display(led7Segment_Object_t *hLed, uint8_t number);

#ifdef __cplusplus
}
#endif

#endif
