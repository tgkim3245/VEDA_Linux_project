#include "lib_led.h"

void* ledControl(void *arg){
    printf("led 라이브러리 동작함\n");
    
    led_init();
    while(!(((st_led_data*)arg)->kill_thread)){
        int sd = ((st_led_data*)arg)->sd;
        int brightness = ((st_led_data*)arg)->brightness;
        led_pwm('r', brightness);
        delay(100);
    }
    ((st_led_data*)arg)->kill_thread = 0;
    return NULL;
}