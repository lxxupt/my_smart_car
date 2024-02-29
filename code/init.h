#ifndef _INIT_H_
#define _INIT_H_
#include "zf_common_headfile.h"

//------------�����ϵ����---------
#define Core_control D26
#define Core_OPEN  gpio_set_level(Core_control,1)
#define Core_CLOSE gpio_set_level(Core_control,0)

//------------�����ϵ����---------
#define Motor_control D4
#define Motor_OPEN  gpio_set_level(Motor_control,1)
#define Motor_CLOSE gpio_set_level(Motor_control,0)

//------------�����---------------
#define MAG C4
#define Mag_ON   gpio_set_level(MAG,1)
#define Mag_OFF  gpio_set_level(MAG,0)

//-------------������-------------
#define BEEP C31
#define BeepON   gpio_set_level(BEEP,1)
#define BeepOFF  gpio_set_level(BEEP,0)

//-------------�ư�---------------
#define Light B9
#define LightON  gpio_set_level(Light,0)
#define LightOFF gpio_set_level(Light,1)
#define Light_toggle gpio_toggle_level(Light)
//--------------����--------------
#define Blue_tooth  UART_3
#define Blue_TX     UART3_TX_C8
#define Blue_RX     UART3_RX_C9

void Board_Init(void);

#endif