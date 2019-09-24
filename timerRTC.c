#include "prototype.h"
#define GPIO_PB4_T1CCP0   0x00011007

void TimeRTCinint(void){
  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB4_T1CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_4);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_RTC);
    TimerRTCEnable(TIMER1_BASE);
    TimerLoadSet64(TIMER1_BASE, 45);
    TimerEnable(TIMER1_BASE, TIMER_A);
    

}