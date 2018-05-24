/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.26
        Device            :  PIC18F25K80
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set VOLUME aliases
#define VOLUME_TRIS               TRISAbits.TRISA0
#define VOLUME_LAT                LATAbits.LATA0
#define VOLUME_PORT               PORTAbits.RA0
#define VOLUME_ANS                ANCON0bits.ANSEL0
#define VOLUME_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define VOLUME_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define VOLUME_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define VOLUME_GetValue()           PORTAbits.RA0
#define VOLUME_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define VOLUME_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define VOLUME_SetAnalogMode()  do { ANCON0bits.ANSEL0 = 1; } while(0)
#define VOLUME_SetDigitalMode() do { ANCON0bits.ANSEL0 = 0; } while(0)

// get/set PWR_IN_PG aliases
#define PWR_IN_PG_TRIS               TRISAbits.TRISA1
#define PWR_IN_PG_LAT                LATAbits.LATA1
#define PWR_IN_PG_PORT               PORTAbits.RA1
#define PWR_IN_PG_ANS                ANCON0bits.ANSEL1
#define PWR_IN_PG_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PWR_IN_PG_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PWR_IN_PG_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PWR_IN_PG_GetValue()           PORTAbits.RA1
#define PWR_IN_PG_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PWR_IN_PG_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PWR_IN_PG_SetAnalogMode()  do { ANCON0bits.ANSEL1 = 1; } while(0)
#define PWR_IN_PG_SetDigitalMode() do { ANCON0bits.ANSEL1 = 0; } while(0)

// get/set EN_5V aliases
#define EN_5V_TRIS               TRISAbits.TRISA2
#define EN_5V_LAT                LATAbits.LATA2
#define EN_5V_PORT               PORTAbits.RA2
#define EN_5V_ANS                ANCON0bits.ANSEL2
#define EN_5V_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define EN_5V_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define EN_5V_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define EN_5V_GetValue()           PORTAbits.RA2
#define EN_5V_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define EN_5V_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define EN_5V_SetAnalogMode()  do { ANCON0bits.ANSEL2 = 1; } while(0)
#define EN_5V_SetDigitalMode() do { ANCON0bits.ANSEL2 = 0; } while(0)

// get/set PI_SHUTDOWN aliases
#define PI_SHUTDOWN_TRIS               TRISAbits.TRISA3
#define PI_SHUTDOWN_LAT                LATAbits.LATA3
#define PI_SHUTDOWN_PORT               PORTAbits.RA3
#define PI_SHUTDOWN_ANS                ANCON0bits.ANSEL3
#define PI_SHUTDOWN_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define PI_SHUTDOWN_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define PI_SHUTDOWN_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define PI_SHUTDOWN_GetValue()           PORTAbits.RA3
#define PI_SHUTDOWN_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define PI_SHUTDOWN_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define PI_SHUTDOWN_SetAnalogMode()  do { ANCON0bits.ANSEL3 = 1; } while(0)
#define PI_SHUTDOWN_SetDigitalMode() do { ANCON0bits.ANSEL3 = 0; } while(0)

// get/set TAS_GPIO aliases
#define SCREEN_UP_TRIS               TRISAbits.TRISA5
#define SCREEN_UP_LAT                LATAbits.LATA5
#define SCREEN_UP_PORT               PORTAbits.RA5
#define SCREEN_UP_ANS                ANCON0bits.ANSEL4
#define SCREEN_UP_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SCREEN_UP_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SCREEN_UP_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SCREEN_UP_GetValue()           PORTAbits.RA5
#define SCREEN_UP_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SCREEN_UP_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SCREEN_UP_SetAnalogMode()  do { ANCON0bits.ANSEL4 = 1; } while(0)
#define SCREEN_UP_SetDigitalMode() do { ANCON0bits.ANSEL4 = 0; } while(0)

// get/set TAS_RST_B aliases
#define TAS_RST_B_TRIS               TRISAbits.TRISA6
#define TAS_RST_B_LAT                LATAbits.LATA6
#define TAS_RST_B_PORT               PORTAbits.RA6
#define TAS_RST_B_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define TAS_RST_B_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define TAS_RST_B_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define TAS_RST_B_GetValue()           PORTAbits.RA6
#define TAS_RST_B_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define TAS_RST_B_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set TAS_MCLK aliases
#define SCREEN_DN_TRIS               TRISAbits.TRISA7
#define SCREEN_DN_LAT                LATAbits.LATA7
#define SCREEN_DN_PORT               PORTAbits.RA7
#define SCREEN_DN_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SCREEN_DN_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SCREEN_DN_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SCREEN_DN_GetValue()           PORTAbits.RA7
#define SCREEN_DN_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SCREEN_DN_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set HP_SW aliases
#define HP_SW_TRIS               TRISBbits.TRISB0
#define HP_SW_LAT                LATBbits.LATB0
#define HP_SW_PORT               PORTBbits.RB0
#define HP_SW_WPU                WPUBbits.WPUB0
#define HP_SW_ANS                ANCON1bits.ANSEL10
#define HP_SW_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define HP_SW_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define HP_SW_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define HP_SW_GetValue()           PORTBbits.RB0
#define HP_SW_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define HP_SW_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define HP_SW_SetPullup()      do { WPUBbits.WPUB0 = 1; } while(0)
#define HP_SW_ResetPullup()    do { WPUBbits.WPUB0 = 0; } while(0)
#define HP_SW_SetAnalogMode()  do { ANCON1bits.ANSEL10 = 1; } while(0)
#define HP_SW_SetDigitalMode() do { ANCON1bits.ANSEL10 = 0; } while(0)

// get/set PI_ALIVE aliases
#define SCREEN_PWM_TRIS               TRISBbits.TRISB1
#define SCREEN_PWM_LAT                LATBbits.LATB1
#define SCREEN_PWM_PORT               PORTBbits.RB1
#define SCREEN_PWM_WPU                WPUBbits.WPUB1
#define SCREEN_PWM_ANS                ANCON1bits.ANSEL8
#define SCREEN_PWM_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SCREEN_PWM_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SCREEN_PWM_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SCREEN_PWM_GetValue()           PORTBbits.RB1
#define SCREEN_PWM_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SCREEN_PWM_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SCREEN_PWM_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define SCREEN_PWM_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define SCREEN_PWM_SetAnalogMode()  do { ANCON1bits.ANSEL8 = 1; } while(0)
#define SCREEN_PWM_SetDigitalMode() do { ANCON1bits.ANSEL8 = 0; } while(0)

// get/set BAT_ALRT_B aliases
#define BAT_ALRT_B_TRIS               TRISBbits.TRISB2
#define BAT_ALRT_B_LAT                LATBbits.LATB2
#define BAT_ALRT_B_PORT               PORTBbits.RB2
#define BAT_ALRT_B_WPU                WPUBbits.WPUB2
#define BAT_ALRT_B_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define BAT_ALRT_B_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define BAT_ALRT_B_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define BAT_ALRT_B_GetValue()           PORTBbits.RB2
#define BAT_ALRT_B_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define BAT_ALRT_B_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define BAT_ALRT_B_SetPullup()      do { WPUBbits.WPUB2 = 1; } while(0)
#define BAT_ALRT_B_ResetPullup()    do { WPUBbits.WPUB2 = 0; } while(0)

// get/set PWR_SW_SIG aliases
#define PWR_SW_SIG_TRIS               TRISBbits.TRISB3
#define PWR_SW_SIG_LAT                LATBbits.LATB3
#define PWR_SW_SIG_PORT               PORTBbits.RB3
#define PWR_SW_SIG_WPU                WPUBbits.WPUB3
#define PWR_SW_SIG_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define PWR_SW_SIG_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define PWR_SW_SIG_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define PWR_SW_SIG_GetValue()           PORTBbits.RB3
#define PWR_SW_SIG_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define PWR_SW_SIG_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define PWR_SW_SIG_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define PWR_SW_SIG_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)

// get/set BRIGHTNESS aliases
#define BRIGHTNESS_TRIS               TRISBbits.TRISB4
#define BRIGHTNESS_LAT                LATBbits.LATB4
#define BRIGHTNESS_PORT               PORTBbits.RB4
#define BRIGHTNESS_WPU                WPUBbits.WPUB4
#define BRIGHTNESS_ANS                ANCON1bits.ANSEL9
#define BRIGHTNESS_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BRIGHTNESS_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BRIGHTNESS_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BRIGHTNESS_GetValue()           PORTBbits.RB4
#define BRIGHTNESS_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BRIGHTNESS_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BRIGHTNESS_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define BRIGHTNESS_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define BRIGHTNESS_SetAnalogMode()  do { ANCON1bits.ANSEL9 = 1; } while(0)
#define BRIGHTNESS_SetDigitalMode() do { ANCON1bits.ANSEL9 = 0; } while(0)

// get/set B_BTN aliases
#define B_BTN_TRIS               TRISBbits.TRISB5
#define B_BTN_LAT                LATBbits.LATB5
#define B_BTN_PORT               PORTBbits.RB5
#define B_BTN_WPU                WPUBbits.WPUB5
#define B_BTN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define B_BTN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define B_BTN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define B_BTN_GetValue()           PORTBbits.RB5
#define B_BTN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define B_BTN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define B_BTN_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define B_BTN_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()    do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()   do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()   do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()         PORTBbits.RB6
#define RB6_SetDigitalInput()   do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()  do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()     do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()   do { WPUBbits.WPUB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()    do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()   do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()   do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()         PORTBbits.RB7
#define RB7_SetDigitalInput()   do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()  do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()     do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()   do { WPUBbits.WPUB7 = 0; } while(0)

// get/set BLUE_LED aliases
#define BLUE_LED_TRIS               TRISCbits.TRISC0
#define BLUE_LED_LAT                LATCbits.LATC0
#define BLUE_LED_PORT               PORTCbits.RC0
#define BLUE_LED_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define BLUE_LED_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define BLUE_LED_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define BLUE_LED_GetValue()           PORTCbits.RC0
#define BLUE_LED_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define BLUE_LED_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set RED_LED aliases
#define RED_LED_TRIS               TRISCbits.TRISC1
#define RED_LED_LAT                LATCbits.LATC1
#define RED_LED_PORT               PORTCbits.RC1
#define RED_LED_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RED_LED_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RED_LED_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RED_LED_GetValue()           PORTCbits.RC1
#define RED_LED_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RED_LED_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set SCREEN_SW aliases
#define SCREEN_SW_TRIS               TRISCbits.TRISC2
#define SCREEN_SW_LAT                LATCbits.LATC2
#define SCREEN_SW_PORT               PORTCbits.RC2
#define SCREEN_SW_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SCREEN_SW_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SCREEN_SW_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SCREEN_SW_GetValue()           PORTCbits.RC2
#define SCREEN_SW_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SCREEN_SW_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()    do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()   do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()   do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()         PORTCbits.RC3
#define RC3_SetDigitalInput()   do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()  do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()    do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()   do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()   do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()         PORTCbits.RC4
#define RC4_SetDigitalInput()   do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()  do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/