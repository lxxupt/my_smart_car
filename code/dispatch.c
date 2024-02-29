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

	�Ÿ籣��               ����BUG
	�Ÿ籣��               ����BUG
	�Ÿ籣��               ����BUG
	�Ÿ籣��               ����BUG 
 *  Created on: 2023��5��22��
 *  Author: Ghost
--------------------------------------------------------------*/
#include "zf_common_headfile.h"
#include "dispatch.h"

fifo_struct bluetooth_receive_fifo;                                 //fifo�ṹ��
uint8 	receive_fifo_buffer[128] 	= {0}; 							// fifo���ݴ洢λ��
uint8 	receive_buffer[64] 	= {0}; 									// �������ݴ��λ��

uint8 	receive_data[64]	= {0};									// ������ɵ����ݴ��λ��
uint8 	one_bag_receive_flag = 0;									// ������־λ   1�����ڽ�������   0������
uint8 	one_bag_num = 0;											// ��������ID

uint8 Send_Buffer[64] = {0};
uint8 data_test[10] = {0,1,2,3,4,5,6,7,8,9};


void Dispatch_Rexeive_Init(void)
{
	fifo_init (&bluetooth_receive_fifo, FIFO_DATA_8BIT, receive_fifo_buffer, sizeof(receive_fifo_buffer));	// ��ʼ������fifo������
	uart_init(Blue_tooth1, 115200, Blue_TX1, Blue_RX1);
	uart_rx_interrupt(Blue_tooth1, 1);
}


void Bluetooh_Callback(void)
{
	uint8  data_temp = 0;
	uint32 receive_count = 0;

	uart_query_byte(Blue_tooth1,&data_temp);                      //��ȡ��������
	fifo_write_buffer(&bluetooth_receive_fifo,&data_temp,1);                 //����FIFO
	if(data_temp == '\n')                                                    //���յ�֡β����
	{
		if(one_bag_receive_flag == 0)                                          //���û���ڽ������ݣ���ô�����ݶ�ȡ����������������λ������־λ
		{
		  receive_count = fifo_used(&bluetooth_receive_fifo);                  //��ȡfifo����������
		  fifo_read_buffer(&bluetooth_receive_fifo,&receive_buffer,&receive_count,FIFO_READ_AND_CLEAN);// ��ȡ FIFO ���ݵ�������
		  one_bag_receive_flag = 1;
		}
		else
		{
		  fifo_clear(&bluetooth_receive_fifo);                                 // ������ڽ������ݣ�����������ݣ��´��ٽ���
		}
	}
}

void Data_Parse(void)
{
	uint8 verify_data[4] 		= {0};
	uint8 data_temp 			= 0;
	uint8 data_count 			= 0;

	data_count = strlen((char *)receive_buffer);					// ͳ��������ݳ���

	memset(receive_data, 0, sizeof(receive_data));					// ����ϴν��յ�������

	for(uint8 i = 3; i < data_count; i ++) 							// �����������ݺ�
	{
		data_temp +=  receive_buffer[i];
	}

	func_hex_to_str((char *)verify_data, data_temp);

	if(data_temp < 16) 												// func_hex_to_str����ת��0x0F�Ľ����0xF  �����Ҫ��λ
	{
		verify_data[3] = verify_data[2];
		verify_data[2] = 0x30;
	}

	if(verify_data[2] == receive_buffer[0] && verify_data[3] == receive_buffer[1])				// ��У��
	{ 
		bluetooth_ch9141_send_buffer(&receive_buffer[3], 2); 										// �ظ����ݰ�ID����֪����ģ��������
		
		one_bag_num = (receive_buffer[3] - 0x30) * 16 + (receive_buffer[4]- 0x30);				// ��ȡ���ݰ�ID
		
		strncpy((char *)receive_data, (char *)&receive_buffer[6], data_count - 6);				// ��������ȡ��
		
	}
	memset(receive_buffer, 0, sizeof(receive_buffer));				// ��ջ�����					

	one_bag_receive_flag = 0;										// ��������
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

