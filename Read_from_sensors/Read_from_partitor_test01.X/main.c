/* 
 * File:   main.c
 * Author: delli
 * Proj-name
 * Created on May 22, 2019, 3:04 PM
 */

// DEVCFG2
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
// DEVCFG1
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
// DEVCFG0
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#define CONFIG1 (ADC_MODULE_ON | ADC_FORMAT_INTG32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON)
#define CONFIG2 (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON |\
 ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF)
#define CONFIG3 (ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15)
#define CONFIGPORT (ENABLE_AN1_ANA)
#define CONFIGSCAN (SKIP_SCAN_AN0 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 |\
SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 |\
SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 |\
SKIP_SCAN_AN15)
// nella slide le righe vanno a capo, nel codice ogni #define va su un?unica riga
#define SYSCLK 80000000L

#include <p32xxxx.h> // Include PIC32 specifics header file
#include <plib.h> // Include the PIC32 Peripheral Library
void initializeADC(){
    CloseADC10(); // Generally, you should disable the ADC before setup.
    // Use ground as negative reference for channel A instead of pin AN1 (RB1)
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10( CONFIG1, CONFIG2, CONFIG3, CONFIGPORT, CONFIGSCAN);
    // Setup for the ADC10.
    EnableADC10(); // Enables the ADC10.
}

void light_up_leds(int value);
long map(long x, long in_min, long in_max, long out_min, long out_max);

int main(){
SYSTEMConfigPerformance(SYSCLK);
initializeADC(); // Initialize the ADC10

TRISB = 0x0002;
TRISD = 0x0000;
TRISG = 0x0000;

LATD = 0;
LATB = 0;
LATG = 0;
int i;
        
    while(1) // Loop forever
    {
        int dato = ReadADC10(0); // l?argomento della funzione indica
        // la locazione del buffer da leggere

        // il dato va presentato in uscita
//        int value1 = dato*3;
        
        //int value = value >> 7;
        
        int value1 = map(dato, 80, 95, 0, 7);

        //light_up_leds(value);

        for ( i = 0; i <= value1; i++)
        {
            light_up_leds(i);
        }
    }
return 1;
}


void light_up_leds(int value)
{
    static const int character[8] = {
        0x0020, 0x0040, 0x0080, 0x0100,
        0x0800, 0x4000, 0x0200, 0x0100
        /*LED1, LED2, LED3, LED4,
        LED5, LED6, LED7, LED8*/
    };
    
    if (value < 5)
    {
        LATD = character [value];
        LATB = 0;
        LATG = 0;
    }
    else if (value == 5)
    {
        LATB = character [value];
        LATD = 0;
        LATG = 0;
    }
    else if (value > 5 && value < 8)
    {
        LATG = character [value];
        LATD = 0;
        LATB = 0;
    }
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}