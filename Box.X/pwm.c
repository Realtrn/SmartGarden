#include <xc.h>
#include <stdint.h>
#include"pwm.h"
#define _XTAL_FREQ 20000000  
#define Fpwm 5000
#define ps 4


void init_PWM(){
    // Configure the CCP1 module for PWM operation
    CCP1M2 = 1;
    CCP1M3 = 1;
    // Set CCP1 pin as output
    TRISC2 = 0;
    // Set the Timer2 prescaler value and enable Timer2
    switch(ps){
        case 1: {T2CKPS0 = 0;   T2CKPS1 = 0;    break;}
        case 4: {T2CKPS0 = 1;   T2CKPS1 = 0;    break;}
        case 16: T2CKPS1 = 0;   
    }
    TMR2ON = 1;
    // Set the PWM period 
    PR2 = ((float)(_XTAL_FREQ/Fpwm))/(4*ps)-1;
    // --------[Warning: Check if PR2 value fits in 8-bit register (0-255)]---------]
}

void setPWM_DutyCycle(uint16_t DC){
    // DC means % (Ex: DC = 50 means Duty Cycle = 50%)
    //uint16_t DC = ((float)_XTAL_FREQ/(float)Fpwm)*((float)DC/(float)100)/ps;
    // Write to CCP1CON<5:4>
    CCP1Y = DC & (1<<0);
    CCP1X = DC & (1<<1);
    // Write to CCPR1L register
    CCPR1L = DC >> 2;
}
