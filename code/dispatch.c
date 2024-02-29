/*-------------------------------------------------------------
                       .::::.
                     .::::::::.
                    :::::::::::
                 ..:::::::::::'
              '::::::::::::'
                .::::::::::
           '::::::::::::::..
                ..::::::::::::.
              ``::::::::::::::::
               ::::``:::::::::'        .:::.
              ::::'   ':::::'       .::::::::.
            .::::'      ::::     .:::::::'::::.
           .:::'       :::::  .:::::::::' ':::::.
          .::'        :::::.:::::::::'      ':::::.
         .::'         ::::::::::::::'         ``::::.
     ...:::           ::::::::::::'              ``::.
    ```` ':.          ':::::::::'                  ::::..
                       '.:::::'                    ':'````..

	杜哥保佑               永无BUG
	杜哥保佑               永无BUG
	杜哥保佑               永无BUG
	杜哥保佑               永无BUG 
 *  Created on: 2023年5月22日
 *  Author: Ghost
--------------------------------------------------------------*/
#include "zf_common_headfile.h"
#include "dispatch.h"

fifo_struct bluetooth_receive_fifo;                                 //fifo结构体
uint8 	receive_fifo_buffer[128] 	= {0}; 							// fifo数据存储位置
uint8 	receive_buffer[64] 	= {0}; 									// 单包数据存放位置

uint8 	receive_data[64]	= {0};									// 解析完成的数据存放位置
uint8 	one_bag_receive_flag = 0;									// 解析标志位   1：正在解析数据   0：空闲
uint8 	one_bag_num = 0;											// 单包数据ID

uint8 Send_Buffer[64] = {0};
uint8 data_test[10] = {0,1,2,3,4,5,6,7,8,9};


void Dispatch_Rexeive_Init(void)
{
	fifo_init (&bluetooth_receive_fifo, FIFO_DATA_8BIT, receive_fifo_buffer, sizeof(receive_fifo_buffer));	// 初始化接收fifo缓冲区
	uart_init(Blue_tooth1, 115200, Blue_TX1, Blue_RX1);
	uart_rx_interrupt(Blue_tooth1, 1);
}


void Bluetooh_Callback(void)
{
	uint8  data_temp = 0;
	uint32 receive_count = 0;

	uart_query_byte(Blue_tooth1,&data_temp);                      //读取串口数据
	fifo_write_buffer(&bluetooth_receive_fifo,&data_temp,1);                 //存入FIFO
	if(data_temp == '\n')                                                    //接收到帧尾数据
	{
		if(one_bag_receive_flag == 0)                                          //如果没有在解析数据，那么将数据读取到缓冲区，并且置位解析标志位
		{
		  receive_count = fifo_used(&bluetooth_receive_fifo);                  //读取fifo内数据数量
		  fifo_read_buffer(&bluetooth_receive_fifo,&receive_buffer,&receive_count,FIFO_READ_AND_CLEAN);// 读取 FIFO 数据到缓冲区
		  one_bag_receive_flag = 1;
		}
		else
		{
		  fifo_clear(&bluetooth_receive_fifo);                                 // 如果正在解析数据，则丢弃这包数据，下次再解析
		}
	}
}

void Data_Parse(void)
{
	uint8 verify_data[4] 		= {0};
	uint8 data_temp 			= 0;
	uint8 data_count 			= 0;

	data_count = strlen((char *)receive_buffer);					// 统计这包数据长度

	memset(receive_data, 0, sizeof(receive_data));					// 清空上次接收到的数据

	for(uint8 i = 3; i < data_count; i ++) 							// 计算所有数据和
	{
		data_temp +=  receive_buffer[i];
	}

	func_hex_to_str((char *)verify_data, data_temp);

	if(data_temp < 16) 												// func_hex_to_str函数转换0x0F的结果是0xF  因此需要移位
	{
		verify_data[3] = verify_data[2];
		verify_data[2] = 0x30;
	}

	if(verify_data[2] == receive_buffer[0] && verify_data[3] == receive_buffer[1])				// 和校验
	{ 
		bluetooth_ch9141_send_buffer(&receive_buffer[3], 2); 										// 回复数据包ID，告知发送模块接收完毕
		
		one_bag_num = (receive_buffer[3] - 0x30) * 16 + (receive_buffer[4]- 0x30);				// 获取数据包ID
		
		strncpy((char *)receive_data, (char *)&receive_buffer[6], data_count - 6);				// 所有数据取出
		
	}
	memset(receive_buffer, 0, sizeof(receive_buffer));				// 清空缓冲区					

	one_bag_receive_flag = 0;										// 解析结束
}


void Send_Data(uint8 x,uint8 y,uint8 big,uint8 small,uint8 flag)
{
	Send_Buffer[0] = x/10 + '0';   //x
	Send_Buffer[1] = x%10 + '0';
	  
	Send_Buffer[2] = y/10 + '0';   //y
	Send_Buffer[3] = y%10 + '0';
	
	Send_Buffer[4] = big + '0'; 
	Send_Buffer[5] = small + '0';
	Send_Buffer[6] = flag + '0';
	
	Send_Buffer[7] = '\n';
	uart_write_buffer(UART_8,&Send_Buffer[0],8);
}

void Send_Data_test(void)
{
	Send_Buffer[0] = 1 + '0';   //x
	Send_Buffer[1] = 5 + '0';
	
	Send_Buffer[2] =' ';  
	Send_Buffer[3] = 2 + '0';   //y
	Send_Buffer[4] = 6 + '0';
	
	Send_Buffer[5] =' ';  
	Send_Buffer[6] = 3 + '0';
	
	Send_Buffer[7] =' ';  
	Send_Buffer[8] = 5 + '0';
	Send_Buffer[9] = '\n';
	
	uart_write_buffer(UART_8,&Send_Buffer[0],10);
	
}

