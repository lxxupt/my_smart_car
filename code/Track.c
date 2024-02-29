#include "zf_common_headfile.h"

/*外部声明*/
extern uint8 filter_image[MT9V03X_H][MT9V03X_W];//高斯滤波后的图像
extern uint8 soble_image[MT9V03X_H][MT9V03X_W];//soble后的图像
extern uint8 using_image[MT9V03X_H][MT9V03X_W];//逆透视后的图像
extern uint8 my_image[MT9V03X_H][MT9V03X_W];   //实际使用的图像
extern wheel Left_Front;  //左前轮
extern wheel Left_Back;   //左后轮
extern wheel Right_Front; //右前轮
extern wheel Right_Back;  //右后轮
/*外部声明*/

uint8 leftline[MT9V03X_H]={0};
uint8 rightline[MT9V03X_H]={0};
uint8 midline[MT9V03X_H]={60};
uint8 threshold=100;									/*sobel阈值*/
bool calculat_finish=false;						/*帧处理结束标志位*/
int offset=0;													/*车体中线偏移量*/
int speed_target=2000;								/*四个轮子目标速度*/

/*给四个轮子赋目标速度=基础速度+车体偏移量*/
void motor_speedset(Wheel L1,Wheel L2,Wheel L3,Wheel L4)		
{
	L1->pwm_out=speed_target+offset;
	L2->pwm_out=speed_target+offset;
	L3->pwm_out=speed_target+offset;
	L4->pwm_out=speed_target+offset;
}

/*计算车体偏移量*/
void offset_calculation(void)
{
	uint8 i,j;
	offset=0;
	for(j=119;j>19;j--)
		{
				if(j<=119&&j>89) 			offset+=(60-midline[j])*0.6;   /*更加信任靠近车头的中线*/
				else if(j<=89&&j>49)  offset+=(60-midline[j])*0.4;
			  else if(j<=49&&j>19)  offset+=(60-midline[j])*0.2;
		}
	calculat_finish=true;		/*计算完成置位*/
}

/*初步中线扫描*/
void Midline_Scanf(void)	
{
    int8 i,j;
    for(i=119;i>1;i--)
    {
        leftline[i]=0;
        rightline[i]=MT9V03X_H-1;

        for(j=midline[i];j>1;j--)
        {
            if((soble_image[i][j]!=soble_image[i][j-1]))
            {
                leftline[i]=j;
                break;
            }
        }
        for(j=midline[i];j<119;j++)
        {
            if((soble_image[i][j]!=soble_image[i][j+1]))
            {
                rightline[i]=j;
                break;
            }
        }
        if(leftline[i]<0)
           leftline[i]=0;
        if(rightline[i]>119)
           rightline[i]=119;

         midline[i]=(leftline[i]+rightline[i])/2;
         midline[i]=midline[i]>119?119:(midline[i]<0?0:midline[i]);
         midline[i-1]=midline[i];
    }
}

/*巡线函数*/
void Track(void) 
{
			if(mt9v03x_finish_flag)
		{
			  Gos_filter(mt9v03x_image,filter_image);
				soble(filter_image,soble_image,threshold);
				Midline_Scanf();
			  offset_calculation();
				tft180_displayimage03x((const uint8 *)soble_image, 160, 128);   // 需要注意 直接显示 188*120 分辨率是显示不下的 会直接进入断言报错
				mt9v03x_finish_flag = 0;
		}
}