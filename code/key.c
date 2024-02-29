#include "zf_common_headfile.h"
#include "key.h"

uint8 project_modo = 0;
uint8 mubiao_data = 0;

extern uint8 find_flag; 
extern bool recieve_flag;
extern CarState Move_state;
extern CorrState Corr_state;
extern TranState Tran_state;

/*
* @fuction: 按键拨码初始化
* @param: void
*/
void Key_Init(void)
{
	//拨码开关初始化
	gpio_init(Boma1pin, GPI, 1, GPI_PULL_UP);
	gpio_init(Boma2pin, GPI, 1, GPI_PULL_UP);
	gpio_init(Boma3pin, GPI, 1, GPI_PULL_UP);
	gpio_init(Boma4pin, GPI, 1, GPI_PULL_UP);
	//按键初始化
	gpio_init(Key1pin, GPI, 1, GPI_PULL_UP);
	gpio_init(Key2pin, GPI, 1, GPI_PULL_UP);
	gpio_init(Key3pin, GPI, 1, GPI_PULL_UP);
	
}

void Key_Scan(uint8 mode)
{
	static uint8 key_up = 1;   //按键松开标志
	static uint8 boma_num = 0;
	boma_num = Boma1*1 + Boma2*2 + Boma3*4 + Boma4*8;
	tft180_show_uint(140,110,boma_num,2);
	if(mode)
		key_up = 0;            //支持连按
	if(key_up && (Key1==0||Key2==0||Key3==0))
	{
		system_delay_ms(10);
		key_up = 0;
		if(Key1 == 0)
		{
			uart_write_string (ART1, "D");
		}
		else if(Key2 == 0)
		{
			find_flag = 1;
		}
		else if(Key3 == 0)
		{
			uart_write_string (ART1, "a");
			tft180_clear();
		}
	}
	else if(Key1==1&&Key2==1&&Key3==1)
		key_up = 1;
	
	if(Boma1)
		mubiao_data = 1;
	if(Boma2)
		mubiao_data = 2;
	if(Boma3)
		mubiao_data = 3;
	if(Boma4)
		project_modo = 1;
}

void Key_Scan_test(uint8 mode)
{
	static uint8 key_up = 1;   //按键松开标志
	static uint8 boma_num = 0;
	boma_num = Boma1*1 + Boma2*2 + Boma3*4 + Boma4*8;
	tft180_show_uint(140,110,boma_num,2);
	if(mode)
		key_up = 0;            //支持连按
	if(key_up && (Key1==0||Key2==0||Key3==0))
	{
		system_delay_ms(10);
		key_up = 0;
		if(Key1 == 0)
		{
//			LightOFF;
//			a += 1;
//			Corr_state = CorrStart;
//			Tran_state = TranStart;
			Move_state = ObjScan;
//			uart_write_byte(ART2,0x51);
		}
		else if(Key2 == 0)
		{
			Art_state = ArtIdentify;
			uart_write_byte(ART2,0x39);
			uart_write_string (ART1, "D");
//			find_flag = 1;
//			RoboticArm_bodong(0);
//			LightON;
//			a -= 1;
		}
		else if(Key3 == 0)
		{
//			uart_write_byte(ART1,0x36);
			gpio_toggle_level(D27);
//			RoboticArm_bodong(2);
//			
//			a = 100;
		}
	}
	else if(Key1==1&&Key2==1&&Key3==1)
		key_up = 1;
	
	
	if(Boma1)
		mubiao_data = 1;
	if(Boma2)
		mubiao_data = 2;
	if(Boma3)
		mubiao_data = 3;
	if(Boma4)
		project_modo = 1;
	if(!Boma4)
		project_modo = 0;
	
	tft180_show_uint(0,20,mubiao_data,2);
	tft180_show_uint(0,40,project_modo,2);
}