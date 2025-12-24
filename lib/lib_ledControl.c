#include "lib_led.h"

void* ledControl(void *arg){
    printf("led 라이브러리 동작함\n");
    st_led_data* data = (st_led_data*)arg;

    led_init();
    while(!(data->kill_thread)){
        int sd = data->sd;
        int brightness = data->brightness;
        led_pwm('r', brightness);
        delay(100);
    }
    *(data->kill_thread) = 0;
    return NULL;
}