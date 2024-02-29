#include "zf_common_headfile.h"

//---------���������ȫ�ֱ����ͽṹ��--------
wheel Left_Front;  //��ǰ��
wheel Left_Back;   //�����
wheel Right_Front; //��ǰ��
wheel Right_Back;  //�Һ���
target Vel;        //�ٶ���ṹ��

coordinate point[30];//�洢��Ƭ����λ������
coordinate road_point[30];//��ʻ·���ĵ�λ����
coordinate Mercedes; //����ǰ����
coordinate Obje_point[0];
coordinate Ware_point[4];//�ֿ�����
coordinate card;      //����ʱ��Ƭ����

integral transverse; //x�������
integral longitudinal; //y�������

uint8 compress_image[MT9V03X_H][MT9V03X_W];//ѹ�����ͼ��
uint8 filter_image[MT9V03X_H][MT9V03X_W];//��˹�˲����ͼ��
uint8 soble_image[MT9V03X_H][MT9V03X_W];//soble���ͼ��
uint8 using_image[MT9V03X_H][MT9V03X_W];//��͸�Ӻ��ͼ��
uint8 my_image[MT9V03X_H][MT9V03X_W];   //ʵ��ʹ�õ�ͼ��

uint8 n = 0;//��ʻ��λ����
int16 speed = 15;//��ʻ��׼�ٶ�

uint8 find_flag = 0;              //����������־λ
bool  Key_flag = true;            //���������־λ
bool  Identi_flag = false;        //ʶ���־λ
bool  Wating_flag = false;        //�ȴ���־λ
bool  PointAdd_flag = false;      //������һ·�����־λ
CarState Move_state = CarReady;   //�����˶�״̬
ObjState Objc_state = ObjReady;   //Ŀ�����־
CorrState Corr_state = CorrReady; //����״̬��־
TranState Tran_state = TranReady; //����״̬��־
StorState Stor_state = StorReady; //ж��״̬��־

extern float pulse_10cm_x;
extern float pulse_10cm_y;

//------debug����-------
uint8 i;           
float debug[4];
char str[100];


int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
//    debug_init();                   // ���Զ˿ڳ�ʼ��
// �˴���д�û����� ���������ʼ�������
//		Vel.x = speed;
//		Vel.y = speed;
    Motor_Param_Init();
    Board_Init();	
	
    while(1)
    {
			  Get_atk601_data(ms601_data);
				Display_Ms601(ms601_data);
			
/*
//			Display_Motor( &Right_Back );
			
//			key_debug(&Right_Back );
			
//			tft180_show_float(0, 20, transverse.pulse, 4, 3);
//			tft180_show_float(0, 40, longitudinal.pulse, 4, 3);
//			Display_Imu(&imu_data);
			
//		debug[0] = Right_Back.target;
//		debug[1] = Right_Back.pulse;
//		debug[2] = Right_Back.pwm_out;
//		debug[3] = Right_Back.angle_compensate;
////		debug[4] = Right_Back.target;
////		debug[5] = Right_Back.pulse;
////		debug[6] = Right_Back.pwm_out;
////		debug[7] = Right_Back.angle_compensate;
//		vcan_sendware(&debug[0],sizeof(debug));	
			
#if 0
		if(Key_flag)
		{
			Key_Scan(0);
			if(find_flag)
			{
				LightOFF;
				for(i = 0;i < point_num;i++)
				{
					point[i].x = POINT_DATA[i*4+0]*10 + POINT_DATA[i*4+1];
					point[i].y = POINT_DATA[i*4+2]*10 + POINT_DATA[i*4+3] -1;
					
					point[i].x = point[i].x * 2 ;
					point[i].y = point[i].y * 2 ;
				}
				//aco(&point[0],&road_point[0],point_num);//��Ⱥ�㷨·���滮
				
				if(project_modo==1)
				{
					Ware_point[0].x = 7;
					Ware_point[0].y = 44;
					Ware_point[1].x = 7;
					Ware_point[1].y = 54;
					Ware_point[2].x = -3;
					Ware_point[2].y = 44;
					Ware_point[3].x = 40;
					Ware_point[3].y = 54;
				}
				else
				{
					Ware_point[0].x = 72;
					Ware_point[0].y = 26;
					Ware_point[1].x = 30;
					Ware_point[1].y = 54;
					Ware_point[2].x = -3;
					Ware_point[2].y = 30;
					Ware_point[3].x = 40;
					Ware_point[3].y = 54;
				}
				
				Obje_point[0].x = 2;
				Obje_point[0].y = 4;
				Obje_point[1].x = 62;
				Obje_point[1].y = 4;
				Obje_point[2].x = 62;
				Obje_point[2].y = 10;
				Obje_point[3].x = 0;
				Obje_point[3].y = 10;
				Obje_point[4].x = 0;
				Obje_point[4].y = 18;
				Obje_point[5].x = 60;
				Obje_point[5].y = 18;
				Obje_point[6].x = 60;
				Obje_point[6].y = 26;
				Obje_point[7].x = 0;
				Obje_point[7].y = 26;
				
				Init_point.x = 2;
				Init_point.y = 4;

				Display_Num();
				find_flag = 0;
				Art_state = ArtIdentify;
				Move_state = OutGarage;
				Key_flag = false;
			}
		}
        
		else
		{
			if(mt9v03x_finish_flag)
			{
				if(Corr_state == CorrStart || Corr_state == CorrLoading_1 || Corr_state == CorrLoading_2 || Corr_state == CorrLoading_3)
				{
					soble(mt9v03x_image,soble_image);
					ImagePerspective(soble_image,using_image);
					Find_Card(my_image,&card);
				}
			}
			
			if(Tran_state == TranStart)
			{
				RoboticArm_greb();
				Tran_state = TranGet;
			}
			else if(Tran_state == TranLoading)
			{
				RoboticArm_freed();
				Tran_state = TranFinish;
				PointAdd_flag = true;
			}
			
			if(Stor_state == StorStart)
			{
				if(project_modo==1)
				{
					RoboticArm_bodong_J(W_index);
				}
				else
				{
					RoboticArm_bodong(W_index);
				}
				
				Stor_state = StorReady;
				if(W_index >= 2)
					Move_state = EnterGarage;
				else
				{
					W_index++;
				}
			}
		}
        
#endif
*/
    }
}