/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef GLOBAL_VARIABLES_H
#define	GLOBAL_VARIABLES_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define QUARTER_SECONDS(x)  (x)
#define HALF_SECONDS(x)     (x << 1)
#define SECONDS(x)          (x << 2)    //Multipled by 4 to get the number of seconds for Timer 3

#define DO_NOTHING          2           //Debounce time for the brightness button
#define TOGGLE_BATTERY      20          //2 seconds necessary to hold for getting to screen control


//flag to determine if the buttons are controlling the screen
uint8_t Screen_Control = 0;
uint8_t Battery_Displayed = 0;
uint8_t Shutdown_Counter = 0;
uint8_t Shutdown_Process = 0;
volatile uint8_t Battery_Timer = 0;
volatile uint8_t Battery_Percent = 100;     //Initialize to 100, so there's no false issues on first powerup until the battery is read
volatile uint8_t Blue_Blink_Timer = 0;
volatile uint8_t Red_Blink_Timer = 0;
volatile uint8_t Brightness_Counter = 0;
volatile uint8_t Brightness_Count_Enable = 0;
volatile uint8_t Startup_Count_Enable = 0;
volatile uint8_t Startup_Counter = 0;
uint8_t Low_Battery = 0;
uint8_t Pi_Syncd = 0;
uint8_t Headphones_In = 0;
uint8_t Screen_Type = 0;       //0=SPI, 1=Composite
uint16_t PWM_Value = 200;




#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

