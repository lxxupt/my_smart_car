#include "zf_common_headfile.h"
#include "init.h"

/*
* @fuction: 板面外设初始化
* @param: void
*/
void Board_Init(void)
{
	system_delay_ms(1000);
	//驱动控制IO初始化
	gpio_init(Motor_control,GPO,1,GPO_PUSH_PULL);
	//外设控制IO初始化
	gpio_init(Core_control ,GPO,1,GPO_PUSH_PULL);
//	//电磁铁初始化
//	gpio_init(MAG ,GPO,0,GPO_PUSH_PULL);
	//灯板初始化
	gpio_init(Light,GPO,1,GPO_PUSH_PULL);
	//蜂鸣器初始化
//	gpio_init(BEEP,GPO,0,GPO_PUSH_PULL);
//	BeepON;
	
	//按键拨码初始化
//	Key_Init();
	//电机初始化
	Motor_Init();
	//编码器初始化
//	Encoder_Init();
	//机械臂舵机初始化
//	Steer_Init();
//	Core_OPEN;
//	Motor_OPEN;
	
	//屏幕初始化
	tft180_init();
	tft180_full(RGB565_BLUE);
//	//摄像头初始化
//	mt9v03x_init();            
	//陀螺仪初始化
	tft180_show_string(0,0,"Ms601 Waiting");
	atk_ms601m_init(115200);  /******UART_8*******/
	system_delay_ms(500);
	gyroOffsetInit();
	tft180_show_string(0,0,"Ms601 OK!");
	tft180_full(RGB565_BLUE);
	
	//定时器初始化
	pit_ms_init(PIT_CH0,2);//电机控制定时器
//	pit_ms_init(PIT_CH1,5);//获取坐标定时器
//	pit_ms_init(PIT_CH2,2);//陀螺仪定时器
//	pit_ms_init(PIT_CH3,10);//DEBUG
	
	//蓝牙初始化
//	uart_init(Blue_tooth, 115200, Blue_TX, Blue_RX);
//	uart_init(UART_5, 115200, UART5_TX_C28, UART5_RX_C29);
//	uart_init(UART_8, 115200, UART8_TX_D16, UART8_RX_D17);
	//ART串口初始化
//	Art_Init();
//	
//	BeepOFF;
//	interrupt_global_enable(0);
}
