#include "PID_Motor.h"

PID_Controller  PID_Current_q,PID_Current_d,PID_Velocity,PID_Angle;

void PID_init(void)    //Motor_init()函数已经对limit初始化，此处无需处理
{
	PID_Velocity.P=0.5;  //0.5
	PID_Velocity.I=0;    //0.5
	PID_Velocity.D=0;
	PID_Velocity.output_ramp=0;   
	//PID_Velocity.limit=0;               
	PID_Velocity.error_prev=0;
	PID_Velocity.output_prev=0;
	PID_Velocity.integral_prev=0;
	PID_Velocity.timestamp_prev=0;
	
	PID_Angle.P=20;
	PID_Angle.I=0;
	PID_Angle.D=0;
	PID_Angle.output_ramp=0;
	//PID_Angle.limit=0;
	PID_Angle.error_prev=0;
	PID_Angle.output_prev=0;
	PID_Angle.integral_prev=0;
	PID_Angle.timestamp_prev=0;
	
	PID_Current_q.P=0.5;                //航模电机，速度闭环，不能大于1，否则容易失控
	PID_Current_q.I=0;                  //电流环I参数不太好调试，只用P参数也可以
	PID_Current_q.D=0;
	PID_Current_q.output_ramp=0;
	//PID_Current_q.limit=0;
	PID_Current_q.error_prev=0;
	PID_Current_q.output_prev=0;
	PID_Current_q.integral_prev=0;
	PID_Current_q.timestamp_prev=0;
	
	PID_Current_d.P=0.5;  //0.5
	PID_Current_d.I=0;
	PID_Current_d.D=0;
	PID_Current_d.output_ramp=0;
	//PID_Current_d.limit=0;
	PID_Current_d.error_prev=0;
	PID_Current_d.output_prev=0;
	PID_Current_d.integral_prev=0;
	PID_Current_d.timestamp_prev=0;
}

void sj(void)
{
    
}