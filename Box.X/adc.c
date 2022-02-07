#include <xc.h>
#include <stdint.h>
#include"adc.h"

#define _XTAL_FREQ 20000000
void init_ADC(){
    //------[There are 2 registers to configure ADCON0 and ADCON1]---------
    // ADCON0 = 0x41
    // Select clock option Fosc/8
    ADCS0 = 1;
    ADCS1 = 0;
    // Turn ADC on
    ADON = 1;
    
    //ADCON1 = 0x80
    // Result mode: Right justified
    ADFM = 1;
    // Select clock option Fosc/8
    ADCS2 = 0;
    // Configure all 8 channels are analog 
    PCFG0 = 0;
    PCFG1 = 0;
    PCFG2 = 0;
    PCFG3 = 0;
}

uint16_t ADC_Read(uint8_t ADC_channel){
    // Check channel number
    if(ADC_channel < 0 || ADC_channel > 7)
        return 0;
    
    // Write ADC__channel into register ADCON0
    CHS0 = (ADC_channel & 1) >> 0;
    CHS1 = (ADC_channel & 2) >> 1;
    CHS2 = (ADC_channel & 4) >> 2;
    
    // Wait the Acquisition time 
    __delay_us(25);
    
    // Start A/D conversion
    GO_DONE = 1;
    
    // (Polling) Wait for the conversion to complete
    while(GO_DONE);
    
    // Read the ADC result ("right justified" mode)
    uint16_t result = ((ADRESH << 8) + ADRESL);
    return result;
}