#ifndef _GYRO_H_
#define _GYRO_H_
#include "zf_common_headfile.h"

typedef struct gyro_param_t //���ٶȵ���Ʈֵ
{
	float Xdata;
	float Ydata;
	float Zdata;
}gyro_param_t;

typedef struct ms601
{
	float acc_x;
	float acc_y;
	float acc_z;
	
	float gyro_x;
	float gyro_y;
	float gyro_z;
	
	float yaw;//    ƫ����
	float pitch;//  ������
	float roll;//   ������
	
	float gyro_input;//���ٶȻ�����
}ms601,*MS601;


extern MS601 ms601_data; /*��������������ȡ�ô˽ṹ������*/
bool gyroOffsetInit(void);
float Angle_regulate(float yaw, float target_angle);
bool Gyro_regulate(float gyro, float target_gyro);


void Get_atk601_data(MS601 MS601_data);
#endif