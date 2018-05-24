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
#ifndef SOUND_CONTROL_H
#define	SOUND_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  

void TAS2521_Initialize(void);
void Build_Volume_Array(void);
void Set_Volume(uint8_t VolumeSetting);
void Volume_Update(void);
uint8_t abval(int8_t val);
void Headphones(uint8_t State);

int8_t  Volume_Array[32];
uint8_t MAX_ADC     = 252;
uint8_t MIN_ADC     = 66;
uint8_t ADC_Step    = 6;
int8_t  MAX_VOLUME   = 10;
int8_t  MIN_VOLUME   = -30;
uint8_t Volume_Step = 1;
uint8_t SENSITIVITY = 5;  //number of bits

const int8_t Linearized_Volume_Array[256] = 
{-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-60,
-59,
-59,
-58,
-58,
-57,
-56,
-56,
-55,
-55,
-54,
-53,
-53,
-52,
-52,
-51,
-51,
-50,
-49,
-49,
-48,
-48,
-47,
-46,
-46,
-45,
-45,
-44,
-43,
-43,
-42,
-42,
-41,
-40,
-40,
-39,
-39,
-38,
-38,
-37,
-37,
-36,
-36,
-35,
-35,
-34,
-34,
-33,
-33,
-32,
-32,
-31,
-31,
-30,
-30,
-29,
-29,
-28,
-28,
-27,
-26,
-26,
-25,
-25,
-24,
-24,
-23,
-23,
-22,
-22,
-22,
-21,
-21,
-20,
-20,
-19,
-19,
-18,
-18,
-18,
-17,
-17,
-16,
-16,
-15,
-15,
-15,
-14,
-14,
-13,
-13,
-12,
-12,
-11,
-11,
-11,
-10,
-10,
-9,
-9,
-9,
-8,
-8,
-8,
-8,
-7,
-7,
-7,
-7,
-7,
-6,
-6,
-6,
-6,
-5,
-5,
-5,
-5,
-5,
-4,
-4,
-4,
-4,
-3,
-3,
-3,
-3,
-3,
-2,
-2,
-2,
-2,
-1,
-1,
-1,
-1,
-1,
-1,
-1,
0,
0,
0,
0,
0,
0,
1,
1,
1,
1,
1,
1,
1,
2,
2,
2,
2,
2,
2,
2,
3,
3,
3,
3,
3,
3,
3,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
5,
6,
6
};



#define ENABLE  1
#define DISABLE 0


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

