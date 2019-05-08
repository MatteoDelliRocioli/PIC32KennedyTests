/* 
 * File:   main.c
 * Author: delli
 * Proj-name: timer_test_01
 * Created on May 1, 2019, 4:17 PM
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

#define SYSCLK 80000000L // Give the system?s clock frequency

void delay(int t) {
   int n = t * 1900; //1900 è un numero ricavato sperimentalmente
   while (n > 0) {
      n--;
   }
}   
      //LATBbits.LATB13 = 1;      //D8 BUT DOESN'T WORK //TODO: chiedi a Mauro

void ControlAllPins (int unsigned n);

int pressedButton = 0;
int start = 0;
int end = 0;
int oldButtonState;
int newButtonState;
int firstLedUp = 0;
int lastLedUp = 0;
int ledNumber = 0;
int gameNumber = 0;
int i, oldNumber = 0;
int unsigned kit = 0;
int unsigned collision = 0;
int n = 0;

int main(void) {
    /*configure machine*/
    TRISD = (1<<4) | (1<<0); // uso il pulsante BUT2
    TRISB = 0x0000;
    TRISG = 0x0000;

    LED_YELLOW = 0;
    /***/
    ControlAllPins(0);
    SYSTEMConfigPerformance(SYSCLK);
    TRISD = 0x0000;
    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_256, 0xFFFF);
    ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2);
    // This statement configured the timer to produce an interrupt with a priority of 2
    INTEnableSystemMultiVectoredInt();
    // Use multi-vectored interrupts
    while( 1)
    {

    }
    return 1;
}

// Timer2 Interrupt Service Routine
void __ISR(_TIMER_2_VECTOR, ipl2) handlesTimer2Ints(void){
// **make sure iplx matches the timer?s interrupt priority level
/*n =~ n;
ControlAllPins(0);*/
    LED1 =~ LED1;
mT2ClearIntFlag();
// Clears the interrupt flag so that the program returns to the main loop
} // END Timer2 ISR

void ControlAllPins (int unsigned n)
{
        LED1 = n;      //D3
        LED2 = n;      //D4
        LED3 = n;      //D5
        LED4 = n;      //D6
        LED5 = n;     //D7
        LED6 = n;     //D9
        LED7 = n;      //D10
        LED8 = n;      //D11
}
