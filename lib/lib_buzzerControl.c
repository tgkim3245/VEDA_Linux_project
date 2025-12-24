#include "lib_buzzer.h"

void* buzzerControl(void *arg){
    printf("lib_buzzer 라이브러리 동작함\n");
    
    st_buzzer_data* data = (st_buzzer_data*)arg;

    buzzer_init();
    while(!(*(data->kill_thread))){
        if(data->musicRunning){
            buzzer_musicPlay(&(data->musicRunning));
        }
    }
    softToneWrite(BUZ_PIN, 0);
    data->musicRunning = 0;
    *(data->kill_thread) = 0;
    return NULL;
}