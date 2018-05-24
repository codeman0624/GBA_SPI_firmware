#include "mcc_generated_files/mcc.h"
#include "xc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Debug.h"
#include "sound_control.h"
#include "battery_control.h"



void DebugMenu(void)
{
    unsigned char selection = 0;
    
    while(selection != 'x' && selection != 'X')
    {
        printf("\n\nThis is the main menu.  Make a selection: \n");
        printf("1: LED Control\n");
        printf("2: TAS2521 communication\n");
        printf("3: MAX17048 communication\n");
        printf("4: ADC\n");
        printf("5: Battery Display\n");
        printf("6: Screen Brightness\n");
        printf("X:  Exit\n\n");
        
        printf("Selection:  ");
        
        
        selection = EUSART1_Read();
        EUSART1_Write(selection);   //echo it back just to show it's working
        
        switch(selection)
        {
            case '1':
            {
                LED_Control();
                break;
            }
            case '2':
            {
                TAS2521_Communication();
                break;
            }
            case '3':
            {
                MAX17048_Communication();
            }
            case '4':
            {
                ADC_Debug();
            }
            case '5':
            {
                Battery_Display();
            }
            case '6':
            {
                Screen_Brightness_Debug();
            }
            case 'x':
            case 'X':
            {
                printf("\n\nQuitting Application...");
                break;
            }
            
            default:
                printf("\n\nInvalid selection...");
                break;
        }
        
        
    }

}


void LED_Control(void)
{
    unsigned char command_input[16];
    unsigned char first_command[16];
    unsigned char second_command[16];
    char delim[] = " ";
    char* token;
    unsigned char counter = 0, flush = 0;
    
    printf("\n\n\n");  //just for formatting
    
    printf("Controls the state of the Blue and Red LEDs\n");
    printf("Command Syntax (single space between):  Blue ON\n\n");
    printf("Command: ");
    
    //read the whole input from the console
    //gets(&command_input);
    
    
    while(command_input[counter-1] != '\n' && command_input[counter-1] != '\r')
    {
        command_input[counter] = EUSART1_Read();
        EUSART1_Write(command_input[counter]);
        counter++;
    }
    command_input[counter-1] = '\0';
    
    while(EUSART1_DataReady)
    {
        flush = EUSART1_Read();
    }
    
      

    //search for the first delimeter, print that to the screen as an
    //  indicator, then copy that into the first_command string
    token = strtok(command_input, delim);
    printf("\ntoken=%s", token);
    strcpy(first_command, token);
    
    //Find the second part of the command, print to the screen then
    //  copy it to the second_command string
    token = strtok(NULL, delim);
    printf("\ntoken=%s\n", token);
    strcpy(second_command, token);

    
    //with strcmp, the output = 0 if both strings are equal
    if((strcmp(first_command, "Blue") == 0))
    {
        if(strcmp(second_command, "ON") == 0)
        {
            BLUE_LED_SetHigh();
        }
        else
        {
            BLUE_LED_SetLow();
        }
    }
    else if((strcmp(first_command, "Red") == 0))
    {
        if(strcmp(second_command, "ON") == 0)
        {
            RED_LED_SetHigh();
        }
        else
        {
            RED_LED_SetLow();
        }
    }
    else
    {
        printf("\nInvalid LED selection");
    }

    
}


void TAS2521_Communication(void)
{
    uint8_t i2c_data[2];
    
    printf("\n\nI2C interface for the TAS2521");
    printf("\nCommand Syntax (single spaces): Command Reg_Address Reg_Value");
    printf("\nAllowed values:  ");
    printf("\nCommand = Write, Read, Exit, Enable, Disable, Initialize");
    printf("\nReg_Address = decimal register address");
    printf("\nReg_Value = decimal register value");
    
    strcpy(commands[0], "");
    
    while(strcmp(commands[0], "Exit") != 0)
    {
        printf("\n\nCommand: ");
        
        command_count = Read_Commands(commands);
             
        i2c_data[0] = atoi(commands[1]);  //Register Address
        i2c_data[1] = atoi(commands[2]);  //Register Data

        
        //Now check to see what the command was, and 
        //  act accordingly
        if(strcmp(commands[0], "Exit")==0)
        {
            //break out of the while loop, should return to the main menu
            break;
        }
        else if(strcmp(commands[0], "Initialize")==0)
        {
            TAS2521_Initialize();
        }
        //Perform an I2C master write command
        else if(strcmp(commands[0], "Write")==0)
        {
            //I2C_MasterWrite(
                                //uint8_t *pdata,
                                //uint8_t length,
                                //uint16_t address,
                                //I2C_MESSAGE_STATUS *pflag)
            while(!I2C_MasterQueueIsEmpty())
            {}
            I2C_MasterWrite(i2c_data, 2, TAS_ADDR, &status);  //need to shift the ADDR?  Can't remember?
        }
        else if (strcmp(commands[0], "Read")==0)
        {
            //do something for read eventually
            
        }
        else if (strcmp(commands[0], "Enable")==0)
        {
            TAS_RST_B_SetHigh();
        }
        else if (strcmp(commands[0], "Disable")==0)
        {
            TAS_RST_B_SetLow();
        }
    }
}


void MAX17048_Communication(void)
{
    uint8_t i2c_data[2];
    uint8_t ReadData = 0;
    
    printf("\n\nI2C interface for the TAS2521");
    printf("\nCommand Syntax (single spaces): Command Reg_Address Reg_Value");
    printf("\nAllowed values:  ");
    printf("\nCommand = Write, Read, Exit");
    printf("\nCan Read Percent or Voltage");
    printf("\nReg_Address = decimal register address");
    printf("\nReg_Value = decimal register value");
    
    strcpy(commands[0], "");
    
    while(strcmp(commands[0], "Exit") != 0)
    {
        printf("\n\nCommand: ");

        command_count = Read_Commands(commands);
             
        i2c_data[0] = atoi(commands[1]);  //Register Address
        i2c_data[1] = atoi(commands[2]);  //Register Data

        
        //Now check to see what the command was, and 
        //  act accordingly
        if(strcmp(commands[0], "Exit")==0)
        {
            //break out of the while loop, should return to the main menu
            break;
        }
        //Perform an I2C master write command
        else if(strcmp(commands[0], "Write")==0)
        {
            //I2C_MasterWrite(
                                //uint8_t *pdata,
                                //uint8_t length,
                                //uint16_t address,
                                //I2C_MESSAGE_STATUS *pflag)
            while(!I2C_MasterQueueIsEmpty())
            {}
            I2C_MasterWrite(i2c_data, 2, BATT_ADDR, &status);  //need to shift the ADDR?  Can't remember?
        }
        else if (strcmp(commands[0], "Read")==0)
        {
            if(strcmp(commands[1], "Percent")==0)
            {
                ReadData = Read_Battery_Percent();
                printf("\n\nBatt Percent = %d\n\n", ReadData);
            }
            else if(strcmp(commands[1], "Voltage")==0)
            {
                ReadData = Read_Battery_Voltage();
                printf("\n\nBatt Voltage = %d\n", ReadData);
                printf("Actual voltage = (Batt Voltage << 8) * 156.25uV");
            }
            else
            {
                ReadData = Read_Battery_Register(atoi(commands[1]));
                printf("\n\nRegister Data = 0x%x", ReadData);
            }
        }
        
    }
}






void ADC_Debug(void)
{
    printf("\n\nADC Debug options");
    printf("\nAllowed values:  ");
    printf("\nCommand = Read, Stream, Exit");
    
    strcpy(commands[0], "");
    
    while(strcmp(commands[0], "Exit") != 0)
    {
        printf("\n\nCommand: ");

        command_count = Read_Commands(commands);


        
        //Now check to see what the command was, and 
        //  act accordingly
        if(strcmp(commands[0], "Exit")==0)
        {
            //break out of the while loop, should return to the main menu
            break;
        }
        //Perform an I2C master write command
        else if(strcmp(commands[0], "Read")==0)
        {
            printf("\nConversion = %u", ADC_Data);
        }
        else if (strcmp(commands[0], "Stream")==0)
        {//are you still on the computer?  I am right now!!! :-P
        
            //Run this loop until something is received on the UART from the console
            while(EUSART1_DataReady == 0)
            {
                if(ADC_Data_Ready == 1)
                {
                    ADC_Data_Ready = 0;
                    printf("\nConversion = %u", ADC_Data);
                }
            }
        
        }
        
    }
}




void Battery_Display(void)
{
    printf("\n\nBattery Display debug");
    printf("\nAllowed commands:  ");
    printf("\nI [battery percent]");
    printf("\nD [1, 0]");
    printf("\nX [x pixel offset]");
    printf("\nY [y pixel offset]");
    printf("\nEcho");
    printf("\nExit");
    
    strcpy(commands[0], "");
    
    while(strcmp(commands[0], "Exit") != 0)
    {
        printf("\n\nCommand: ");

        command_count = Read_Commands(commands);
        
        //Now check to see what the command was, and 
        //  act accordingly
        if(strcmp(commands[0], "Exit")==0)
        {
            //break out of the while loop, should return to the main menu
            break;
        }
        //Perform an I2C master write command
        else if(strcmp(commands[0], "I")==0)
        {
            //update the on screen icon
            Update_Battery_Icon(atoi(commands[1]));
        }
        else if (strcmp(commands[0], "D")==0)
        {
            //update the battery display
            Update_Battery_Display(atoi(commands[1]));
        }
        else if (strcmp(commands[0], "X")==0)
        {
            //update the Xoffset
            Update_X_Offset(atoi(commands[1]));
        }
        else if (strcmp(commands[0], "Y")==0)
        {
            //update the Yoffset
            Update_Y_Offset(atoi(commands[1]));
        }
        else if (strcmp(commands[0], "Echo")==0)
        {
            uint8_t data[2] = {'E','Q'};
            EUSART2_Write_Array(data, sizeof(data));
        }
        
    }
}



void Screen_Brightness_Debug(void)
{
       
    strcpy(commands[0], "");
    
    while(strcmp(commands[0], "Exit") != 0)
    {
        printf("\n\nScreen Brightness debug (Exit to exit)");
        printf("\nPWM Value:  ");

        command_count = Read_Commands(commands);
        
        //Now check to see what the command was, and 
        //  act accordingly
        if(strcmp(commands[0], "Exit")==0)
        {
            //break out of the while loop, should return to the main menu
            break;
        }
        else
        {
            EPWM1_LoadDutyValue(atoi(commands[0]));
        }
        
        
    }
}




/*
 *
 * Reads commands from the console, and parses them into
 *  an array of strings.  That array is stored in the variable
 *  that was passed into this function
 * 
 */
unsigned char Read_Commands(char cmds[][16])
{
    char str[128];
    char delim[] = " ,-";
    char* token;
    char i = 0;
    unsigned char counter = 0;
    char flush = 0;
     
    while(str[i-1] != '\n' && str[i-1] != '\r')
    {
        str[i] = getch();
        i++;               
    }    
    //be sure to terminate the string properly
    str[i-1] = '\0';
    
    //flush out the receive buffer to get rid of the \n and \r and stuff
    while(EUSART1_DataReady)
    {
        flush = EUSART1_Read();
    }
      
    //Split the input string into an array of strings, separated by
    //  the given delimiters (in the variable at the top)
    //Put the split strings into the array that was passed into this
    //  function, then will use that info in the calling function
    for (token = strtok(str, delim); token; token = strtok(NULL, delim))
    {
        strcpy(&(cmds)[counter], token);
        //printf("\ntoken=%s\n", token);
        counter++;
    }
    
    //return the number of commands that were found
    return counter;
}




void Debug_Mode(void)
{
    
    if(Red_Blink_Timer > QUARTER_SECONDS(1))
    {
        Red_Blink_Timer = 0;
        RED_LED_Toggle();
    }
    
    SCREEN_SW_SetHigh();
    
    BLUE_LED_LAT = !B_BTN_GetValue();
    BLUE_LED_LAT = !BRIGHTNESS_GetValue();
    
    //Go to the debug menu only if a D is detected on the UART
    if(EUSART1_DataReady)
    {
        if('D' == EUSART1_Read())
        {
            DebugMenu();
        }
    }
    
    //PWR_SW_Check(); //make sure to check the power switch!!
}