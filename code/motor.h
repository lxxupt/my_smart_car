#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "zf_common_headfile.h"

#define	Left_Front_direction	              D1
#define	Left_Front_PWM	                		PWM1_MODULE3_CHA_D0
#define Right_Front_direction					      D13
#define	Right_Front_PWM  	              	  PWM1_MODULE0_CHA_D12

#define	Left_Behind_direction	          		D2
#define	Left_Behind_PWM   						      PWM2_MODULE3_CHB_D3
#define Right_Behind_direction				    	D14
#define	Right_Behind_PWM    				       	PWM1_MODULE1_CHB_D15


typedef struct wheel
{
	int16 pulse;             //������
	int16 pwm_out;           //pwm���
	int16 target;            //����Ŀ���ٶ�
	int16 angle_compensate;  //�����ٶȡ������˽��ٶȻ�����ó�
	int16 wheel_target;      //Ԥ���ٶȡ����ƶ��������ó�
	int16 error;
	int16 last_err;
	int16 Last_Err;
	float Kp;
	float Ki;
	float Kd;
	uint16 adc;
	
	int16 last_RealSpeed;
	int16 Ensoc[5];
	uint8 index;
	int16 Encoder_Speed_Max;
	int16 Encoder_Speed_Min;
	
	int32 length;
}wheel,*Wheel;

void Motor_Init(void);
void Motor_Param_Init(void);
bool Motor_Pid(Wheel L);
bool PWM_OUT(Wheel L1,Wheel L2,Wheel L3,Wheel L4);



#endif 