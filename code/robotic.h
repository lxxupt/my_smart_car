#ifndef _ROBOTIC_H_
#define _ROBOTIC_H_
#include "zf_common_headfile.h"

#define steer_1 PWM2_MODULE0_CHA_C6   //
#define steer_2 PWM2_MODULE2_CHA_C10   //
#define steer_3 PWM2_MODULE2_CHB_C11   //
#define steer_4 PWM4_MODULE2_CHA_C30    //

//#define steer_O PWM2_MODULE0_CHA_C6   //
//#define steer_G PWM2_MODULE2_CHA_C7   //
//#define steer_W PWM2_MODULE2_CHB_C10   //
//#define steer_F PWM4_MODULE2_CHA_C30    //

void Steer_Init(void);
bool RoboticArm_greb(void);
bool RoboticArm_freed(void);
bool RoboticArm_revole(uint8 data);
bool RoboticArm_revole_J(uint8 data);
bool RoboticArm_bodong(uint8 data);
bool RoboticArm_bodong_J(uint8 data);

void Robot_test(void);





#endif