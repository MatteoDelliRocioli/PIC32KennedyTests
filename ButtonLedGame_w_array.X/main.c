/* 
 * File:   main.c
 * Author: delli
 * Proj-name: ButtonLedGame_w_array
 * Created on May 16, 2019, 4:43 PM
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
#include "pinlib.h"

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
void Light_up_leds(char value);
void KittCar();
void Collision();
void Random();

int pressedButton = 0;
int oldButtonState;
int newButtonState, gameNumber;
int i, add;

int main(void) {
    /*configure machine*/
    TRISD = (1<<4) | (1<<0); // uso il pulsante BUT2
    TRISB = 0x0000;
    TRISG = 0x0000;
    
    LED_YELLOW = 0;
    ResetPins (0);
    gameNumber = 0;
    add = 0;
    
    while (1) {
        /*wait button state*/
        if (!pressedButton)
        {
        delay(50);
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
            pressedButton = 0;
            gameNumber ++;
            //TODO: aumenta numero per switch gioco
            LED_YELLOW =~ LED_YELLOW;    //button pressed, led yellow 
                                                //lights up
            /*while(1)
            {
                for (i = 0; i < 8; i++)
                {
                    light_up_leds(i);
                    delay(50);
                    ResetPins();
                }
                for (i = 6; i > 0; i--)
                {
                    light_up_leds(i);
                    delay(50);
                    ResetPins();
                }
            }*/
        }
        switch (gameNumber)
        {
            case 1:
                KittCar();
                break;
            case 2:
                Collision();
                break;
            case 3:
                Random();
                break;
            default:
                gameNumber = 0;
                break;
        }
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

void Light_up_leds(char value)
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
    }
    else if (value == 5)
    {
        LATB = character [value];
    }
    else if (value > 5 && value < 8)
    {
        LATG = character [value];
    }
}

void KittCar()
{
    for (i = 0; i < 8; i++)
    {
        Light_up_leds(i);
        delay(50);
        ResetPins();
    }
    for (i = 6; i > 0; i--)
    {
        Light_up_leds(i);
        delay(50);
        ResetPins();
    }
}

void Collision()
{
    //Light_up_leds(1);
    for (i = 0; i < 4; i++)
    {
        Light_up_leds(i);
        Light_up_leds(7 - i);
        delay(50);
        ResetPins();
    }
}

void Random()
{
    for (i = 0; i < 8; i++)
    {
        Light_up_leds(i);
        delay(50);
        ResetPins();
        if (i == 8)
        {
            add++;
        }
        Light_up_leds(add);
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

/*PINS' MAP
20, 40, 80, 100, 800, 
d3, d4, d5, d6, d7  [LATD]


LATB = 0x4000; d9
LATG = 0x0200; d10
LATG = 0x0100; d11*/
