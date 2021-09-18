/*
File Name:LCD_program
Author:DohaOsama
Date:18/9/2021
Description:LCD Driver 
version 1.0
*/

//Inclusion of library
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
//Inclusion of lower layers

#include "../../MCAL/DIO/DIO_interface.h"

//Inclusion of self layer
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

#include <util/delay.h>

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,LOW);//output for now
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);//output for now
	DIO_voidSetPortSpecificValue(LCD_DATA_PORT,Copy_u8Command);//insert data in portdata
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);//after inserting the data read the command by enabling it
	_delay_ms(2);//high for 2 ms
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);//after reading the command close the enable to not read any un wanted data
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,HIGH);//output for now
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);//output for now
	DIO_voidSetPortSpecificValue(LCD_DATA_PORT,Copy_u8Data);//insert data in portdata
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);//after inserting the data read the command by enabling it
	_delay_ms(2);//high for 2 ms
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);//after reading the command close the enable to not read any un wanted data
}
void LCD_voidLint(void)
{
	DIO_voidSetPortDirection(LCD_DATA_PORT,OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_EN_PIN,OUTPUT);
	_delay_ms(40);
	LCD_voidSendCommand(FunctionSet);
	LCD_voidSendCommand(DisplayOn_Off);
	LCD_voidSendCommand(ClearDisplay);
}
void LCD_voidGoToXY(u8 Copy_u8XPosition,u8 Copy_u8YPosition)//function to start from a specific position in lcd
{
	u8 Local_u8DDRAMAddress;//CKECK where exactly the position
	if(Copy_u8XPosition==0)
	{
		Local_u8DDRAMAddress=Copy_u8YPosition;	
	}
	else if(Copy_u8XPosition==1)
	{
		Local_u8DDRAMAddress=Copy_u8YPosition+DDRAM_CONST_ADDRESS;
	}
	//set bit no 7 to be 1 talk to DDRAM
	SET_BIT(Local_u8DDRAMAddress,7);
	//send the command
	LCD_voidSendCommand(Local_u8DDRAMAddress);
}
void LCD_voidSendString(u8*Copy_pu8strings)
{
	while(*Copy_pu8strings!='\0')//check if the pointer points to the null pointer inside the pointer itself
	//another way while(copy_pu8string[Local_u8Counter]!='0')
	{
		//u8 Local_u8Counter=0;
		LCD_voidSendData(*Copy_pu8strings);//send data inside the pointer  to lcd
		//LCD_voidSendData(copy_pu8string[Local_u8Counter]);
		//Local_u8Counter++;
		Copy_pu8strings++;//increment the address of the pointer to point to next location
	}	
}
void LCD_voidSendCustomPattern(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	u8 Local_u8Counter=0;
	u8 Local_u8CGRAMAddress;
	//set the CGRAM Address to the pattern to be saved
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;
	SET_BIT(Local_u8CGRAMAddress,6);
	//send the set CGRAM Address Command
	LCD_voidSendCommand(Local_u8CGRAMAddress);
	//send data to the data portdata
	for(Local_u8Counter=LOW;Local_u8Counter<8;Local_u8Counter++)//LOW=0
	{
		LCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	LCD_voidGoToXY(Copy_u8XPosition,Copy_u8YPosition);
	LCD_voidSendData(Copy_u8PatternNumber);
}

