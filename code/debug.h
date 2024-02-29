#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "zf_common_headfile.h"

#define VCAN_PORT UART_8

#define  sw_write_byte(dat)  uart_write_byte(UART_3,dat)//���ڷ����ֽ�
#define  sw_write_buffer(dat,len)  uart_write_buffer(UART_3,dat,len)//���ߴ��ڷ�������򴮿ڷ�������

void vcan_sendware(void *wareaddr, uint32_t waresize);
void sendimg_A( uint8* image, uint8 width, uint8 height);
void sendimg_binary_CHK(uint8* image, uint8 width, uint8 height,uint8 otu,uint8 chk);
void send_information(uint8 big,uint8 sma);
void key_debug(Wheel L);
void speed_change(Wheel L);
void alpha_change();
void speed_test(Target V);
#endif