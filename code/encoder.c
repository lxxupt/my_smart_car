#include "zf_common_headfile.h"
#include "encoder.h"

/*
* @fuction���������˲�
* @param: void
*/
void Encoder_Init(void)
{
	encoder_dir_init(Left_FrontEncoderTimer, Left_FrontEncoderDirCh1, Left_FrontEncoderPulseCh2);
	encoder_dir_init(Left_BehindEncoderTimer, Left_BehindEncoderDirCh1, Left_BehindEncoderPulseCh2);
	encoder_dir_init(Right_FrontEncoderTimer, Right_FrontEncoderDirCh1, Right_FrontEncoderPulseCh2);
	encoder_dir_init(Right_BehindEncoderTimer, Right_BehindEncoderDirCh1, Right_BehindEncoderPulseCh2);
}

/*
* @fuction���������˲�
* @param:
* @return: None
*/
void Encoder_Filter(Wheel L,encoder_index_enum encoder_n,int8 flag)
{
	L->last_RealSpeed = L->pulse;
	
	L->pulse = flag*encoder_get_count(encoder_n);
	encoder_clear_count(encoder_n);
	
	L->pulse = (int16)(0.8*L->pulse+0.2*L->last_RealSpeed);

	L->Ensoc[L->index++] = L->pulse;
	L->index %= 5;

	L->Encoder_Speed_Max = L->Ensoc[0];
	L->Encoder_Speed_Min = L->Ensoc[0];

	L->pulse=0;

	for(uint8 i = 0; i < 5; i++)
	{
		L->pulse += L->Ensoc[i];
		if(L->Encoder_Speed_Min < L->Ensoc[i])
			L->Encoder_Speed_Min = L->Ensoc[i];
		if(L->Encoder_Speed_Max > L->Ensoc[i])
			L->Encoder_Speed_Max = L->Ensoc[i];
	}
	L->pulse = (L->pulse - L->Encoder_Speed_Max - L->Encoder_Speed_Min) / 3;
}


/*
* @fuction��ͨ����������ȡ����ת��
* @param: L ���Ƴ��ֵĽṹ��ָ��
* @return: ����ת��
* @time:  2023/03/02
* @author: WXQ
* @other: ת��=������ֵ/������������/ʱ��
*/
float get_speed(float data)
{
	float S;
	S = data*500/1024 * 3/7 * 0.187;//
	
	return S;
}

/*
* @fuction����ȡ������ƽ��ƽ�Ƶı�����ֵ
* @param: L ���Ƴ��ֵĽṹ��ָ��
* @return: ������ֵ
* @time:  2023/03/02
* @author: WXQ
* @other: ת��=����ֵ * �ƶ�Ŀ��ֵ/��Ŀ��ֵ
*/
float get_V(Wheel L)
{
	float V;
	V = L->pulse*L->wheel_target/L->target;
	return V;
}
/*
* @fuction���޷��˲�
* @param:data ��Ҫ�˲�������
* @time:  2023/03/02
* @author: WXQ
*/
float filter(float data,float a)
{
	if(data>a || data<-a)
		return data;
	else 
		return 0;
}
