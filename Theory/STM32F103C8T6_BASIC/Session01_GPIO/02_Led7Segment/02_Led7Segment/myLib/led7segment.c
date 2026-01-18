#include "led7segment.h"

/* led cathode chung */
static uint8_t segment_code[] = {  0x3F, // 0
                            0x06, // 1
                            0x5B, // 2
                            0x4F, // 3
                            0x66, // 4
                            0x6D, // 5
                            0x7D, // 6
                            0x07, // 7
                            0x7F, // 8
                            0x6F  // 9
                            };
                             
void led7Segment_Init(led7Segment_Object_t *hLed,
                    led7Segment_GPIO_t segment_a,
                    led7Segment_GPIO_t segment_b,
                    led7Segment_GPIO_t segment_c,
                    led7Segment_GPIO_t segment_d,
                    led7Segment_GPIO_t segment_e,
                    led7Segment_GPIO_t segment_f,
                    led7Segment_GPIO_t segment_g,
                    led7Segment_Type_t type) {

    hLed->type = type;
    hLed->segment[0] = segment_a;
    hLed->segment[1] = segment_b;
    hLed->segment[2] = segment_c;
    hLed->segment[3] = segment_d;
    hLed->segment[4] = segment_e;
    hLed->segment[5] = segment_f;
    hLed->segment[6] = segment_g;                                 
}


void led7Segment_Display(led7Segment_Object_t *hLed, uint8_t number) {
    if (number > 9) {return ;} // nếu lớn hơn số 9 => cần 2 con thì không thể dùng được

    uint8_t data = segment_code[number];

    // cần dịch bit để lấy từng bit xuất ra chứ không xuất 1 lần song song
    // Lý do vì không có định nghĩa xây dựng 1 port 7 bit để có thể xuất ra 1 lần
    // hiện chỉ đang xây dựng thành các chân riêng lẻ

    for(uint8_t i = 0 ; i < 7 ; i++) {
        uint8_t bit = (data >> i) & 0x01; // dịch bit cần ghi xuống vị trí MSB và chỉ giữ lại bit này để xuất ra

        GPIO_PinState state; // biến lưu trạng thái

        if (hLed->type == LED_ANODE) {
            state = bit ? 0 : 1; // kiểm tra và đảo bit để giống với anode chung
        } else {
            state = bit ? 1 : 0; // kiểm tra và đảo bit để giống với cathode chung
        }

        HAL_GPIO_WritePin(hLed->segment[i].port, hLed->segment[i].pin, state);
    }

}
