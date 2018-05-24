/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F25K80
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
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
#include "Debug.h"
#include "sound_control.h"
#include "battery_control.h"




void Brightness_SW_Check(void);
void PWR_SW_Check(void);
void Battery_Check(void);
void LED_Check(void);
void PI_UART_SYNC(void);
void Headphone_Check(void);
void Button_Check(void);

uint16_t    counter = 0;

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();


    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    //BLUE_LED_SetHigh();
    
    //while(PI_ALIVE_GetValue() == 0);    //wait here until the Pi is alive
    
    EN_5V_SetHigh();  //Now keep the 5V alive until I shut it down, regardless of the power switch
    BRIGHTNESS_SetPullup();     //set internal pullup for the brightness button
    
    
    /*
    uint8_t data_again = 0;
    
    while(1)
    {
        data_again = EUSART1_Read();
        EUSART2_Write(data_again);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        __delay_ms(10);
        if(eusart2RxCount)
        {
            EUSART1_Write(EUSART2_Read());
        }
    }
    
    while(1)
    {
        data_again = EUSART2_Read();
        EUSART1_Write(data_again);
    }
    */
    
    
    
    //Use RC4, the I2C SDA pin to monitor when/if the Pi is alive
    //  When it goes high, the Pi is there and generating 3.3V
    //If it does not go high after 100 Startup counts (5 seconds at 50ms per count)
    //  then go into debug mode
    RC4_SetDigitalInput();
    Startup_Count_Enable = 1;
    //While this pin is low, sit in this loop
    while(!RC4_GetValue())
    {
        if(Startup_Counter > 100)
        {
            Startup_Counter = 101;  //force it to keep coming back here
            Startup_Count_Enable = 0;  //stop the counter
            //go into debug mode
            Debug_Mode();
        }
    }
    
    Startup_Count_Enable = 0;  //stop the counter
    
    //After the Pi is alive, then enable I2C
    I2C_Initialize();
    
        
    TAS2521_Initialize();   //Initialize the I2S sound chip
    //If the headphones are already in, then be sure to set that flag
    //  and enable the headphones
    if(HP_SW_GetValue())
    {
        Headphones_In = 1;
        Headphones(ENABLE);
    }
    
    
    
    Battery_Percent = Read_Battery_Percent();   //read an initial battery percentage

    
    //Start the ADC going
    ADC_StartConversion(volume_input);
    while(ADC_Data_Ready == 0);  //wait here until the ADC data is ready
    ADC_Data_Ready = 0;
    Previous_ADC_Data = ADC_Data;  //initial condition for previous data
    
    Build_Volume_Array();  //build the array of volume data
    Set_Volume(ADC_Data);   //Set the initial volume to whatever the Pot is at
    
    EPWM1_LoadDutyValue(PWM_Value);
    
    //DEBUG REMOVE THIS SOON!
    //0x41 is the DAC volume address
    //I2C_Write(TAS_ADDR, 0x41, 5);
        
    
    //BLUE_LED_SetHigh();         //Turn on the Blue LED to show it's on
    
    SCREEN_UP_SetDigitalMode();
    SCREEN_UP_SetDigitalInput();
    SCREEN_DN_SetDigitalInput();
    
    while (1)
    {
        
        //counter = 65000;
        //while(counter--);
        //RED_LED_Toggle();
        
        //Go to the debug menu only if a D is detected on the UART
        if(EUSART1_DataReady)
        {
            if('D' == EUSART1_Read())
            {
                DebugMenu();
            }
        }
        
        LED_Check();
        
        Volume_Update();  //check the ADC data change and update volume if necessary
        
        Brightness_SW_Check();
        
        PWR_SW_Check();
        
        Battery_Check();
                        
        PI_UART_SYNC();
        
        Headphone_Check();
        
        Button_Check();
        
    }
}


//Controls the Red and Blue LEDs based off of certain status flags and counters
void LED_Check(void)
{
    
    //Update the Blue LED every quarter second
    if(Blue_Blink_Timer >= QUARTER_SECONDS(1))
    {
        //Reset the timer counter
        Blue_Blink_Timer = 0;
        
        //If the battery percent is high enough, keep the blue LED on
        if(Battery_Percent > LOW_BATTERY_PERCENT)
        {
            //If the battery is high enough, and the screen is being controlled,
            //  then toggle the LED
            if(Screen_Control == 1)
            {
                BLUE_LED_Toggle();
            }
            //If the screen is not being controlled, then just keep the LED high
            else
            {
                BLUE_LED_SetHigh();
            }
        }
        //If the battery is in a low battery state, then turn off the blue LED,
        //  the Red LED will be illuminated
        else
        {
            BLUE_LED_SetLow();
        }
    }
    
    
    //Every quarter second, check up on the Red LED status
    if(Red_Blink_Timer >= QUARTER_SECONDS(1))
    {
        //Reset the timer counter
        Red_Blink_Timer = 0;
        
        //If the battery is below critical level, then start blinking the Red LED
        if(Battery_Percent <= CRITICAL_BATTERY_PERCENT)
        {
            RED_LED_Toggle();
        }
        //If it's just below the low battery threshold, then just set it high
        else if(Battery_Percent <= LOW_BATTERY_PERCENT)
        {
            RED_LED_SetHigh();
        }
        //If it's above the low battery levels, then just keep it low
        else
        {
            RED_LED_SetLow();
        }
        
        
    }

}


//Checks the battery percentage every 30 seconds
void Battery_Check(void)
{
    //If there is input power, then the PWR_IN_PG signal will go low
    //  In this case, let's just fool things into thinking the battery
    //  is at 100 percent now, so the LEDs behave as if the battery is
    //  good, because it is now running off the power adapter
    if(PWR_IN_PG_GetValue() == 0)
    {
        Battery_Timer = 0;      //be sure to keep resetting this timer
        if(Battery_Percent < 100)
        {
            Battery_Percent = 105;
            Update_Battery_Icon(Battery_Percent);
        }
    }
    //If there is no input power (equals 1), and the battery percent is
    //  greater than 100, then this means the power plug was just removed.
    //  So read the actual battery percent and update the battery display on the screen.
    else if((PWR_IN_PG_GetValue() == 1) && Battery_Percent > 100)
    {
        Battery_Percent = Read_Battery_Percent();
        Update_Battery_Icon(Battery_Percent);
    }
    //If there is no input power then continue with reading the
    //  battery every 30 seconds and thus updating LEDs
    else
    {    
        //Battery_Timer is incremented every 250ms, so check the battery
        //  every 30 seconds
        if(Battery_Timer >= SECONDS(30))
        {
            //reset the battery timer
            Battery_Timer = 0;

            //Battery Percent is a global, since it is used in lots of places
            Battery_Percent = Read_Battery_Percent();
            Update_Battery_Icon(Battery_Percent);

        }
    }
    
}


void Brightness_SW_Check(void)
{
    //If the Brightness button is pressed, then start counting
    //  Will then determine from the count what action to take
    if(BRIGHTNESS_GetValue() == 0)
    {
        Brightness_Count_Enable = 1;    //start counting, 50ms per count
        if(Brightness_Counter >= 250)
        {
            Brightness_Counter = 250;     //latch at 250 = 12.5 seconds
        }
    }
    else
    {
        Brightness_Count_Enable = 0;    //don't count anymore
        if(Brightness_Counter < DO_NOTHING)
        {
            //then do nothing
        }
        //Toggle battery display if button is pressed for under 2 seconds
        else if(Brightness_Counter < TOGGLE_BATTERY)
        {
            //Every time the battery is toggled on or off, be sure to
            //  write the proper battery percent
            Update_Battery_Icon(Battery_Percent);

            if(Battery_Displayed == 0)
            {
                Battery_Displayed = 1;
                Update_Battery_Display(1);
            }
            else
            {
                Battery_Displayed = 0;
                Update_Battery_Display(0);
            }

        }
        else   //if it's greater than TOGGLE_BATTERY, then it is going to screen mode
        {
            if(Screen_Control == 1)
            {
                Screen_Control = 0;     //tell the code it's no longer in screen mode
                SCREEN_SW_SetLow();
            }
            else
            {
                Screen_Control = 1;     //tell the code it's in screen mode
                SCREEN_SW_SetHigh();
            }
        }
        
        //after determining how long it was pressed, reset the counter
        Brightness_Counter = 0;        
    }
        
          
    
}

//
// In there check the Up and Down buttons to see what
//  to do with the screen PWM
//
void Button_Check(void)
{
    //Only do brightness change if we're in screen control mode
    if(Screen_Control == 1)
    {
        //PWM value is inverse of brightness...higher PWM is dimmer screen
        if(SCREEN_DN_GetValue() == 0)
        {
            PWM_Value = PWM_Value + 1;
            if(PWM_Value > 499)
            {
                PWM_Value = 499;   //don't go above here
            }
            
            EPWM1_LoadDutyValue(PWM_Value);
            
            //delay how long here?
            __delay_ms(10);
        }
        else if(SCREEN_UP_GetValue() == 0)
        {
            PWM_Value = PWM_Value - 1;
            if(PWM_Value < 2)
            {
                PWM_Value = 2;   //don't go below here
            }
            
            EPWM1_LoadDutyValue(PWM_Value);
            
            //delay how long here?
            __delay_ms(10);
        }
    }
    
}


void Headphone_Check(void)
{
    //If the headphones are not in, but the switch says they are plugged in,
    //  then set the headphones flag and enable the headphones
    //If the headphones are in, then check the switch.  If it says they are not
    //  plugged in, then disable the headphones and turn on the speaker
    if(Headphones_In == 0)
    {
        if(HP_SW_GetValue())
        {
            Headphones(ENABLE);
        }
    }
    else
    {
        if(!HP_SW_GetValue())
        {
            Headphones(DISABLE);            
        }
        
    }
    

}


void PWR_SW_Check(void)
{
    //If the power switch is turned off, then do a 
    //  safe shutdown of the RPi
    if(PWR_SW_SIG_GetValue() == 0)
    {
        //Long debounce, to make sure it really wants to be turned off
        counter = 10000;
        while(counter--);
        
        if(PWR_SW_SIG_GetValue() == 0)
        {
            BLUE_LED_LAT = 1;
            TAS_RST_B_SetLow();     //hold the sound chip in reset while shutting down
            PI_SHUTDOWN_SetHigh();  //Shutdown the Pi
            
            //Start the shutdown process
            Shutdown_Process = 1;   //Start the shutdown counter
            
            
            //
            //Set the UART pin to digital input, and remove the pullup
            //  Then wait until it goes low, meaning the Pi is off
            
            RB7_SetDigitalInput();
            RB7_ResetPullup();
            
            //Need to make sure that there is a timeout on checking if the
            //  UART pin has gone low.  There could be a case where someone toggles
            //  the power switch quickly, so the Pi is not yet responding to the
            //  shutdown signal, so UART will never go low, it will never turn off
            //So put in a timeout where it will eventually shut down regardless of the 
            //  state of the UART pin
            counter = 0;
            while(counter < 2000)
            {
                counter++;
                __delay_ms(10);
                if(RB7_GetValue() == 0)
                {
                    counter = 5001;
                }
                
            }
            
            //
            counter = 100;
            while(counter--)
            {
                __delay_ms(10);
            }
            
            //Now that we've cleaned everything up and shutdown the Pi, it's time
            //  to cut the power
            EN_5V_SetLow();
            SLEEP();        //Attempt to get the part to sleep quickly so that
                            //  if/when I do EEPROM stuff I don't run into that 
                            //  shutdown issue of overwriting EEPROM data because
                            //  the program counter goes nuts as the supply falls
            
            
                
        }
        
    }
}


//When starting up, make sure to sync with the Pi before trying
//  to transmit the battery update data
void PI_UART_SYNC(void)
{
    uint8_t data[2] = {'E', 'Q'};
    //Only run this if the Pi is not sync'd
    //  Maybe every once in a while clear and re-sync...?
    if(Pi_Syncd != 1)
    {
        //Write 'E', 'Q' continually,  until the Pi responds
        EUSART2_Write_Array(data, 2);
        __delay_ms(10);
        
        //if the Pi responds with an 'e', then it is alive and ready
        if(eusart2RxCount > 0)
        {
            if(EUSART2_Read() == 'e')
            {
                Pi_Syncd = 1;
            }
        }
    }
   
}


/**
 End of File
*/