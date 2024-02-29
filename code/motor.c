#include "zf_common_headfile.h"
#include "motor.h"

extern wheel Left_Front,Left_Back,Right_Front,Right_Back;

/*
* @fuction: 电机PWM初始化
* @param: void
*/
void Motor_Init(void)
{
	pwm_init(Left_Front_PWM, 15000, 0);
	pwm_init(Right_Front_PWM, 15000, 0);
	pwm_init(Left_Behind_PWM, 15000, 0);
	pwm_init(Right_Behind_PWM, 15000, 0);
	gpio_init(Left_Front_direction,GPO,1,GPO_PUSH_PULL);
	gpio_init(Right_Front_direction,GPO,1,GPO_PUSH_PULL);
	gpio_init(Left_Behind_direction,GPO,1,GPO_PUSH_PULL);
	gpio_init(Right_Behind_direction,GPO,1,GPO_PUSH_PULL);
}

/*
* @fuction: 电机PID参数初始化
* @param: void
*/
void Motor_Param_Init(void)
{
	Left_Front.Ki = 2.234;//2.294;//2.064;//1.015;//2.215;//2.215;//2.566;//1.967    1.266
	Left_Front.Kp = 5.638;//5.698;//5.398;//3.898;//46.599;//33.200;//4.098    2.568
	Left_Front.Kd = 18.481;//18.581;//13.230;//4.671;//-5.399;//6.999;//11.25    5.658

	Left_Back.Ki = 2.234;//2.566;//2.815
	Left_Back.Kp = 5.638;//6.750;//6.198
	Left_Back.Kd = 10.000;//10.95;//12.15

	Right_Front.Ki =2.055;//2.066;// 2.566;//    
	Right_Front.Kp = 8.769;//10.700;//6.85;//
	Right_Front.Kd = 12.299;//13.600;//12.05;//

	Right_Back.Ki = 1.974;//1.965;//2.315;//2.566;//1.919
	Right_Back.Kp = 8.139;//8.099;//-0.850;//7.849;//3.849   7.849
	Right_Back.Kd = 9.528;//9.298;//2.099;//15.899;//10.5
}

/*
* @fuction: pid计算pwm输出
* @param: L 控制车轮的结构体指针
*/
bool Motor_Pid(Wheel L)
{
	L->Last_Err = L->last_err;
	L->last_err = L->error;
	L->error = L->target - L->pulse;
	L->pwm_out += L->Ki * L->error + L->Kp * (L->error - L->last_err) + L->Kd * (L->error - 2*L->Last_Err + L->last_err);
	if(L->pwm_out > 8000) L->pwm_out = 8000;
	else if(L->pwm_out < -8000) L->pwm_out = -8000;
	
	return true;
}


/*
* @fuction: 电机控制
* @param: L1 左前轮
* @param: L2 左后轮
* @param: L3 右前轮
* @param: L4 右后轮
*/
bool PWM_OUT(Wheel L1,Wheel L2,Wheel L3,Wheel L4)
{
	if(L1->pwm_out > 0)
	{
		gpio_set_level(Left_Front_direction,0);
		pwm_set_duty(Left_Front_PWM,L1->pwm_out);
	}
	else
	{
		gpio_set_level(Left_Front_direction,1);
		pwm_set_duty(Left_Front_PWM,-L1->pwm_out);
	}
	
	if(L2->pwm_out > 0)
	{
		gpio_set_level(Left_Behind_direction,0);
		pwm_set_duty(Left_Behind_PWM,L2->pwm_out);
	}
	else
	{
		gpio_set_level(Left_Behind_direction,1);
		pwm_set_duty(Left_Behind_PWM,-L2->pwm_out);
	}
	
	if(L3->pwm_out > 0)
	{
		gpio_set_level(Right_Front_direction,1);
		pwm_set_duty(Right_Front_PWM,L3->pwm_out);
	}
	else
	{
		gpio_set_level(Right_Front_direction,0);
		pwm_set_duty(Right_Front_PWM,-L3->pwm_out);
	}
	
	if(L4->pwm_out > 0)
	{
		gpio_set_level(Right_Behind_direction,1);
		pwm_set_duty(Right_Behind_PWM,L4->pwm_out);
	}
	else
	{
		gpio_set_level(Right_Behind_direction,0);
		pwm_set_duty(Right_Behind_PWM,-L4->pwm_out);
	}
	
	return true;
}



