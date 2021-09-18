#ifndef LCD_INTERFACE_H

#define LCD_INTERFACE_H

void LCD_voidLint(void);

void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidGoToXY(u8 Copy_u8XPosition,u8 Copy_u8YPosition);

void LCD_voidSendString(u8*Copy_pu8strings);

void LCD_voidSendCustomPattern(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPosition,u8 Copy_u8YPosition);

#endif