#include <xc.h>
#include <stdint.h>
#include <htc.h>
#include "servo.h"
#define _XTAL_FREQ 20000000  


void tsDelay(int d)
{
 int delay = d/5;
 while(delay-->0)
  __delay_us(1); 
}

void tsSetPulse(int p1, int p2, int freq)
{
 while(freq-->0)
 {
  RB3 = 1;
  tsDelay(p1);
  RB3 = 0;
  tsDelay(p2);
 }
}

void tsCenterize()
{
 for(int f=0; f<60; f++)
 {
  RB3 = 1;
  __delay_us(1500);
  RB3 = 0;
  __delay_us(18500);
 }
}

void tsSetPosPercent(int percent, int freq)
{
 int delay1 = percent * 12 + 1000;
 int delay2 = 20000 - delay1;
 tsSetPulse(delay1, delay2, freq);
}
