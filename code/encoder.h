#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "zf_common_headfile.h"

#define Left_FrontEncoderTimer         QTIMER1_ENCODER2                   //使用TIM1作为左前轮编码器时钟                                  
#define Left_FrontEncoderDirCh1        QTIMER1_ENCODER2_CH1_C2            //使用C2作为左前轮编码器方向输入引脚
#define Left_FrontEncoderPulseCh2      QTIMER1_ENCODER2_CH2_C24           //使用C24作为左前轮编码器脉冲输入引脚

#define Left_BehindEncoderTimer        QTIMER1_ENCODER1                   //使用TIM1作为左后轮编码器时钟                              
#define Left_BehindEncoderDirCh1       QTIMER1_ENCODER1_CH1_C0            //使用C0作为左后轮编码器方向输入引脚
#define Left_BehindEncoderPulseCh2     QTIMER1_ENCODER1_CH2_C1            //使用C1作为左后轮编码器脉冲输入引脚

#define Right_FrontEncoderTimer        QTIMER2_ENCODER1                   //使用TIM2作为右前轮编码器时钟
#define Right_FrontEncoderDirCh1       QTIMER2_ENCODER1_CH1_C3            //使用C3作为右前轮编码器方向输入引脚
#define Right_FrontEncoderPulseCh2     QTIMER2_ENCODER1_CH2_C25           //使用C25作为右前轮编码器脉冲输入引脚

#define Right_BehindEncoderTimer       QTIMER3_ENCODER2                   //使用TIM3作为右后轮编码器时钟                                          
#define Right_BehindEncoderDirCh1      QTIMER3_ENCODER2_CH1_B18           //使用B18作为右后轮编码器方向输入引脚
#define Right_BehindEncoderPulseCh2    QTIMER3_ENCODER2_CH2_B19           //使用B19作为右后轮编码器脉冲输入引脚

typedef struct Integral
{
	float pulse;  //既是编码器数据 也是 积分的导数 即 向速度
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