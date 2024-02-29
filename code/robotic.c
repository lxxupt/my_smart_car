#include "zf_common_headfile.h"
#include "robotic.h"

extern TranState Tran_state;

void Steer_Init(void)
{
	pwm_init(steer_1,50,665);
	pwm_init(steer_2,50,1250);
	pwm_init(steer_3,50,750);
	pwm_init(steer_4,50,300);
}

/*
* @brief: 机械臂抓取卡片
* @param: none
* @return:true
* @note:  当标志位Tran_state为TranStart时执行
* @time:  2023/03/15
* @author:WXQ
*/
bool RoboticArm_greb(void)
{
	Mag_ON;
	system_delay_ms(100);
	pwm_set_duty(steer_3,1175);
	pwm_set_duty(steer_2,640);
	system_delay_ms(470);//
	pwm_set_duty(steer_2,550);
	system_delay_ms(150);//
	pwm_set_duty(steer_2,950);
	pwm_set_duty(steer_3,550);
	system_delay_ms(100);
	
	return true;
}

/*
* @brief: 机械臂释放卡片
* @param: none
* @return:true
* @note:  当标志位Tran_state为TranLoading时执行
* @time:  2023/03/15
* @author:WXQ
*/
bool RoboticArm_freed(void)
{
	pwm_set_duty(steer_2,930);
	system_delay_ms(200);
	pwm_set_duty(steer_3,1050);
	system_delay_ms(300);
	Mag_OFF;//----电磁铁关闭-----
	system_delay_ms(50);
	pwm_set_duty(steer_3,750);
	pwm_set_duty(steer_2,1250);
	pwm_set_duty(steer_1,665);
	
	return true;
}

/*
* @brief: 旋转机械臂
* @param: data 识别小分类结果
* @return:true
* @note:  当标志位****为**时执行
* @time:  2023/03/15
* @author:WXQ
*/
bool RoboticArm_revole(uint8 data)
{	
	switch(data)
	{
		case 0:pwm_set_duty(steer_1,435);break;//665
		case 1:pwm_set_duty(steer_1,435);break;//665
		case 2:pwm_set_duty(steer_1,910);break;//415
		case 3:pwm_set_duty(steer_1,280);break; //280
		case 4:pwm_set_duty(steer_1,1070);break;  //1070
		case 5:pwm_set_duty(steer_1,1070);break;  //915 
		case 6:pwm_set_duty(steer_1,280);break;
	}
	
 	return true;
}

bool RoboticArm_revole_J(uint8 data)
{	
	switch(data)
	{
		case 0:pwm_set_duty(steer_1,435);break;//665
		case 1:pwm_set_duty(steer_1,435);break;//665
		case 2:pwm_set_duty(steer_1,910);break;//415
		case 3:pwm_set_duty(steer_1,1070);break; //280
		case 4:pwm_set_duty(steer_1,1070);break;  //1070
		case 5:pwm_set_duty(steer_1,1070);break;  //915 
		case 6:pwm_set_duty(steer_1,280);break;
	}
	
 	return true;
}

bool RoboticArm_bodong(uint8 data)
{
	switch(data)
	{
		case 0:pwm_set_duty(steer_1,550);break;
		case 1:pwm_set_duty(steer_1,400);break;
		case 2:pwm_set_duty(steer_1,910);break;
		case 3:pwm_set_duty(steer_1,725);break;//725
	}
	system_delay_ms(500);
	pwm_set_duty(steer_4,450);
	system_delay_ms(300);
	pwm_set_duty(steer_4,300);
	pwm_set_duty(steer_1,665);
 	return true;
}

bool RoboticArm_bodong_J(uint8 data)
{
	switch(data)
	{
		case 0:pwm_set_duty(steer_1,725);break;
		case 1:pwm_set_duty(steer_1,400);break;
		case 2:pwm_set_duty(steer_1,910);break;
		case 3:pwm_set_duty(steer_1,725);break;//725
	}
	system_delay_ms(500);
	pwm_set_duty(steer_4,450);
	system_delay_ms(300);
	pwm_set_duty(steer_4,300);
	pwm_set_duty(steer_1,665);
 	return true;
}

void Robot_test(void)
{
	if(Tran_state == TranStart)
	{
		RoboticArm_greb();
		system_delay_ms(150);
		Tran_state = TranGet;
	}
	else if(Tran_state == TranLoading)
	{
		RoboticArm_freed();
		Tran_state = TranFinish;
	}

}