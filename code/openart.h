#ifndef _OPENART_H_
#define _OPENART_H_
#include "zf_common_headfile.h"

//-------------ART1--------------
#define ART1    UART_1
#define ART1_TX UART1_TX_B12
#define ART1_RX UART1_RX_B13

//------------ART2---------------
#define ART2    UART_4
#define ART2_TX UART4_TX_C16
#define ART2_RX UART4_RX_C17


typedef enum
{
	ArtGetpoint = 1,
	ArtIdentify,
	ART_Yellow,
}ArtState;

extern ArtState Art_state;
extern uint8 point_num;
extern uint8 POINT_DATA[128];
extern uint8 Big_data;
extern uint8 Small_data;
extern uint16 X_num;
extern uint16 Y_num;
extern uint16 Yellow_point;


void Art_Init(void);
void Art_Read(void);
void ART_Read_test(void);
void Obj_Detection_Start(void);
void Obj_Detection_Read(void);


#endif