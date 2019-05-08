/* DOESN'T WORK
 * File:   main.c
 * Author: delli
 * Proj-name: external_button_test_01
 * Created on May 1, 2019, 11:27 AM
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

#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.

#define LED1 LATDbits.LATD5
#define LED2 LATDbits.LATD6
#define LED3 LATDbits.LATD7
#define LED4 LATDbits.LATD8
#define LED5 LATDbits.LATD11
#define LED6 LATBbits.LATB14
#define LED7 LATGbits.LATG9
#define LED8 LATGbits.LATG8
#define LED_YELLOW LATDbits.LATD1

void delay(int t) {
   int n = t * 1900; //1900 è un numero ricavato sperimentalmente
   while (n > 0) {
      n--;
   }
}   

void ResetPins ();

int oldButtonState;
int newButtonState;
int unsigned status;

int main(void) {

    TRISD = 0x0000;
    TRISB = 0x0000;
    TRISG = (1<<7);
    //ResetPins();
    LED4 = 1;
    
    while (1)
    {
        LED4 =1;
        delay(100);
        status = LATGbits.LATG7;         // Read the pin
        delay(100);

        if (status)
        {
            ResetPins();
            LED5 = 1;
        }
    }
}

void ResetPins ()
{
        LED1 = 0;      //D3
        LED2 = 0;      //D4
        LED3 = 0;      //D5
        LED4 = 0;      //D6
        LED5 = 0;     //D7
        LED6 = 0;     //D9
        LED7 = 0;      //D10
        LED8 = 0;      //D11
}