#ifndef __Low_pass_filtering_H__
#define __Low_pass_filtering_H__

typedef struct 
{
	float Tf; 						//低通滤波时间常数
	float y_prev; 					//上一次函数的值
	unsigned long timestamp_prev;   //上一次执行的时间常数
} LowPassFilter;

#endif

