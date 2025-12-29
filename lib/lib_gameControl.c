#include "lib_game.h"

void* gameControl(void* arg){
    printf("game 라이브러리 동작함\n");
    
    st_game_data* data = (st_game_data*)arg;

    while(!(*(data->kill_thread))){
        if(data->gameRunning){
            game_play(&(data->gameRunning), data->kill_thread);
        }
        else{
            if(digitalRead(BTN_PIN) == HIGH){
                game_init(void* arg);
                delay(50);
            }
            delay(10);
        }
    }
    softToneWrite(BUZ_PIN, 0);
    data->musicRunning = 0;
    led_pwm('r', 0);
    seg_off();
    *(data->kill_thread) = 0;
    return NULL;
}