#include "lib_led.h"

struct st_led_data{
    int sd;
    int brightness;
};

void* ledControl(void *arg){
    printf("led 라이브러리 동작함\n");
    int sd = ((struct st_led_data*)arg)->sd;
    int brightness = ((struct st_led_data*)arg)->brightness;

    led_init();
    led_pwm('r', brightness);

    return NULL;
}