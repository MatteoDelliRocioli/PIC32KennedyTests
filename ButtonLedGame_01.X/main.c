/* 
 * File:   main.c
 * Author: delli
 * Proj-name: ButtonLedGame_01
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
void CheckButton();
void ResetPins();
void LightUpLeds();
void KitCarEffect();
void ScrollLedsBackwards();
void KitCar();

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
        CheckButton(); //IT'S NOT PRECISE, MULTIPLE BUTTON PRESSURES NEEDED
        if (kit)
        {
            KitCarEffect();
            CheckButton();
        }
        
        if (collision)
        {
            Collision();
            CheckButton();
        }
    }
}

void CheckButton()
{
    //delay(50);
    newButtonState = !PORTDbits.RD4;
    if (oldButtonState > newButtonState)
    {
        gameNumber++;
        ResetPins();
        /*choose game*/
        switch(gameNumber)
        {
            case 1:
                kit = 1;
                break;
            case 2:
                kit = 0;
                collision = 1;
                break;
            default:
                ResetPins();
                collision = 0;
                gameNumber = 0;
                delay(1000);
                break;
        }
        /***/
    }
    oldButtonState = !PORTDbits.RD4;
    /***/
}

void ResetPins()
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

void LightUpLeds()
{
    switch (ledNumber) {
            
        case 1 : 
            LED1 = 1;
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
            break;
                    
        default :
            break;
  }
}

void KitCarEffect()
{
    for (i = 0; i<=8; i++)
    {
        ledNumber = i;
        LightUpLeds();
        delay(50);
        ResetPins();
    }
    for (i = 8; i>=1; i--)
    {
        ledNumber = i;
        LightUpLeds();
        delay(50);
        if (i != 1)
        {
            ResetPins();
        }
    }
}

void Collision()
{
    for (i = 0; i<=8; i++)
    {
        ledNumber = i;
        oldNumber = 8 - i;
        LightUpLeds();
        ledNumber = oldNumber;
        LightUpLeds();
        delay(50);
        ResetPins();
    }
}
              //  firstLedUp = 1;
/*     LATDbits.LATD5 = 1;      //D3
       LATDbits.LATD6 = 1;      //D4
       LATDbits.LATD7 = 1;      //D5
       LATDbits.LATD8 = 1;      //D6
       LATDbits.LATD11 = 1;     //D7
       LATBbits.LATB14 = 1;      //D9
       LATGbits.LATG9 = 1;      //D10
       LATGbits.LATG8 = 1;      //D11*/
 //comment