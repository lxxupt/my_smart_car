#ifndef _DISPATCH_H_
#define _DISPATCH_H_
#include "zf_common_headfile.h"

#define Blue_tooth1  UART_5              //车辆间通信
#define Blue_TX1     UART5_TX_C28
#define Blue_RX1     UART5_RX_C29

void Dispatch_Rexeive_Init(void);
void Send_Data_test(void);
void Bluetooh_Callback(void);
void Data_Parse(void);
void Send_Data(uint8 x,uint8 y,uint8 big,uint8 small,uint8 flag);

#endif