#include "lib_motor.h"
#include "lib_cds.h"
#include "lib_seg.h"
#define BTN 5

void* motorControl(void* arg){
    printf("motor 라이브러리 동작함\n");
    
    st_motor_data* data = (st_motor_data*)arg;

    pinMode(BTN, INPUT);
    cds_init();
    motor_init();
    seg_init();
    while(!(*(data->kill_thread))){
        if(digitalRead(BTN) == HIGH){
            data->motorRunning ^= 1;
            delay(100); // 채터링 방지
        }
        else if(data->motorRunning) {
            int cds_val = cds_read(); // 240(어두울때) ~ 140(밝을때)
            if(cds_val>240) cds_val  = 240;
            else if(cds_val<140) cds_val = 140;
            int speed = (int)((240-cds_val)*2.55); // 속도 정규화
            motor_speed(speed);
            seg_display((int)(240-cds_val-1)/10);
        }
        delay(10);
    }
    seg_off();
    data->motorRunning = 0;
    *(data->kill_thread) = 0;
    return NULL;
}