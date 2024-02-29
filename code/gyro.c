#include "zf_common_headfile.h"
#include "gyro.h"
#include "math.h"
#include "atk_ms601m.h"

atk_ms601m_attitude_data_t attitude_dat;           /* ��̬������ */
atk_ms601m_gyro_data_t gyro_dat;                   /* ���������� */
atk_ms601m_accelerometer_data_t accelerometer_dat; /* ���ٶȼ����� */
gyro_param_t GyroOffset;  
MS601 ms601_data;																	 /*��������������ȡ�ô˽ṹ������*/

/*�˺����ڲ��д���ͨѶ��ʱ�ȴ���������ŵ���ʱ��*/
void Get_atk601_data(MS601  MS601_data)
{
    /* ��ȡATK-MS901���ݵ�MS601_data�ṹ�� */
    atk_ms601m_get_attitude(&attitude_dat, 100);                            /* ��ȡ��̬������ */
	  atk_ms601m_get_gyro_accelerometer(&gyro_dat, &accelerometer_dat, 100);  /* ��ȡ�����ǡ����ٶȼ����� */
		MS601_data->acc_x=accelerometer_dat.x;
		MS601_data->acc_y=accelerometer_dat.y;
		MS601_data->acc_z=accelerometer_dat.z;
		MS601_data->gyro_x=gyro_dat.x-GyroOffset.Xdata;
		MS601_data->gyro_y=gyro_dat.y-GyroOffset.Ydata;
		MS601_data->gyro_z=gyro_dat.z-GyroOffset.Zdata;
		MS601_data->pitch=attitude_dat.pitch;
		MS601_data->roll=attitude_dat.roll;
		MS601_data->yaw=attitude_dat.yaw;
}
/*
* @function: ��������Ʈ��ʼ��
* @param: None
* @return: bool
* @others: ���� �����Ƕ�ȡ������ - ��Ʈֵ������ȥ�����ƫ������
*/
  
bool gyroOffsetInit(void)     
{
    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;
    for (uint8 i = 0; i < 100; i++) 
	{
        atk_ms601m_get_gyro_accelerometer(&gyro_dat, &accelerometer_dat, 100);  /* ��ȡ�����ǡ����ٶȼ����� */
        GyroOffset.Xdata += gyro_dat.x;
        GyroOffset.Ydata += gyro_dat.y;
        GyroOffset.Zdata += gyro_dat.z;
        system_delay_ms(5);
    }

    GyroOffset.Xdata /= 100;
    GyroOffset.Ydata /= 100;
    GyroOffset.Zdata /= 100;
	
	return true;
}


/*
* @function: ������̬�ǶȻ�
* @param: 
* @return float����
* @others:
*/

float attitude_kp = 0.1780; //0.158; 
float attitude_ki = 0.001; //0.017;  0.008
float attitude_kd = 0.05; //-0.089;
float Angle_regulate(float yaw, float target_angle)
{
	static float Err_attitude, Err0_attitude;
	static float attitude_err_i; //����ۻ�
	float angle_out;
	
	Err0_attitude = Err_attitude;
	Err_attitude =  target_angle - yaw;
	attitude_err_i += Err_attitude;
	if(attitude_err_i>3) attitude_err_i = 3;
	else if(attitude_err_i<-3) attitude_err_i = -3;
	angle_out = attitude_kp*(Err_attitude) + attitude_ki*(attitude_err_i) +attitude_kd*(Err_attitude-Err0_attitude);
	return angle_out;
}

/*
* @function: ������̬���ٶȻ�
* @param: 
* @return bool����
* @others:
*/
extern wheel Left_Front,Right_Front,Left_Back,Right_Back;
float gyro_kp = 125.8f*0.35;  //75.8f*0.35;   95.8f*0.35;   125.8f*0.35;
float gyro_ki = 0.0f*0.35;   //0.8f*0.35;    0.0f*0.35;
float gyro_kd = 13.3f*0.35; //143.75f*0.35; 123.5f*0.35;    13.3f*0.35;
int16 temp;
bool Gyro_regulate(float gyro, float target_gyro)
{
	static float Err_gyro, Err0_gyro;
	static float Err_i; //����ۻ�
	static int16 out;
	
	Err0_gyro = Err_gyro;
	Err_gyro =  gyro - target_gyro;
	
	Err_i += Err_gyro;
	
	out = gyro_kp*Err_gyro + gyro_ki*Err_i +gyro_kd*(Err_gyro-Err0_gyro);
	temp = out;
	
	Left_Front.angle_compensate = out;
	Right_Front.angle_compensate = -out;
	
	Left_Back.angle_compensate =  out;
	Right_Back.angle_compensate =  -out;
	return true;
}
