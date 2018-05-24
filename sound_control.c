/*****************************************************
 All the stuff necessary to talk to and control the
 TAS2521...it's a complicated chip
 
 *****************************************************/


#include "mcc_generated_files/mcc.h"
#include "sound_control.h"


void TAS2521_Initialize(void)
{
    //Make sure the chip is not in reset
    TAS_RST_B_SetHigh();
    __delay_ms(10);
    __delay_ms(10);  //wait for it to wake up
    
    
    //Giant sequence of I2C writes to get this thing setup
    //  hopefully it's correct...
    
    //BCLK measured = 1.536MHz
    //Is this going to be a problem that it bursts, it's not a constant clock?
    //  Is it true that it's not constant...?  Need to check that too
    
    I2C_Write(TAS_ADDR, 0x00, 0x00);  //register 0, set to page 0
    I2C_Write(TAS_ADDR, 0x01, 0x01);  //initiate software reset
    I2C_Write(TAS_ADDR, 0x04, 0x07);  //Low PLL range, BCLK is PLL input, CODEC uses PLL
    I2C_Write(TAS_ADDR, 0x05, 0x18);  //PLL powered down, P=1, R=8
    I2C_Write(TAS_ADDR, 0x06, 0x07);  //J=7
    I2C_Write(TAS_ADDR, 0x07, 0x00);  //D=0
    I2C_Write(TAS_ADDR, 0x05, 0x98);  //PLL powered up, P=1, R=8
    I2C_Write(TAS_ADDR, 0x0B, 0x82);  //NDAC powered up, NDAC=2
    I2C_Write(TAS_ADDR, 0x0C, 0x87);  //MDAC powered up, MDAC=7
    I2C_Write(TAS_ADDR, 0x0D, 0x00);  //upper bits of DOSR
    I2C_Write(TAS_ADDR, 0x0E, 0x80);  //DOSR=128
    I2C_Write(TAS_ADDR, 0x1B, 0x00);  //I2S interface, 16-bit word, BCLK is input, WCLK is input
    I2C_Write(TAS_ADDR, 0x3C, 0x02);  //processing = PRB_P2
    
    //Debug steps here...hopefully put a clock out on GPIO
    I2C_Write(TAS_ADDR, 0x19, 0x03);  //CDIV_CLKIN=PLL_CLK (clock going into the output divider to go to the GPIO)
    I2C_Write(TAS_ADDR, 0x1A, 0x00);  //CLKOUT M divider = 128  (so 672kHz output in theory)
    I2C_Write(TAS_ADDR, 0x34, 0x04);  //GPIO is CLKOUT 
    //end debug steps
    
    I2C_Write(TAS_ADDR, 0x00, 0x01);  //Set to page 1
    I2C_Write(TAS_ADDR, 0x01, 0x10);  //Master reference enabled, POR nod powered down, LDO bandgap not powered down
    I2C_Write(TAS_ADDR, 0x02, 0x00);  //AVDD LDO = 1.8V, PLL and HP level shifters powered up
    I2C_Write(TAS_ADDR, 0x09, 0x00);  //HP powered down, AIN powered down
    I2C_Write(TAS_ADDR, 0x0A, 0x00);  //Common Mode = 0.9V, HP full drive ability
    I2C_Write(TAS_ADDR, 0x0B, 0x00);  //Over current debounced by 64ms, will current limit if detected
    I2C_Write(TAS_ADDR, 0x0C, 0x00);  //DAC not to HP, nothing routed to HP
    I2C_Write(TAS_ADDR, 0x10, 0x40);  //HP driver is muted
    I2C_Write(TAS_ADDR, 0x14, 0x02);    //HP power up time set to fastest
    //I2C_Write(TAS_ADDR, 0x14, 0x65);  //Soft step time = 50ms, slow power up = 5 time constants, use 6k resistance
    I2C_Write(TAS_ADDR, 0x16, 0x6C);  //HP volume = mute
    I2C_Write(TAS_ADDR, 0x2D, 0x02);  //SPK output driver powered up
    I2C_Write(TAS_ADDR, 0x2E, 0x14);  //SPK driver volume = -10dB
    I2C_Write(TAS_ADDR, 0x30, 0x20);  //SPK amplifier volume = 12dB
    
    //wait for things to get set and settle
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
    
    I2C_Write(TAS_ADDR, 0x00, 0x00);  //go back to page 0
    I2C_Write(TAS_ADDR, 0x3F, 0xB0);  //DAC powered up, data from mix of left and right channel soft stepping = 1 step per word clock
    I2C_Write(TAS_ADDR, 0x40, 0x04);  //DAC not muted
    I2C_Write(TAS_ADDR, 0x41, 0x00);  //Volume = 0dB
    
    //Get sound now?!?!...I did get sound now!!!!
    
    
}


void Volume_Update(void)
{
    int8_t Difference = 0;
    uint8_t Abs_diff = 0;
    
   
    if(ADC_Data_Ready == 1)
    {
        Difference = ADC_Data - Previous_ADC_Data;
        
        Abs_diff = abval(Difference);
        
        if(Abs_diff > ADC_Step)
        {
            Previous_ADC_Data = ADC_Data;
            Set_Volume(ADC_Data);                  
        }
                
        
    }
    
}



void Set_Volume(uint8_t VolumeSetting)
{
    
    
    int8_t Volume_Index = 0;
    int8_t Volume = 0;
    
    Volume_Index = VolumeSetting;
    
    
    Volume = Linearized_Volume_Array[Volume_Index];
 
    
    
    printf("\nVolume = %d", Volume);
    
    
    //0x41 is the DAC volume address
    I2C_Write(TAS_ADDR, 0x41, Volume);
    
}



void Build_Volume_Array(void)
{
            
}


/*
void Set_Volume(uint8_t VolumeSetting)
{
    //First figure out what is the lowest usable volume setting
    //  for the part (definitely going to be higher than -63dB)
    //Then figure out the max volume that doesn't bust the speaker
    //  Probably around 20dB or so, maybe 15dB
    //These will give me upper and lower bounds for how to step the volume
    
    //Then find the upper and lower bounds for ADC conversions
 
    //Then give the selection of Fine, Medium, or Coarse for
    //  volume sensitivity
    //Fine = 32 steps,  Medium = 16 steps, Coarse = 8 steps
    //  This would make SENSITIVITY = 5, 4, 3, so i can bit shift
    //  
    //The hysteresis will be the (max ADC - min ADC)/num steps
    //The corresponding volume settings will be (max dB - min dB)/num steps
    //Build this table programmatically?
    //  or have it started manually then update if necessary
    
    int8_t Volume_Index = 0;
    int8_t Volume = 0;
    
    Volume_Index = (VolumeSetting - MIN_ADC) / ADC_Step;
    
    if(Volume_Index < 0)
    {
        Volume = Volume_Array[0];
    }
    else if(Volume_Index > (1 << SENSITIVITY))
    {
        Volume = Volume_Array[(1 << SENSITIVITY)-1];
    }
    else
    {
        Volume = Volume_Array[Volume_Index];
    }
    
    
    printf("\nVolume = %d", Volume);
    
    
    //0x41 is the DAC volume address
    I2C_Write(TAS_ADDR, 0x41, Volume);
    
}



void Build_Volume_Array(void)
{
    uint8_t counter = 0;
    
    for(counter = 0; counter < (1 << SENSITIVITY); counter++)
    {
        Volume_Array[counter] = (MIN_VOLUME + ((counter)*Volume_Step));// << 1;
    }
        
}

 */


uint8_t abval(int8_t val)  
 { 
     return (val<0 ? (-val) : val);
 } 


void Headphones(uint8_t State)
{
    
    if(State == ENABLE)
    {
        Headphones_In = 1;  //set the headphones flag
        //setup the driver to drive headphones and turn off speaker
        I2C_Write(TAS_ADDR, 0x00, 0x01);    //switch to page 1
        I2C_Write(TAS_ADDR, 0x09, 0x20);    //Power up HP
        I2C_Write(TAS_ADDR, 0x0C, 0x08);    //DAC to HP
        I2C_Write(TAS_ADDR, 0x10, 0x0C);    //HP not muted, gain = 12dB
        I2C_Write(TAS_ADDR, 0x2D, 0x00);    //Power down speaker
        I2C_Write(TAS_ADDR, 0x00, 0x00);    //Back to page 0
    }
    else
    {
        Headphones_In = 0;  //clear the headphones flag, they're not in anymore
        //setup the driver to drive speakers and turn off the headphones
        I2C_Write(TAS_ADDR, 0x00, 0x01);    //switch to page 1
        I2C_Write(TAS_ADDR, 0x2D, 0x02);    //Power up speaker
        I2C_Write(TAS_ADDR, 0x09, 0x00);    //Power down HP
        I2C_Write(TAS_ADDR, 0x0C, 0x00);    //DAC not to HP
        I2C_Write(TAS_ADDR, 0x10, 0x40);    //HP muted
        I2C_Write(TAS_ADDR, 0x00, 0x00);    //Back to page 0
    }
    
    
}