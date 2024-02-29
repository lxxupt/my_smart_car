#ifndef _KEY_H_
#define _KEY_H_
#include "zf_common_headfile.h"

#define Boma1pin B11
#define Boma2pin B10
#define Boma3pin B9
#define Boma4pin C15

#define Key1pin C13
#define Key2pin C14
#define Key3pin C12

#define Boma1 gpio_get_level(Boma1pin)
#define Boma2 gpio_get_level(Boma2pin)
#define Boma3 gpio_get_level(Boma3pin)
#define Boma4 gpio_get_level(Boma4pin)

#define Key1 gpio_get_level(Key1pin)
#define Key2 gpio_get_level(Key2pin)
#define Key3 gpio_get_level(Key3pin)

extern uint8 project_modo;
extern uint8 mubiao_data;

void Key_Init(void);
void Key_Scan(uint8 mode);
void Key_Scan_test(uint8 mode);

#endif