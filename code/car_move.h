#ifndef _CAR_MOVE_H_
#define _CAR_MOVE_H_
#include "zf_common_headfile.h"

#define C_X    (85)//½ÃÕý×ø±ê//91  //76
#define C_Y    (72)         //83  //70
#define Obj_X  (170)//Ä¿±ê¼ì²â×ø±ê
#define Obj_Y  (200)

//½ÃÕý×´Ì¬
typedef enum
{
	CorrReady = 0,
	CorrStart,
	CorrLoading_1,
	CorrLoading_2,
	CorrLoading_3,
	CorrFinish,
}CorrState;

//°áÔË×´Ì¬
typedef enum
{
	TranReady = 0,
	TranStart,
	TranGet,
	TranLoading,
	TranFinish,
}TranState;

//Ð¶¿¨×´Ì¬
typedef enum
{
	StorReady = 0,
	StorStart,
	StorFinish,
}StorState;

//Ä¿±ê¼ì²â×´Ì¬
typedef enum
{
	ObjReady = 0,
	ObjStart,
	ObjFinish,
}ObjState;

//³µÁ¾ÔË¶¯×´Ì¬
typedef enum
{
	CarReady = 0,
	OutGarage,
	CarMove,
	StorageCard,
	EnterGarage,
	WordControl,
	ObjScan,
	WaitObj,
	CarStop,
}CarState;

typedef struct target
{
	float x;
	float y;
}target,*Target;

typedef struct coordinate
{
	int8 x;
	int8 y;
	int16 angle;
	bool flag;
	
}coordinate,*Coordinate;

bool Motor_target(Target V,Wheel L1, Wheel L2, Wheel L3, Wheel L4);
bool Motion_analysis(int8 x ,int8 y, Coordinate Mer, Target V, int16 target);
bool Motion_analysis_text(int8 p_x ,int8 p_y, Target V, int16 target);
void Correction_PID(uint8 recv_x,uint8 recv_y,uint8 COR_X,uint8 COR_Y,Target V ,float a);
bool dijkstra_plan(Coordinate P,Coordinate new,uint8 num);
void Obj_Detection_Control(uint16 obj_x,uint8 obj_y,uint8 COR_X,uint8 COR_Y,Target V ,float a);
bool New_Motion_analysis_text(int8 p_x ,int8 p_y, Target V, int16 target);


#endif