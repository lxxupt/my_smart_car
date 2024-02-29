#ifndef _GYRO_H_
#define _GYRO_H_
#include "zf_common_headfile.h"

typedef struct gyro_param_t //角速度的零飘值
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
	
	float yaw;//    偏航角
	float pitch;//  俯仰角
	float roll;//   翻滚角
	
	float gyro_input;//角速度环输入
}ms601,*MS601;


extern MS601 ms601_data; /*最终陀螺仪数据取用此结构体数据*/
bool gyroOffsetInit(void);
float Angle_regulate(float yaw, float target_angle);
bool Gyro_regulate(float gyro, float target_gyro);


void Get_atk601_data(MS601 MS601_data);
#endif