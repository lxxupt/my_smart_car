#ifndef _KWS_H_
#define _KWS_H_

typedef enum
{
	Back = 0,
	Left,
    LeftTurn,
    Null,
    Pickup,
    Right,
    RightTurn,
    Stop,
    Stright,
}KwsCommand;

void Kws_Get(Coordinate Next, Coordinate Mer);
void Kws_Get_test(void);
void Kws_Control(Coordinate Next, Coordinate Mer, Target V, int16 target);
void Kws_Control_test(void);

#endif