#ifndef prototype_H
#define prototype_H
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/eeprom.h"
volatile extern uint8_t key; 
volatile extern int flag;   
void Listinit(void);
void writeContact(uint32_t list);
uint32_t ReadContact();
void LCD_Init(void);
void writePin(volatile unsigned long *port, uint8_t pin, uint8_t lead);
void lcd_data(unsigned char data);
void delayMicroSec(uint32_t n);
void delayMilliSec(uint32_t n);
void lcd_Command(unsigned char  cmnd);
void intTochar(uint32_t y);
uint32_t charToint(uint8_t ch);
void keypad_init(void);
unsigned char readKeypad(void);
void store(uint32_t number);
void calculate_operand(uint8_t arr[],uint32_t c);
void error(void);
void PortCIntHandler(void);
void clear (void);
void TimeRTCinint(void);
#endif 