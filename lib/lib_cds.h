#ifndef CDS_H
#define CDS_H

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define CDS_CH 0

void cds_init();

int cds_read();


#endif