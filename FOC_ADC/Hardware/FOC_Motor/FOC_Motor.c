#include "FOC_Motor.h"

float zero_electric_angle;
long sensor_direction;

void Motor_Init(void)
{
    printf("Motor Start Init");

    if(Motor_init.voltage_sensor_align > Motor_init.voltage_limit)    //防止校准电流过大
    {
        Motor_init.voltage_sensor_align = Motor_init.voltage_limit;
    }

    PID_Current_q.limit = Motor_init.voltage_limit;         //Iq和Id最终会反馈成电压后输出至SVPWM，因此使用电压限制他。
	PID_Current_d.limit = Motor_init.voltage_limit;
    PID_Velocity.limit = Motor_init.current_limit;          //通过设定的最大电流来给PID的反馈速度进行一个的限制

    M1_Enable;
	printf("MOT: Enable driver.\r\n");
}

void Motor_FOC_Init(float zero_electric_offset,Direction _sensor_direction)
{
    if(zero_electric_offset != 0)
    {
        zero_electric_angle = zero_electric_offset;
    }
    if(_sensor_direction != 0)
    {
        sensor_direction = _sensor_direction;
    }
    
}

