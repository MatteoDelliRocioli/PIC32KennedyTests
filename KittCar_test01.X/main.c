/* 
 * File:   main.c
 * Author: delli
 * Proj-name: KittCar_test01
 * Created on April 27, 2019, 4:23 PM
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
      //LATBbits.LATB13 = 1;      //D8 BUT DOESN'T WORK //TODO: chiedi a Mauro
void ResetPins ();
void LightUpLeds ();

int pressedButton = 0;
int start = 0;
int end = 0;
int oldButtonState;
int newButtonState;
int firstLedUp = 0;
int lastLedUp = 0;
int ledNumber = 1;

int main(void) {
    /*configure machine*/
    TRISD = (1<<4) | (1<<0); // uso il pulsante BUT2
    TRISB = 0x0000;
    TRISG = 0x0000;
    
    LED_YELLOW = 0;
    ResetPins (0);
    /***/
    
    
    while (1) {
        /*wait button state*/
        if (!pressedButton)
        {
        delay(100);
        newButtonState = !PORTDbits.RD4;
        if (oldButtonState > newButtonState)
        {
            pressedButton =~ pressedButton;
        }
        oldButtonState = !PORTDbits.RD4;
        }
        /***/
        
        /*Control if game has started*/
        if (pressedButton)
        {
            LED_YELLOW =~ LED_YELLOW;    //button pressed, led yellow 
                                                //lights up
            pressedButton =~ pressedButton;
            firstLedUp =~ firstLedUp;
            if (!start)
            {
                start =~ start;
            }
            else
            {
                end =~ end;
            }
        }
        /***/
        
        /*start game*/
        if (firstLedUp)
        {
            ScrollLedsUpwards();
        }
        /***/
        
        /*light from last to first*/
        if (lastLedUp)
        {
            ScrollLedsBackwards();
        }
        /***/
        
        /*end game*/
        if (end)
        {
            ResetPins (0);
            firstLedUp = 0;
            lastLedUp = 0;
        }
        /***/
    }
    return 1;
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

void LightUpLeds ()
{
    switch (ledNumber) {
            
        case 1 : 
            LED1 = 1;
            lastLedUp = 0;
            break;
            
        case 2 :
            LED2 = 1;
            break;
          
        case 3 :
            LED3 = 1;
            break;
          
        case 4 :
            LED4 = 1;
            break;
          
        case 5 :
            LED5 = 1;
            break;
          
        case 6 :
            LED6 = 1;
            break;
          
        case 7 :
            LED7 = 1;
            break;
          
        case 8 :
            LED8=  1;
            //delay(100);
            /*lastLedUp = 1;
            firstLedUp = 0;*/
            break;
                    
        default :
            break;
  }
}

void ScrollLedsUpwards ()
{
    ResetPins();
    LightUpLeds();
    ledNumber++;
    if (ledNumber > 8)
    {
        ledNumber--;
        lastLedUp = 1;
        firstLedUp = 0;
    }
}

void ScrollLedsBackwards ()
{
    ResetPins();
    LightUpLeds();
    ledNumber--;
    if (ledNumber < 1)
    {
        ledNumber++;
        lastLedUp = 0;
        firstLedUp = 1;
    }
}

              //  firstLedUp = 1;
/*     LATDbits.LATD5 = 1;      //D3
       LATDbits.LATD6 = 1;      //D4
       LATDbits.LATD7 = 1;      //D5
       LATDbits.LATD8 = 1;      //D6
       LATDbits.LATD11 = 1;     //D7
       LATBbits.LATB14 = 1;     //D9
       LATGbits.LATG9 = 1;      //D10
       LATGbits.LATG8 = 1;      //D11*/
