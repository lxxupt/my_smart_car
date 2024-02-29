#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "zf_common_headfile.h"

#define black      0
#define white      255
#define RESULT_ROW 120//结果图行列
#define RESULT_COL 188
#define USED_ROW   120  //用于透视图的行列
#define USED_COL   188



extern bool find_point;
extern uint8 a;

void Gos_filter(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W]);
void soble(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W] , uint8 threshold);
void ImagePerspective(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W]);
void Dilate(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W]);
void Find_Card(uint8 (*image)[MT9V03X_W],Coordinate P);
void Corr_test(void);
void Compress(uint8 (*image)[MT9V03X_W], uint8 (*news)[MT9V03X_W]);
bool Soble(uint8 (*image)[MT9V03X_W], uint8 (*New)[MT9V03X_W]);
bool scan_picture(uint8 (*image)[MT9V03X_W], Coordinate P);




#endif