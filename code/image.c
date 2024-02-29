#include "zf_common_headfile.h"
#include "image.h"

bool find_point = false;

uint16 my_abs(int16 x)
{
    if(x<0)
    {
        return -1 * x;
    }
    else
    {
        return x;
    }
}


/*
* @brief:图像压缩
* @param: uint8 (*image)[MT9V03X_W] 原图像，传入时，直接调用数组名即可
* @param: uint8 (*news)[MT9V03X_W] 滤波后的图像，传入时，直接调用数组名即可
*/
void Compress(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W])
{
    int16 i,j;
    for(i=0;i<120;i+=2)
    {
        for(j=0;j<188;j+=2)
        {
            news[i/2][j/2]=image[i][j];
        }
    }
}

/*
* @brief:高斯滤波
* @param: uint8 (*image)[MT9V03X_W] 原图像，传入时，直接调用数组名即可
* @param: uint8 (*news)[MT9V03X_W] 滤波后的图像，传入时，直接调用数组名即可
*/
void Gos_filter(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W])
{
	uint8 i,j;
	for(i = 1;i < MT9V03X_H-2;i++)
	{
		for(j = 1;j < MT9V03X_W-2;j++)
		{
			*(news[i]+j) = ((int16)*(image[i-1]+j-1) * 1 + (int16)*(image[i-1]+j) * 2 + (int16)*(image[i-1]+j+1) * 1
						   +(int16)*(image[i]+j-1) * 2   + (int16)*(image[i]+j) * 5   + (int16)*(image[i]+j+1) * 2
						   +(int16)*(image[i+1]+j-1) * 1 + (int16)*(image[i+1]+j) * 2 + (int16)*(image[i+1]+j+1) * 1)/17;
		}
	}
}

/*
* @brief: soble边缘扫线
* @param: uint8 (*image)[MT9V03X_W] 原图像，传入时，直接调用数组名即可
* @param: uint8 (*news)[MT9V03X_W] soble处理后的图像，传入时，直接调用数组名即可
* @note:  边缘检测将边缘像素变白
*/
void soble(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W] , uint8 threshold)
{
    uint8 i,j;
    int16 soble_x = 0;
    int16 soble_y = 0;
    uint16 soble_xy;
    for(i=1;i<MT9V03X_H-1;i++)
    {
        for(j=1;j<MT9V03X_W-1;j++)
        {
            soble_x = (int16)*(image[i-1]+j-1)*1 + (int16)*(image[i-1]+j)*2 + (int16)*(image[i-1]+j+1)*1
                  +(int16)*(image[i+1]+j-1)*(-1) + (int16)*(image[i+1]+j)*(-2) + (int16)*(image[i+1]+j+1)*(-1);


            soble_y = (int16)*(image[i-1]+j-1)*1   +  (int16)*(image[i-1]+j+1)*(-1)
                       +(int16)*(image[i]+j-1)*2   +  (int16)*(image[i]+j+1)*(-2)
                     +(int16)*(image[i+1]+j-1)*1   +  (int16)*(image[i+1]+j+1)*(-1);

            soble_xy = my_abs(soble_x) + my_abs(soble_y);

            if (soble_xy >= threshold)
            {
                *(news[i]+j) = black;
            }
            else
            {
                *(news[i]+j) = white;
            }
        }
    }
}

/*
* @brief: 逆透视变换
* @param: uint8 (*image)[MT9V03X_W] soble处理后的图像，传入时，直接调用数组名即可
* @param: uint8 (*news)[MT9V03X_W] 逆透视变换处理后的图像，传入时，直接调用数组名即可
* @note:  将图像从摄像头坐标系转换为平面坐标系
* @time: 2023/03/13
* @author: WXQ
*/
void ImagePerspective(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W])
{
	static uint8_t BlackColor = 0;
	
	double change_un_Mat[3][3] ={{0.311538,-0.200350,24.809790},{-0.000000,0.113287,23.412587},{-0.000000,-0.002098,0.566434}}; //            70   40
    for (int i = 0; i < RESULT_COL ;i++) 
	{
        for (int j = 0; j < RESULT_ROW ;j++) 
		{
            int local_x = (int) ((change_un_Mat[0][0] * i
                    + change_un_Mat[0][1] * j + change_un_Mat[0][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            int local_y = (int) ((change_un_Mat[1][0] * i
                    + change_un_Mat[1][1] * j + change_un_Mat[1][2])
                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
                            + change_un_Mat[2][2]));
            if (local_x>= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL)
			{
                *(news[j]+i) = *(image[local_y]+local_x);
            }
            else 
			{
                *(news[j]+i) = 255;          //&PER_IMG[0][0];
            }
        }
    }
}



/*
* @brief: 寻找卡片中心点
* @param: uint8 (*image)[MT9V03X_W] 逆透视变换处理后的图像，传入时，直接调用数组名即可
* @param: Coordinate P 卡片中心点坐标指针数组
* @time: 2023/03/13
* @author: WXQ
*/
void Find_Card(uint8 (*image)[MT9V03X_W],Coordinate P)
{
	uint8 i,j;
	uint8 black_num;
	uint8 last_num;
	int8 temp_y = 0;
	uint8 min_y = 110,max_y = 10;
	uint8 min_x = 170,max_x = 10;
	for(i = 5;i<MT9V03X_W-5;i++)
	{
		black_num = 0;
		last_num = black_num;
		for(j = 5;j<MT9V03X_H-5;j++)
		{
			if(*(image[j]+i) == 0 && i>25 && i<175)
				black_num++;
		}
		if(black_num >=23 && black_num>last_num && i<min_x)
			min_x = i;
		else if(black_num >=23 && black_num>last_num && i>max_x)
			max_x = i;
	}
	P->x = (max_x+min_x)/2;
	
	for(i = 5;i<MT9V03X_H-10;i++)
	{
		if(*(image[i]+P->x) == 0 && i<min_y)
			min_y = i;
		else if(*(image[i]+P->x) == 0 && i>max_y)
			max_y = i;
	}
//	temp_y = (max_y+min_y)/2;
//	if(P->x == 90&&temp_y == 60)
//		P->y = 100;
//	else 
//		P->y = temp_y;
	
	P->y = (max_y+min_y)/2;
	if(P->x == 90 && P->y == 60)
	{
		find_point = false;
	}
	else
		find_point = true;
}
