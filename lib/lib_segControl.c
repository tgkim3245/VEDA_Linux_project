#include "lib_seg.h"
#include "lib_buzzer.h"

void* segControl(void *arg){
    printf("seg 라이브러리 동작함\n");
    
    st_seg_data* data = (st_seg_data*)arg;
    
    seg_init();
    buzzer_init();
    while(!(*(data->kill_thread))){
        if(data->start_num == 0){
            delay(100);
            continue;
        }
        while(data->start_num > 0 && !(*(data->kill_thread))){
            seg_display(data->start_num);
            printf("남은 시간: %d\n", data->start_num);
            
            delay(1000); 
            data->start_num--;
            if(data->start_num == 0){
                seg_display(0); 
                printf("시간 종료 부저 \n");
                buzzer_beep();  
            }
        }
    }
    seg_off();
    *(data->kill_thread) = 0;
    return NULL;
}