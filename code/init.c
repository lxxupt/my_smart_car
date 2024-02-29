#include "zf_common_headfile.h"
#include "init.h"

/*
* @fuction: ���������ʼ��
* @param: void
*/
void Board_Init(void)
{
	system_delay_ms(1000);
	//��������IO��ʼ��
	gpio_init(Motor_control,GPO,1,GPO_PUSH_PULL);
	//�������IO��ʼ��
	gpio_init(Core_control ,GPO,1,GPO_PUSH_PULL);
//	//�������ʼ��
//	gpio_init(MAG ,GPO,0,GPO_PUSH_PULL);
	//�ư��ʼ��
	gpio_init(Light,GPO,1,GPO_PUSH_PULL);
	//��������ʼ��
//	gpio_init(BEEP,GPO,0,GPO_PUSH_PULL);
//	BeepON;
	
	//���������ʼ��
//	Key_Init();
	//�����ʼ��
	Motor_Init();
	//��������ʼ��
//	Encoder_Init();
	//��е�۶����ʼ��
//	Steer_Init();
//	Core_OPEN;
//	Motor_OPEN;
	
	//��Ļ��ʼ��
	tft180_init();
	tft180_full(RGB565_BLUE);
//	//����ͷ��ʼ��
//	mt9v03x_init();            
	//�����ǳ�ʼ��
	tft180_show_string(0,0,"Ms601 Waiting");
	atk_ms601m_init(115200);  /******UART_8*******/
	system_delay_ms(500);
	gyroOffsetInit();
	tft180_show_string(0,0,"Ms601 OK!");
	tft180_full(RGB565_BLUE);
	
	//��ʱ����ʼ��
	pit_ms_init(PIT_CH0,2);//������ƶ�ʱ��
//	pit_ms_init(PIT_CH1,5);//��ȡ���궨ʱ��
//	pit_ms_init(PIT_CH2,2);//�����Ƕ�ʱ��
//	pit_ms_init(PIT_CH3,10);//DEBUG
	
	//������ʼ��
//	uart_init(Blue_tooth, 115200, Blue_TX, Blue_RX);
//	uart_init(UART_5, 115200, UART5_TX_C28, UART5_RX_C29);
//	uart_init(UART_8, 115200, UART8_TX_D16, UART8_RX_D17);
	//ART���ڳ�ʼ��
//	Art_Init();
//	
//	BeepOFF;
//	interrupt_global_enable(0);
}
