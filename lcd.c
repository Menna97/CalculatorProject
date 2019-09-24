#include "prototype.h"
#include "tm4c123gh6pm.h"
#define RS 5 //port A bit 5 mask
#define RW 6 //port A bit 6 mask
#define EN 7 //port A bit 7 mask
void LCD_Init(void){
    //initialize tiva ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 |GPIO_PIN_6 | GPIO_PIN_7); //set pin 5 and pin 6 and 7 in port A as outputs for control
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3
    |GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6 | GPIO_PIN_7);  
    
    lcd_Command(0x30);		// command 0x30 = Wake up
    delayMilliSec(10);
    
    lcd_Command(0x38); //setting LCD to 2 line, 8-bit data, 5x7 font
    delayMilliSec(200);
    lcd_Command(0x06); //move cursor right
    delayMilliSec(200);
    lcd_Command(0x01); //clear screen, move cursor to home
    delayMilliSec(200);
    lcd_Command(0x0F); //turn on display, blink cursor (now LCD is ready)
    delayMilliSec(200); 
    
    }  

    void writePin(volatile unsigned long *port, uint8_t pin, uint8_t lead){
    if (lead == 1)
    {
        *port |= (0x01 << pin);
    }
    if (lead == 0)
    {
        *port &= ~(0x01 << pin);
    }
}
    void clear (void){
    lcd_Command(0x01);
    delayMilliSec(20);
 }


    void lcd_Command(unsigned char  cmnd){
    GPIO_PORTA_DATA_R = 0x00; //clear Port A data register
    GPIO_PORTB_DATA_R = cmnd; //write command in Port B data register
    writePin(&GPIO_PORTA_DATA_R, EN , 1); //set enable bit in port A for a short pulse
    delayMicroSec(10);
    GPIO_PORTA_DATA_R = 0x00; //then clear enable bit
    if (cmnd < 4) //commands 1,2 need longer delays
        delayMilliSec(2); //they take up to 1.64 ms
    else
        delayMilliSec(40); //all others take 40 us
    }
    void lcd_data(unsigned char data){
    GPIO_PORTA_DATA_R = 0x00; //clear Port A data register
    writePin(&GPIO_PORTA_DATA_R, RS , 1); //to write data RS must be = 1 and RW = 0
    GPIO_PORTB_DATA_R = data; //then write data onto Port B pins
    writePin(&GPIO_PORTA_DATA_R, EN , 1); //then enable for a short pulse
    delayMilliSec(1);
    GPIO_PORTA_DATA_R = 0x00; //then clear control bits (PORT A) again
    delayMilliSec(40);
    }


