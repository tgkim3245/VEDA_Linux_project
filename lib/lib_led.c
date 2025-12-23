#include "lib_led.h"

int led_pins[3] = {LED_RED_PIN, LED_GREEN_PIN, LED_YELLOW_PIN};

void led_init(){
    // wiringPiSetup(); 
    pinMode(led_pins[LED_RED_IDX], OUTPUT);
    pinMode(led_pins[LED_GREEN_IDX], OUTPUT);
    pinMode(led_pins[LED_YELLOW_IDX], OUTPUT);
    softPwmCreate(led_pins[LED_RED_IDX], 0, 255);
    softPwmCreate(led_pins[LED_GREEN_IDX], 0, 255);
    softPwmCreate(led_pins[LED_YELLOW_IDX], 0, 255);
}

void led_pwm(char color, int duty){
    if (duty<0) duty = 0;
    else if(duty>255) duty = 255;

    int led_idx;
    if(color < 3) led_idx = (int)color;
    else if(color=='r' || color=='R') led_idx = LED_RED_IDX;
    else if(color=='g' || color=='G') led_idx = LED_GREEN_IDX;
    else if(color=='y' || color=='Y') led_idx = LED_YELLOW_IDX;
    else {
        printf("error : led_pwm index error\n");
        return;
    }
    softPwmWrite(led_pins[led_idx], duty);
}

void led_write(char color, int state){
    if(state) led_pwm(color, 255);
    else led_pwm(color, 0);
}
/*
int main()
{
    wiringPiSetup( );      
    led_init();

    for(int k = 0; k<3; k++){
        for(int i = 0; i<256; i++){
            led_pwm(k, i);
            delay(10);
        }
    }
    delay(2000);
    led_write('r', 0);
    led_write('g', 0);
    led_write('y', 0);
    delay(2000);
    led_write('R', 1);
    led_write('G', 1);
    led_write('Y', 1);
    delay(2000);
    return 0;
}
*/