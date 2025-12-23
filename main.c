#include "lib_seg.h"
#include "lib_cds.h"
#include "lib_led.h"
#include <stdio.h>

int main(){
    wiringPiSetup();
    seg_init();
    led_init();

    seg_off();
    led_write(0, 0);
    led_write(1, 0);
    led_write(2, 0);
}