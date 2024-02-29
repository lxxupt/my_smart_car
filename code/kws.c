#include "zf_common_headfile.h"
#include "kws.h"
#include "run_kws_model_demo.h"
//ÓïÒôÄ£¿é£¬ÎðÓÃ
uint8 Kws_Num;
KwsCommand Kws_Comd = Null;

extern target Vel;
extern CorrState Corr_state;

void Kws_Get(Coordinate Next, Coordinate Mer)
{
    if(audio_data_get_finish)
    {
        Kws_Comd = audio_predict();
        switch(Kws_Comd)
        {
            case Back:Next->x = Mer->x;Next->y = Mer->y - 6;tft180_show_string(0, 20, "BACK");break;
            case Left:Next->x = Mer->x - 6;Next->y = Mer->y;tft180_show_string(0, 20, "Left");break;
            case Right:Next->x = Mer->x + 6;Next->y = Mer->y;tft180_show_string(0, 20, "Right");break;
            case Stright:Next->x = Mer->x;Next->y = Mer->y + 6;tft180_show_string(0, 20, "Stright");break;
            case LeftTurn:tft180_show_string(0, 20, "Lt");break;
            case Null:tft180_show_string(0, 20, "Null");break;
            case Pickup:tft180_show_string(0, 20, "Pick");break;
            case RightTurn:tft180_show_string(0, 20, "Rt");break;
            case Stop:tft180_show_string(0, 20, "Stop");break;
        }
        audio_data_get_finish = 0;
    }
}

void Kws_Get_test(void)
{
	if(audio_data_get_finish)
		Kws_Comd = audio_predict();
	audio_data_get_finish = 0;
}

void Kws_Control(Coordinate Next, Coordinate Mer, Target V, int16 target)
{
    if(Mer->x == Next->x && Mer->y == Next->y)
    {
        V->x = 0;
        V->y = 0;
    }
    else
        Motion_analysis(Next->x,Next->y,Mer,V,target);
}

void Kws_Control_test(void)
{
	switch(Kws_Comd)
	{
		case Back:Motion_analysis_text(0,-5,&Vel,30);break;
		case Left:Motion_analysis_text(-5,0,&Vel,30);break;
		case Right:Motion_analysis_text(5,0,&Vel,30);break;
		case Stright:Motion_analysis_text(0,5,&Vel,30);break;
		case LeftTurn:Motion_analysis_text(0,0,&Vel,30);break;
		case Null:Motion_analysis_text(0,0,&Vel,30);break;
		case Pickup:Corr_state = CorrStart;break;
		case RightTurn:Motion_analysis_text(0,0,&Vel,30);break;
		case Stop:Motion_analysis_text(0,0,&Vel,30);break;
	}
}