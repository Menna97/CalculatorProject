#include "prototype.h"

// PORTE(PE0-PE3) for Rows
// PORTC(PC4-PC7) for Columns

void keypad_init(void)
{
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {
    }
  GPIOIntRegister(GPIO_PORTC_BASE, PortCIntHandler);
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOOutputOD(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  GPIOIntTypeSet(GPIO_PORTC_BASE,GPIO_PIN_4 |GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 , GPIO_FALLING_EDGE);
  GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 |GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
}

unsigned char readKeypad(void){
  
    const unsigned char keymap[4][4] = {
        {'1' , '2' , '3' , '+'},
        {'4' , '5' , '6' , '-'},
        {'7' , '8' , '9' , '*'},
        {'=' , '0' , 'C' , '/'}
    };
    
    int row,col;
    
    GPIO_PORTE_DATA_R = 0; //enable rows;
    delayMilliSec(200);
    col = GPIO_PORTC_DATA_R & 0xF0;
    if (col == 0xF0)
        return 0;
    
    while(1)
    {
        row = 0;
        GPIO_PORTE_DATA_R = 0x0E;
        delayMilliSec(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
            break;
        
        row = 1;
        GPIO_PORTE_DATA_R = 0x0D;
        delayMilliSec(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
            break;
        
        row = 2;
        GPIO_PORTE_DATA_R = 0x0B;
        delayMilliSec(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
            break;
        
        row = 3;
        GPIO_PORTE_DATA_R = 0x07;
        delayMilliSec(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if(col != 0xF0)
            break;
        
        return 0;
    }
    
    if (col == 0xE0) return keymap[row][0];
    if (col == 0xD0) return keymap[row][1];
    if (col == 0xB0) return keymap[row][2];
    if (col == 0x70) return keymap[row][3];
    
    return 0;
 
}

void PortCIntHandler(void){
 flag=1;
 GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
 key=readKeypad();
 delayMilliSec(200);
}