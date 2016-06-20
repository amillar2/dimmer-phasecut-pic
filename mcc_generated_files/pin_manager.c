/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC16F1614
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x0;
    LATC = 0x0;
    WPUA = 0x3F;
    WPUC = 0x3F;
    ANSELA = 0x17;
    ANSELC = 0x4;
    TRISC = 0xB;
    TRISA = 0x24;

    OPTION_REGbits.nWPUEN = 0x1;

    // interrupts-on-change are globally disabled
    INTCONbits.IOCIE = 0;
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    SSPSSPPS = 0x0013;   //RC3->MSSP:SS;
    T2PPS = 0x0005;   //RA5->TMR2:T2IN;
    SSPDATPPS = 0x0011;   //RC1->MSSP:SDI;
    RA4PPS = 0x0003;   //RA4->ZCD:ZCD1OUT;
    RC4PPS = 0x000E;   //RC4->PWM3:PWM3OUT;
    RC2PPS = 0x0011;   //RC2->MSSP:SDO;
    RC5PPS = 0x000F;   //RC5->PWM4:PWM4OUT;
    SSPCLKPPS = 0x0010;   //RC0->MSSP:SCK;
    T4PPS = 0x0005;   //RA5->TMR4:T4IN;
    HIDRVC = 0X0030; //ENABLE HIGH CURRENT

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}


void PIN_MANAGER_IOC(void)
{    
}

/**
 End of File
*/