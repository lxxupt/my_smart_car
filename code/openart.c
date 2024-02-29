#include "zf_common_headfile.h"
#include "openart.h"

ArtState Art_state = ArtGetpoint;
uint8 read_flag = 1;
bool recieve_flag = false;  //ART接收标志位
extern bool Identi_flag;
extern CarState Move_state;  //车俩运动状态
extern ObjState Objc_state;

uint8 Art_data;
uint8 point_num;
uint8 POINT_NUM[32];
uint8 POINT_DATA[128];
uint8 receieve_buffer[2];
uint8 Yellow[8];
uint16 Yellow_point = 0;
uint8 Big_data;
uint8 Small_data;

uint8 Obj_data;
uint8 Obj_Buffer[16];
uint16 X_num = 0;
uint16 Y_num = 0;

/*
* @fuction: ART初始化
* @param: void
*/
void Art_Init(void)
{
	uart_init(ART1, 115200, ART1_TX, ART1_RX);
	uart_rx_interrupt(ART1, 1);
//	interrupt_set_priority(LPUART1_IRQn, 0);
	
	uart_init(ART2, 115200, ART2_TX, ART2_RX);
	uart_rx_interrupt(ART2, 1);
//	interrupt_set_priority(LPUART4_IRQn, 1);
}

/*
* @fuction: 读取ART数据
* @param: void
*/
void Art_Read(void)
{
	if(uart_query_byte(ART1,&Art_data))
	{
		//获取识别后的分类信息
		if(Art_state == ArtIdentify && recieve_flag == true)
		{
			static uint8 index = 0;
			receieve_buffer[index] = Art_data-48;
			index++;
			BeepON;
			if(index>=2)
			{
				Big_data = receieve_buffer[0];
				Small_data = receieve_buffer[1];
				index = 0;
				recieve_flag = false;
				Identi_flag = true;
				BeepOFF;
			}
		}
		//根据坐标纸获取点位信息
		else if(Art_state == ArtGetpoint)
		{
			static uint8 i1 = 0;
			static uint8 i2 = 0;
			if(read_flag == 1) // 获取点位数目
			{
				POINT_NUM[i1] = Art_data-48;
				i1++;
				if(i1>=2)
				{
					BeepON;
					point_num = POINT_NUM[0]*10+POINT_NUM[1];
					i1 = 0;
					read_flag = 2;
				}
			}
			else if(read_flag == 2) // 接收数据--点位坐标信息
			{
				POINT_DATA[i2] = Art_data-48;
				i2++;
				if(i2>=point_num*4)
				{
					i2 = 0;
					read_flag = 0;
					BeepOFF;
				}
			}
		}
		
//		if(Art_state == ART_Yellow)
//		{
//			static uint8 y_index = 0;
//			Yellow[y_index++] = Art_data - '0';
//			if(y_index >= 4)
//			{
//				if(Yellow[0] == 'H' - '0')
//				{
//					Yellow_point = Yellow[1]*100 + Yellow[2]*10 + Yellow[3];
//					y_index = 0;
//				}
//			}
//		}
	}
}

void ART_Read_test(void)
{
	if(uart_query_byte(ART1,&Art_data))
	{
		static uint8 index = 0;
		receieve_buffer[index] = Art_data-48;
		index++;
		BeepON;
		if(index>=2)
		{
			Big_data = receieve_buffer[0];
			Small_data = receieve_buffer[1];
			index = 0;
			BeepOFF;
		}
	}
}

/*
* @fuction: 发送标志，开启目标检测
* @param: void
*/
void Obj_Detection_Start(void)
{
	uart_write_byte(ART2,0x33);//数据可更改
}

/*
* @fuction: 读取目标检测的返回值
* @param: void
*/
void Obj_Detection_Read(void)
{
	static uint8 cnt = 0;
	if(uart_query_byte(ART2,&Obj_data))
	{
//		BeepON;
		if(Move_state == ObjScan)
		{
			Obj_Buffer[cnt++] = Obj_data - '0';
			if(cnt >= 9)
			{
				if(Obj_Buffer[4] == 'M'-'0')
					X_num = Obj_Buffer[1]*100 + Obj_Buffer[2]*10 + Obj_Buffer[3];
				if(Obj_Buffer[8] == 'E'-'0')
					Y_num = Obj_Buffer[5]*100 + Obj_Buffer[6]*10 + Obj_Buffer[7];
				Objc_state = ObjStart;
				cnt = 0;
			}
		}
		
		
	}
}