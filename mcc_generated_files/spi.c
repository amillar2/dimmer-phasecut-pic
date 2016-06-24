/**
  MSSP Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    mssp.c

  @Summary
    This is the generated driver implementation file for the MSSP driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for MSSP.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "spi.h"
#include "pin_manager.h"
#include "interrupt_manager.h"

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

void SPI_Initialize(void)
{
    // Set the SPI module to the options selected in the User Interface

    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE Idle to Active; D_nA lastbyte_address; 
    SSP1STAT = 0x00;

    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM SCKx_nSSxenabled; SSPOV no_overflow; 
    SSP1CON1 = 0x24;

    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    
    SLRCONC = 0X00;
}

uint8_t SPI_Exchange8bit(uint8_t data)
{
    uint8_t dummyRead = SSPBUF;    // Clears buffer full flag

    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSPBUF = data;

    while(SSP1STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSPBUF);
}

uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;
    uint8_t dummyRead;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    dummyRead = SPI_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(DUMMY_DATA);
                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

bool SPI_IsBufferFull(void)
{
    return (SSP1STATbits.BF);
}

bool SPI_HasWriteCollisionOccured(void)
{
    return (SSP1CON1bits.WCOL);
}

void SPI_ClearWriteCollisionStatus(void)
{
    SSP1CON1bits.WCOL = 0;
}

bool SPI_HasReceiveOverflowOccured(void)
{
    return (SSP1CON1bits.SSPOV);
}

void SPI_ClearReceiveOverflowStatus(void)
{
    SSP1CON1bits.SSPOV = 0;
}

// ============================================
// Add this line to share Cnt between main and TMR0_ISR
extern volatile uint8_t pwm3;
extern volatile uint8_t pwm4;

void SPI_ISR(void)
{
    //disable interrupts to allow blocking reads following first byte
   // Disable the Global Interrupts
    INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptDisable();
    
    uint8_t     readDummy = 0; //dummy variable for SPI read
    uint8_t     addr = 0; //address 0-PWM3 1-PWM4
    uint8_t     data = 0; //PWM setting 0-256
    addr = SPI_Exchange8bit(readDummy);//read address 0-PWM3 1-PWM4
    data = SPI_Exchange8bit(readDummy);//read pwm setting
    if (addr==0) {
            pwm3 = data;
        }
        else if (addr==1) {
            pwm4 = data;
        }
}
// ============================================
/**
 End of File
*/