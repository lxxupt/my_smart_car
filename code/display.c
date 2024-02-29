#include "zf_common_headfile.h"
#include "display.h"
extern coordinate road_point[30];

void Display_Menu(void)
{
	
}

void Display_Num(void)
{
	uint8 i;
	for(i=0;i<point_num;i++)
	{
		if(i<6)
		{
			tft180_show_uint(0,i*16,road_point[i].x,2);
			tft180_show_uint(20,i*16,road_point[i].y,2);
		}
		else if(i>=6 && i<12)
		{
			tft180_show_uint(40,(i-6)*16,road_point[i].x,2);
			tft180_show_uint(60,(i-6)*16,road_point[i].y,2);
		}
		else if(i>=12)
		{
			tft180_show_uint(80,(i-12)*16,road_point[i].x,2);
			tft180_show_uint(100,(i-12)*16,road_point[i].y,2);
		}
		
	}
}

void Display_Motor(Wheel L)
{
	tft180_show_string(0, 0, "I");
    tft180_show_float(40, 0, L->Ki, 2, 3);

    tft180_show_string(0, 20, "P");
    tft180_show_float(40, 20, L->Kp, 2, 3);

    tft180_show_string(0, 40, "D");
    tft180_show_float(40, 40, L->Kd, 2, 3);

    tft180_show_string(0, 60, "pulse");
    tft180_show_int(40, 60, L->pulse,5);

    tft180_show_string(0, 90, "PWM");
    tft180_show_int(40, 90, L->pwm_out,5);
}

void Display_Ms601(MS601 MS601_data)
{
if(!Boma4)
{
	tft180_show_string(0, 0, "g_x");
	tft180_show_float(32, 0, MS601_data->gyro_x, 2, 3);
	
	tft180_show_string(0, 20, "g_y");
	tft180_show_float(32, 20, MS601_data->gyro_y, 2, 3);

	tft180_show_string(0, 40, "g_z");
	tft180_show_float(32, 40, MS601_data->gyro_z, 2, 3);
}else{
	tft180_show_string(0, 0, "a_x");
	tft180_show_float(32, 0, MS601_data->acc_x, 2, 3);
	
	tft180_show_string(0, 20, "a_y");
	tft180_show_float(32, 20, MS601_data->acc_y, 2, 3);

	tft180_show_string(0, 40, "a_z");
	tft180_show_float(32, 40, MS601_data->acc_z, 2, 3);
}
	tft180_show_string(0, 60, "yaw");
	tft180_show_float(40, 60, MS601_data->yaw, 2, 3);
}


