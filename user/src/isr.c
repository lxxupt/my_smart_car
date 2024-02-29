#include "zf_common_headfile.h"
#include "zf_common_debug.h"
#include "isr.h"
#include "math.h"
#include "all_lstruct.h"


//-------���������������-------------
extern wheel Left_Front;  //������
extern wheel Left_Back;   //������
extern wheel Right_Front; //������
extern wheel Right_Back;  //������
extern target Vel;        //�ٶ���ṹ��
extern integral transverse; //x�������
extern integral longitudinal; //y�������
extern int16 speed;//��ʻ��׼�ٶ�

/*Ѳ�߲���*/
extern bool calculat_finish;
extern uint8 offset;
/*Ѳ�߲���*/


float pulse_10cm_x = 31.300f;//����׼ȷ��������
float pulse_10cm_y = 22.210f;

int16 ANGLE = 0;//ת������



void CSI_IRQHandler(void)
{
    CSI_DriverIRQHandler();     // ����SDK�Դ����жϺ��� ���������������������õĻص�����
    __DSB();                    // ����ͬ������
	
}

void PIT_IRQHandler(void)
{
    if(pit_flag_get(PIT_CH0))
    {
        pit_flag_clear(PIT_CH0);
				motor_speedset(&Left_Front,&Left_Back,&Right_Front,&Right_Back);
				PWM_OUT(&Left_Front,&Left_Back,&Right_Front,&Right_Back);
//				if(calculat_finish)
//				{
//				  motor_speedset(&Left_Front,&Left_Back,&Right_Front,&Right_Back);
//					PWM_OUT(&Left_Front,&Left_Back,&Right_Front,&Right_Back);
//					calculat_finish=false;
//				}
//        //��������ֵ
//					Encoder_Filter(&Left_Front,Left_FrontEncoderTimer,-1);
//					Encoder_Filter(&Left_Back,Left_BehindEncoderTimer,-1);
//					Encoder_Filter(&Right_Front,Right_FrontEncoderTimer,1);
//					Encoder_Filter(&Right_Back,Right_BehindEncoderTimer,1);
//					//���PID�������ֵ
//					Motor_Pid(&Left_Front);
//					Motor_Pid(&Left_Back);
//					Motor_Pid(&Right_Front);
//					Motor_Pid(&Right_Back);
//					//PWM���
//					PWM_OUT(&Left_Front,&Left_Back,&Right_Front,&Right_Back);
        //���������ֶ�λ
//        transverse.pulse = (Left_Front.pulse + Right_Back.pulse - Right_Front.pulse - Left_Back.pulse)*0.125f;
//				longitudinal.pulse = (Left_Front.pulse + Right_Back.pulse + Right_Front.pulse + Left_Back.pulse)*0.125f;
//		    longitudinal.pulse = (get_V(&Left_Front) + get_V(&Right_Back) + get_V(&Right_Front) + get_V(&Left_Back))*0.125f*fast_cos(imu_data.yaw); 

////      transverse.Length += get_speed(filter(transverse.pulse,1.5)) * 1.27f;
//		    transverse.Length += get_speed(transverse.pulse) * 1.27f;
//		    Mercedes.x = (int)transverse.Length/pulse_10cm_x;
		
////		  longitudinal.Length += get_speed(filter(longitudinal.pulse,1.5));
//		    longitudinal.Length += get_speed(longitudinal.pulse);
//		    Mercedes.y = (int)longitudinal.Length/pulse_10cm_y;
        
    }
    
    if(pit_flag_get(PIT_CH1))
    {
      pit_flag_clear(PIT_CH1);
//    static uint8 angle_time;                      //�ǶȻ����֣����ջ�
//		if(angle_time==0)				
//			imu_data.gyro_input = Angle_regulate(imu_data.yaw,0); //����
//		Gyro_regulate(imu_data.gyro_z,imu_data.gyro_input);//0
//		angle_time = (angle_time+1)%5;//ʱ����ۼ�
		

//		Motor_target(&Vel, &Left_Front, &Left_Back,  &Right_Front, &Right_Back);
//		Left_Front.angle_compensate = ANGLE;
//		Right_Front.angle_compensate = -ANGLE;
//		Left_Back.angle_compensate =  ANGLE;
//		Right_Back.angle_compensate =  -ANGLE;
//		Left_Front.target = Left_Front.wheel_target + Left_Front.angle_compensate;
//		Left_Back.target = Left_Back.wheel_target + Left_Back.angle_compensate;
//		Right_Front.target = Right_Front.wheel_target + Right_Front.angle_compensate;
//		Right_Back.target = Right_Back.wheel_target + Right_Back.angle_compensate;
    }
    
    if(pit_flag_get(PIT_CH2))
    {
         pit_flag_clear(PIT_CH2);
    }
    
    if(pit_flag_get(PIT_CH3))
    {
        pit_flag_clear(PIT_CH3);
//			speed_change(&Right_Back);
//			  speed_test(& Vel);
			
    }

    __DSB();
}

void LPUART1_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART1))
    {
        // �����ж�

    }
        
    LPUART_ClearStatusFlags(LPUART1, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART2_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART2))
    {
        // �����ж�
        
    }
        
    LPUART_ClearStatusFlags(LPUART2, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART3_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART3))
    {
        // �����ж�
        
    }
        
    LPUART_ClearStatusFlags(LPUART3, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART4_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART4))
    {
        // �����ж� 
        // flexio_camera_uart_handler();
        // gps_uart_callback();
		Obj_Detection_Read();
    }
        
    LPUART_ClearStatusFlags(LPUART4, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART5_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART5))
    {
        // �����ж�
        camera_uart_handler();
    }
	
        
    LPUART_ClearStatusFlags(LPUART5, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART6_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART6))
    {
        // �����ж�
        
    }
        
    LPUART_ClearStatusFlags(LPUART6, kLPUART_RxOverrunFlag);    // ������ɾ��
}

void LPUART8_IRQHandler(void)
{
    if(kLPUART_RxDataRegFullFlag & LPUART_GetStatusFlags(LPUART8))
    {
				ATK_MS601M_UART_IRQHandler();
        // �����ж�
        wireless_module_uart_handler();
        
    }
        
    LPUART_ClearStatusFlags(LPUART8, kLPUART_RxOverrunFlag);    // ������ɾ��
}


void GPIO1_Combined_0_15_IRQHandler(void)
{
    if(exti_flag_get(B0))
    {
        exti_flag_clear(B0);// ����жϱ�־λ
    }
    
}


void GPIO1_Combined_16_31_IRQHandler(void)
{
    wireless_module_spi_handler();
    if(exti_flag_get(B16))
    {
        exti_flag_clear(B16); // ����жϱ�־λ
    }

    
}

void GPIO2_Combined_0_15_IRQHandler(void)
{
    flexio_camera_vsync_handler();
    
    if(exti_flag_get(C0))
    {
        exti_flag_clear(C0);// ����жϱ�־λ
    }

}


void GPIO2_Combined_16_31_IRQHandler(void)
{
    if(exti_flag_get(C16))
    {
        exti_flag_clear(C16); // ����жϱ�־λ
    }
    
    
}




void GPIO3_Combined_0_15_IRQHandler(void)
{

    if(exti_flag_get(D4))
    {
        exti_flag_clear(D4);// ����жϱ�־λ
    }
}









/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ���ж�
void PIT_IRQHandler(void)
{
    //��������־λ
    __DSB();
}
�ǵý����жϺ������־λ
CTI0_ERROR_IRQHandler
CTI1_ERROR_IRQHandler
CORE_IRQHandler
FLEXRAM_IRQHandler
KPP_IRQHandler
TSC_DIG_IRQHandler
GPR_IRQ_IRQHandler
LCDIF_IRQHandler
CSI_IRQHandler
PXP_IRQHandler
WDOG2_IRQHandler
SNVS_HP_WRAPPER_IRQHandler
SNVS_HP_WRAPPER_TZ_IRQHandler
SNVS_LP_WRAPPER_IRQHandler
CSU_IRQHandler
DCP_IRQHandler
DCP_VMI_IRQHandler
Reserved68_IRQHandler
TRNG_IRQHandler
SJC_IRQHandler
BEE_IRQHandler
PMU_EVENT_IRQHandler
Reserved78_IRQHandler
TEMP_LOW_HIGH_IRQHandler
TEMP_PANIC_IRQHandler
USB_PHY1_IRQHandler
USB_PHY2_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
DCDC_IRQHandler
Reserved86_IRQHandler
Reserved87_IRQHandler
GPIO1_INT0_IRQHandler
GPIO1_INT1_IRQHandler
GPIO1_INT2_IRQHandler
GPIO1_INT3_IRQHandler
GPIO1_INT4_IRQHandler
GPIO1_INT5_IRQHandler
GPIO1_INT6_IRQHandler
GPIO1_INT7_IRQHandler
GPIO1_Combined_0_15_IRQHandler
GPIO1_Combined_16_31_IRQHandler
GPIO2_Combined_0_15_IRQHandler
GPIO2_Combined_16_31_IRQHandler
GPIO3_Combined_0_15_IRQHandler
GPIO3_Combined_16_31_IRQHandler
GPIO4_Combined_0_15_IRQHandler
GPIO4_Combined_16_31_IRQHandler
GPIO5_Combined_0_15_IRQHandler
GPIO5_Combined_16_31_IRQHandler
WDOG1_IRQHandler
RTWDOG_IRQHandler
EWM_IRQHandler
CCM_1_IRQHandler
CCM_2_IRQHandler
GPC_IRQHandler
SRC_IRQHandler
Reserved115_IRQHandler
GPT1_IRQHandler
GPT2_IRQHandler
PWM1_0_IRQHandler
PWM1_1_IRQHandler
PWM1_2_IRQHandler
PWM1_3_IRQHandler
PWM1_FAULT_IRQHandler
SEMC_IRQHandler
USB_OTG2_IRQHandler
USB_OTG1_IRQHandler
XBAR1_IRQ_0_1_IRQHandler
XBAR1_IRQ_2_3_IRQHandler
ADC_ETC_IRQ0_IRQHandler
ADC_ETC_IRQ1_IRQHandler
ADC_ETC_IRQ2_IRQHandler
ADC_ETC_ERROR_IRQ_IRQHandler
PIT_IRQHandler
ACMP1_IRQHandler
ACMP2_IRQHandler
ACMP3_IRQHandler
ACMP4_IRQHandler
Reserved143_IRQHandler
Reserved144_IRQHandler
ENC1_IRQHandler
ENC2_IRQHandler
ENC3_IRQHandler
ENC4_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
TMR4_IRQHandler
PWM2_0_IRQHandler
PWM2_1_IRQHandler
PWM2_2_IRQHandler
PWM2_3_IRQHandler
PWM2_FAULT_IRQHandler
PWM3_0_IRQHandler
PWM3_1_IRQHandler
PWM3_2_IRQHandler
PWM3_3_IRQHandler
PWM3_FAULT_IRQHandler
PWM4_0_IRQHandler
PWM4_1_IRQHandler
PWM4_2_IRQHandler
PWM4_3_IRQHandler
PWM4_FAULT_IRQHandler
Reserved171_IRQHandler
GPIO6_7_8_9_IRQHandler*/



