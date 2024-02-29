#include "zf_common_headfile.h"

/*�ⲿ����*/
extern uint8 filter_image[MT9V03X_H][MT9V03X_W];//��˹�˲����ͼ��
extern uint8 soble_image[MT9V03X_H][MT9V03X_W];//soble���ͼ��
extern uint8 using_image[MT9V03X_H][MT9V03X_W];//��͸�Ӻ��ͼ��
extern uint8 my_image[MT9V03X_H][MT9V03X_W];   //ʵ��ʹ�õ�ͼ��
extern wheel Left_Front;  //��ǰ��
extern wheel Left_Back;   //�����
extern wheel Right_Front; //��ǰ��
extern wheel Right_Back;  //�Һ���
/*�ⲿ����*/

uint8 leftline[MT9V03X_H]={0};
uint8 rightline[MT9V03X_H]={0};
uint8 midline[MT9V03X_H]={60};
uint8 threshold=100;									/*sobel��ֵ*/
bool calculat_finish=false;						/*֡���������־λ*/
int offset=0;													/*��������ƫ����*/
int speed_target=2000;								/*�ĸ�����Ŀ���ٶ�*/

/*���ĸ����Ӹ�Ŀ���ٶ�=�����ٶ�+����ƫ����*/
void motor_speedset(Wheel L1,Wheel L2,Wheel L3,Wheel L4)		
{
	L1->pwm_out=speed_target+offset;
	L2->pwm_out=speed_target+offset;
	L3->pwm_out=speed_target+offset;
	L4->pwm_out=speed_target+offset;
}

/*���㳵��ƫ����*/
void offset_calculation(void)
{
	uint8 i,j;
	offset=0;
	for(j=119;j>19;j--)
		{
				if(j<=119&&j>89) 			offset+=(60-midline[j])*0.6;   /*�������ο�����ͷ������*/
				else if(j<=89&&j>49)  offset+=(60-midline[j])*0.4;
			  else if(j<=49&&j>19)  offset+=(60-midline[j])*0.2;
		}
	calculat_finish=true;		/*���������λ*/
}

/*��������ɨ��*/
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

/*Ѳ�ߺ���*/
void Track(void) 
{
			if(mt9v03x_finish_flag)
		{
			  Gos_filter(mt9v03x_image,filter_image);
				soble(filter_image,soble_image,threshold);
				Midline_Scanf();
			  offset_calculation();
				tft180_displayimage03x((const uint8 *)soble_image, 160, 128);   // ��Ҫע�� ֱ����ʾ 188*120 �ֱ�������ʾ���µ� ��ֱ�ӽ�����Ա���
				mt9v03x_finish_flag = 0;
		}
}