#include "lib_seg.h"
#include "lib_buzzer.h"

void* segControl(void *arg){
    printf("seg 라이브러리 동작함\n");
    
    st_seg_data* data = (st_seg_data*)arg;
    
    seg_init();
    buzzer_init();
    while(!(*(data->kill_thread))){
        if(data->start_num == 0) continue;
        else if(data->start_num > 0){
            int num = data->start_num;
            seg_display(num);
            *(data->start_num) = num--;
            delay(1000);
            if(data->start_num == 0){
                buzzer_beep();
                break;
            }
        }
    }
    seg_off();
    *(data->kill_thread) = 0;
    return NULL;
}