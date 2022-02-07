#include <xc.h>
#include <stdint.h>
#include <htc.h>

//CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000      //pic frequency (Hz)                 

#include "pwm.h"
#include "adc.h"
#include "servo.h"
#include "lcd.h"

void Servocontrol(){
    if(ADC_Read(0) > 500){
        tsSetPulse(300, 19000, 60);
        __delay_ms(1000);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("LIGHT--"); 

    }
    else{
        tsSetPulse(2200, 19000, 60);
        __delay_ms(1000);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("DARK--"); 
    }
}

void main()
{
TRISD = 0x00;
TRISB = 0x00;
TRISC = 0xF9; 
Lcd_Init();
init_ADC();
init_PWM();
 while(1) {
    setPWM_DutyCycle(-ADC_Read(0));
    Servocontrol();
}
}

