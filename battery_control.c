/*****************************************************
 All the stuff necessary to talk to and control the
 *   MAX17048 battery  monitor
 *  
 *****************************************************/


#include "mcc_generated_files/mcc.h"
#include "battery_control.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"



uint8_t Read_Battery_Percent(void)
{
    uint8_t BatteryPercent = 0;
    
    //0x04 is the battery percent register in the part
    BatteryPercent = I2C_Read(BATT_ADDR, 0x04);
    
    return BatteryPercent;
}


uint8_t Read_Battery_Voltage(void)
{
    uint8_t BatteryVoltage = 0;
    
    //0x02 is the battery voltage register in the part
    BatteryVoltage = I2C_Read(BATT_ADDR, 0x02);
    
    return BatteryVoltage;
}


uint8_t Read_Battery_Register(uint8_t Register)
{
    uint8_t RegisterData = 0;
    
    //Reads any register from the battery monitor
    RegisterData = I2C_Read(BATT_ADDR, Register);
    
    return RegisterData;
}


void Update_Battery_Icon(uint8_t charge)
{
    uint8_t data[3] = {'I', 0, 'Q'};
    
    data[1] = charge;
    
    EUSART2_Write_Array(data, sizeof(data));
    
}


void Update_Battery_Display(uint8_t display)
{
    uint8_t data[3] = {'D', 0, 'Q'};
    
    data[1] = display;    
    
    EUSART2_Write_Array(data, sizeof(data));
}


void Update_X_Offset(uint16_t offset)
{
    uint8_t data[4] = {'X', 0, 0, 'Q'};
    
    data[1] = (uint8_t) ((offset >> 8) & 0xFF);
    data[2] = (uint8_t) (offset & 0xFF);
    
    EUSART2_Write_Array(data, sizeof(data));
    
}


void Update_Y_Offset(uint16_t offset)
{
    uint8_t data[4] = {'Y', 0, 0, 'Q'};
    
    data[1] = (uint8_t) ((offset >> 8) & 0xFF);
    data[2] = (uint8_t) (offset & 0xFF);
    
    EUSART2_Write_Array(data, sizeof(data));
    
}