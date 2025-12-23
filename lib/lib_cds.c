#include "lib_cds.h"

int fd_cds;

void cds_init(){
    // wiringPiSetup(); 
    if ((fd_cds = wiringPiI2CSetupInterface("/dev/i2c-1", 0x48)) < 0) {
        printf("wiringPiI2CSetupInterface failed:\n");
    }
}

int cds_read(){
    wiringPiI2CWrite(fd_cds, 0x00 | CDS_CH);

    int prev = wiringPiI2CRead(fd_cds);  
    return wiringPiI2CRead(fd_cds);
} 
/*
int main(){
    cds_init();
    while(1){
        printf("cds : %d\n",cds_read());
        delay(500);
    }
}
*/