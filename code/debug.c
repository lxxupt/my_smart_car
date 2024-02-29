#include "zf_common_headfile.h"
#include "debug.h"

/*
 *  @brief      虚拟示波器显示函数
 *  @param      wareaddr    波形数组起始地址
 *  @param      waresize    波形数组占用空间的大小
 */
void vcan_sendware(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart_write_buffer(VCAN_PORT, cmdf, sizeof(cmdf));    //先发送前命令
    uart_write_buffer(VCAN_PORT, (uint8_t *)wareaddr, waresize);    //发送数据
    uart_write_buffer(VCAN_PORT, cmdr, sizeof(cmdr));    //发送后命令
}

//--------------抗干扰灰度图传-------------------//
//当丢失数据的情况下，该协议能重新定位行来实现一定程度抗干扰能力
//*image图像地址 width图像宽 height图像高
//例：sendimg(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);
//数据包大小:6+（width+3） * height(图传一帧的字节数)
void sendimg_A( uint8* image, uint8 width, uint8 height)
{

    sw_write_byte(0x21); sw_write_byte(0x7A);
    sw_write_byte(width);sw_write_byte(height);
    sw_write_byte((width+height)/2);sw_write_byte(0x7A);

    uint8 line=0,col=0;
    for(line=0;line<width;line++)
        {
        sw_write_byte(21);
        sw_write_byte(line);
        sw_write_byte(133);
           for(col=0;col<height;col++)
           {
               sw_write_byte(*(image+line*height+col));

           }

        }
}

//带有校验的二值图传
//chk值越大 抗干扰越强 值0-55
//请根据实际使用情况进行调整
void sendimg_binary_CHK(uint8* image, uint8 width, uint8 height,uint8 otu,uint8 chk)
{
    chk=chk>0?chk:0;
    chk=chk<56?chk:55;
    uint8 dat[7]={0x7A,0x21,width,height,0x7A,0x21,200+chk};
      sw_write_buffer(dat,7);
      int databool=255;uint8 lon=0;int data=255;
      uint8 line=0,col=0;
      int imglon=0;
      int imgdatlo=width*height/chk;
      uint8 CHK=0;
      for(line=0;line<width;line++)
          {
             for(col=0;col<height;col++)
             {imglon++;

                if(*(image+line*height+col)>otu)data=255;
                else data=0;
                if(data==databool)
                {lon++;}
                else{sw_write_byte(lon);lon=1;}

                if(imglon==imgdatlo)
                {CHK++;sw_write_byte(lon);data=255; databool=255;sw_write_byte(200+CHK);lon=0;imglon=0;}
                if(lon==190){sw_write_byte(lon);sw_write_byte(0);lon=0;}
               databool=data;
             }
          }
}


/*
* @fuction: 车体发送信息
* @param: Big 大类
* @param: Small 小类
* @time: 2023/04/09 
* @others: None
*/
void send_information(uint8 big,uint8 sma)
{
	uart_write_byte(Blue_tooth, big+48); 
	uart_write_byte(Blue_tooth, ' ');
	
	uart_write_byte(Blue_tooth, sma+48); 
	uart_write_byte(Blue_tooth, ' ');
	
	uart_write_byte(Blue_tooth, '\n');
}

/*
* @fuction: 按键调试电机PID参数
* @param: L 控制车轮的结构体指针
*/
float hina = 0.05;
int8 hina_temp = 5;
void key_debug(Wheel L)
{
	if(!Key3)
		{
			system_delay_ms(10);
			if(!Key3)
			{
				switch (hina_temp)
				{
					case 5: hina_temp = 3;hina = 0.2;break;
					case 3: hina_temp = 1;hina = 0.01;break;
					case 1: hina_temp = 5;hina = 0.05;break;
				}
				while(!Key3);
			}
		}
	if(Boma1 && Boma2)
	{
		if(!Key1)
		{
			system_delay_ms(10);
			if(!Key1)
			{
				L->Kp+=hina;
				while(!Key1);
			}
		}
		
		if(!Key2)
		{
			system_delay_ms(10);
			if(!Key2)
			{
				L->Kp-=hina;
				while(!Key2);
			}
		}
	}
	
	if(Boma1 && !Boma2)
	{
		if(!Key1)
		{
			system_delay_ms(10);
			if(!Key1)
			{
				L->Ki+=hina;
				while(!Key1);
			}
		}
		
		if(!Key2)
		{
			system_delay_ms(10);
			if(!Key2)
			{
				L->Ki-=hina;
				while(!Key2);
			}
		}
	}
	
	if(!Boma1 && Boma2)
	{
		if(!Key1)
		{
			system_delay_ms(10);
			if(!Key1)
			{
				L->Kd+=hina;
				while(!Key1);
			}
		}
		
		if(!Key2)
		{
			system_delay_ms(10);
			if(!Key2)
			{
				L->Kd-=hina;
				while(!Key2);
			}
		}
	}
}


/*
* @fuction: 定时器中改变电机转速目标值
* @param: L 控制车轮的结构体指针
* @other: 调参时在定时器中调用
*/
void speed_change(Wheel L)
{
	static uint16 count = 0;
	count++;
	if(count == 40)
		L->target = 30;
	if(count == 80)
		L->target = 60;
	if(count == 120)
		L->target = 0;
	if(count == 160)
		L->target = -30;
	if(count == 200)
		L->target = -60;
	if(count == 240)
	{
		count = 0;
		L->target = 0;
	}
	
}
extern int16 speed;
extern int16 ANGLE;

void speed_test(Target V)
{
	static int16 count = 0;
	count++;
		if(count == 40)
		{
		V->x = speed;
		V->y = speed;ANGLE = 0;
		}
	if(count == 200)
		{
		V->x = 0;
		V->y = 0;ANGLE = 30;
		}
	if(count == 209)
		{
		V->x = -speed;
		V->y = -speed;ANGLE = 0;
		}	
	if(count == 369)
		{
		V->x = 0;
		V->y = 0;ANGLE = 30;
		}
		if(count == 378)
		{
		V->x = speed;
		V->y = speed;ANGLE = 0;
		}
	if(count == 538)
		{
		V->x = 0;
		V->y = 0;ANGLE = 30;
		}
	if(count == 547)
		{
		V->x = -speed;
		V->y = -speed;ANGLE = 0;
		}	
	if(count == 707)
		{
		V->x = 0;
		V->y = 0;ANGLE = 30;
		}
		if(count == 716)
		{
		V->x = speed;
		V->y = speed;ANGLE = 0;
		}	
	if(count == 876)
		{
		V->x = 0;
		V->y = 0;ANGLE = 30;
		}
	if(count == 885)
		{
					count = -500;
		V->x = 0;
		V->y = 0;ANGLE = 0;
		}


//	if(count == 40)
//		{
//		V->x = 0;
//		V->y = 0;
//			ANGLE = 30;
//		}
//	if(count == 135)
//		{
//		V->x = -0;
//		V->y = 0;
//			ANGLE = 0;
//		}
//	if(count == 200)
//		{
//					count = 0;
//		V->x = 0;
//		V->y = 0;
//		}
}

/*
* @fuction: 定时器中改变角度环目标值
* @param: 
* @other: 调参时在定时器中调用
*/
float target_alpah;
void alpha_change()
{
	static uint16 count = 0;
	count++;
	if(count == 40)
		target_alpah = 60.0;
	if(count == 80)
	{
		target_alpah = 0.0;
	}
	if(count == 120)
	{
		target_alpah = -60.0;
	}
	if(count == 160)
	{
		target_alpah = 0.0;
		count = 0;
	}
}