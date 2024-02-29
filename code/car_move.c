#include "zf_common_headfile.h"
#include "car_move.h"
#include "math.h"
#include "all_lstruct.h"

/*
* @fuction: 将速度轴上的目标速度赋值给四个电机
* @param: L1 左前轮
* @param: L2 左后轮
* @param: L3 右前轮
* @param: L4 右后轮
* @others: 速度轴的y即 麦轮右前和左后
		   速度轴的x即 麦轮左前和右后
*/
bool Motor_target(Target V,Wheel L1, Wheel L2, Wheel L3, Wheel L4)
{
	L1->wheel_target = V->x;
	L4->wheel_target = V->x;
	
	L2->wheel_target = V->y;
	L3->wheel_target = V->y;
	return true;
}

/*
* @function: 将目标点坐标转化位速度轴上x、y的分量
* @param: x、y目标点的坐标
* @param: Mer 指向车体当前坐标的指针
* @param: V 指向速度轴结构体的指针
* @param: target 车的基础目标速度
* @others: 速度轴向和实际坐标的轴向相差45°，因此需要进行坐标轴系变换公式 
*           x1 = x*cosθ + y*sinθ    y1 = y*cosθ - x*sinθ 解算出的 x1 和 y1 其实就是速度轴上的x和y
*/
bool Motion_analysis(int8 x ,int8 y, Coordinate Mer, Target V, int16 target)
{
	float Vx; 
	float Vy;
	int8 p_x;
	int8 p_y;
	
	p_x = x - Mer->x;
	p_y = y - Mer->y;
	
	Vx = p_x*fast_cos(45-ms601_data->yaw) + p_y*fast_sin(45-ms601_data->yaw);
	Vy = p_y*fast_cos(45-ms601_data->yaw) - p_x*fast_sin(45-ms601_data->yaw); 

	V->x = (target * (Vx*1.0)/sqrt(p_x * p_x + p_y * p_y))+0.55;
	V->y = (target * (Vy*1.0)/sqrt(p_x * p_x + p_y * p_y))+1.55;
	
	return true;
}

bool Motion_analysis_text(int8 p_x ,int8 p_y, Target V, int16 target)
{
	float Vx; 
	float Vy;
	
	Vx = p_x*fast_cos(45+ms601_data->yaw) + p_y*fast_sin(45+ms601_data->yaw);
	Vy = p_y*fast_cos(45+ms601_data->yaw) - p_x*fast_sin(45+ms601_data->yaw); 

	V->x = (target * (Vx*1.0)/sqrt(p_x * p_x + p_y * p_y))+0.55;
	V->y = (target * (Vy*1.0)/sqrt(p_x * p_x + p_y * p_y))+0.55;
	
	return true;
}
bool New_Motion_analysis_text(int8 p_x ,int8 p_y, Target V, int16 target)
{
	float Vx; 
	float Vy;
	
	Vx = p_x*fast_cos(45) + p_y*fast_sin(45);
	Vy = p_y*fast_cos(45) - p_x*fast_sin(45); 

	V->x = (target * (Vx*1.0)/sqrt(p_x * p_x + p_y * p_y))+0.55;
	V->y = (target * (Vy*1.0)/sqrt(p_x * p_x + p_y * p_y))+0.55;
	
	return true;
}
/*
* @fuction：矫正PID
* @param: recv_x 卡片中心x坐标
* @param: recv_y 卡片中心y坐标
* @param: V 速度结构体指针
* @return: void
* @time:  2023/03/13
* @author: WXQ
*/
static float er_kp = 0.4f;
static float er_kd = 0.68f;
void Correction_PID(uint8 recv_x,uint8 recv_y,uint8 COR_X,uint8 COR_Y,Target V ,float a)
{
	int16 x_out;
	int16 y_out;
	
	static int16 x_er[2];
	static int16 y_er[2];
	
	x_er[1] = x_er[0];
	x_er[0] = recv_x - COR_X;
	
	x_out = er_kp * x_er[0] + er_kd * (x_er[0] - x_er[1]);
	if(x_out>30) x_out = 25;
	else if(x_out<-30) x_out = -25;
	
	y_er[1] = y_er[0];
	y_er[0] = COR_Y - recv_y;
	
	y_out = er_kp * y_er[0] + er_kd * (y_er[0] - y_er[1]);
	if(y_out>30) y_out = 25;
	else if(y_out<-30) y_out = -25;
	
	V->x = (y_out + x_out) * a;
	V->y = (y_out - x_out) * a;
}




/*
* @fuction：目标检测控制
* @param: obj_x 卡片中心x坐标
* @param: obj_y 卡片中心y坐标
* @param: V 速度结构体指针
* @return: void
* @time:  2023/07/05
* @author: WXQ
*/
static float Obj_er_kp = 0.4f;
static float Obj_er_kd = 0.88f;
void Obj_Detection_Control(uint16 obj_x,uint8 obj_y,uint8 COR_X,uint8 COR_Y,Target V ,float a)
{
	int16 X_out;
	int16 Y_out;
	
	static int16 x_er[2];
	static int16 y_er[2];
	
	x_er[1] = x_er[0];
	x_er[0] = obj_x - COR_X;
	
	X_out = Obj_er_kp * x_er[0] + Obj_er_kd * (x_er[0] - x_er[1]);
	if(X_out>30) X_out = 25;
	else if(X_out<-30) X_out = -25;
	
	y_er[1] = y_er[0];
	y_er[0] = COR_Y - obj_y;
	
	Y_out = Obj_er_kp * y_er[0] + Obj_er_kd * (y_er[0] - y_er[1]);
	if(Y_out>30) Y_out = 25;
	else if(Y_out<-30) Y_out = -25;
	
	
	V->x = (Y_out + X_out) * a;
	V->y = (Y_out - X_out) * a;
}