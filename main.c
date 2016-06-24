/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC16F1614
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "cie1931.h"
#define DELAY_TIME 5
//globals for pwm state
volatile uint8_t     pwm3 = 0; //PWM3 setting
volatile uint8_t     pwm4 = 0; //PWM4 setting
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    // enable high drive mode for pwm pins
    HIDC5 = 1;
    HIDC4 = 1;

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    uint8_t     pwm3_fade = 0; //PWM3 setting during fade
    uint8_t     pwm4_fade = 0; //PWM4 setting during fade
    //initialize outputs
    PWM3_LoadDutyValue(cie[pwm3]);
    PWM4_LoadDutyValue(cie[pwm4]);
    IO_RA4_SetLow();
    while (1)
    {
        //increment or decrement fade variable closer to desired pwm setting
        if(pwm3_fade < pwm3)
        {
            pwm3_fade++;
            PWM3_LoadDutyValue(cie[pwm3_fade]); 
        }
        else if(pwm3_fade >pwm3)
        {
            pwm3_fade--;
            PWM3_LoadDutyValue(cie[pwm3_fade]);
        }
        
        if(pwm4_fade < pwm4)
        {
            pwm4_fade++;
            PWM4_LoadDutyValue(cie[pwm4_fade]); 
        }
        else if(pwm4_fade >pwm4)
        {
            pwm4_fade--;
            PWM4_LoadDutyValue(cie[pwm4_fade]);
        }
        //delay time. Can't be a variable
        __delay_ms(DELAY_TIME);
    }
}
/**
 End of File
*/