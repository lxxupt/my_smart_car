#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "zf_common_headfile.h"

#define Left_FrontEncoderTimer         QTIMER1_ENCODER2                   //ʹ��TIM1��Ϊ��ǰ�ֱ�����ʱ��                                  
#define Left_FrontEncoderDirCh1        QTIMER1_ENCODER2_CH1_C2            //ʹ��C2��Ϊ��ǰ�ֱ�����������������
#define Left_FrontEncoderPulseCh2      QTIMER1_ENCODER2_CH2_C24           //ʹ��C24��Ϊ��ǰ�ֱ�����������������

#define Left_BehindEncoderTimer        QTIMER1_ENCODER1                   //ʹ��TIM1��Ϊ����ֱ�����ʱ��                              
#define Left_BehindEncoderDirCh1       QTIMER1_ENCODER1_CH1_C0            //ʹ��C0��Ϊ����ֱ�����������������
#define Left_BehindEncoderPulseCh2     QTIMER1_ENCODER1_CH2_C1            //ʹ��C1��Ϊ����ֱ�����������������

#define Right_FrontEncoderTimer        QTIMER2_ENCODER1                   //ʹ��TIM2��Ϊ��ǰ�ֱ�����ʱ��
#define Right_FrontEncoderDirCh1       QTIMER2_ENCODER1_CH1_C3            //ʹ��C3��Ϊ��ǰ�ֱ�����������������
#define Right_FrontEncoderPulseCh2     QTIMER2_ENCODER1_CH2_C25           //ʹ��C25��Ϊ��ǰ�ֱ�����������������

#define Right_BehindEncoderTimer       QTIMER3_ENCODER2                   //ʹ��TIM3��Ϊ�Һ��ֱ�����ʱ��                                          
#define Right_BehindEncoderDirCh1      QTIMER3_ENCODER2_CH1_B18           //ʹ��B18��Ϊ�Һ��ֱ�����������������
#define Right_BehindEncoderPulseCh2    QTIMER3_ENCODER2_CH2_B19           //ʹ��B19��Ϊ�Һ��ֱ�����������������

typedef struct Integral
{
	float pulse;  //���Ǳ��������� Ҳ�� ���ֵĵ��� �� ���ٶ�
	float Length; 
	int32 cor_length;
	float speed; 
	
}integral, *Integral;

void Encoder_Init(void);
void Encoder_Filter(Wheel L,encoder_index_enum encoder_n,int8 flag);

float get_speed(float data);
float get_V(Wheel L);
float filter(float data,float a);
#endif