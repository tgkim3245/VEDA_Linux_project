#include "lib_cds.h"
#include "lib_led.h"

void* cdsControl(void* arg){
    printf("cds 라이브러리 동작함\n");
    
    st_cds_data* data = (st_cds_data*)arg;

    led_init();
    cds_init();
    while(!(*(data->kill_thread))){
        int sd = data->sd;
        // int brightness = data->brightness;
        if(cds_read()>200){
            led_pwm('r', 255);
        }
        else{
            led_pwm('r', 0);
        }
        delay(10);
    }
    led_pwm('r', 0);
    *(data->kill_thread) = 0;
    return NULL;
}