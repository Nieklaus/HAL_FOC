#include "Usrt.h"
//By LJR
//在mian函数中写这个
//__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);       //打开IDLE中断
//  HAL_UART_Receive_DMA(&huart1,rx1_buffer,BUFFER_SIZE);    //开启DMA接受
//在stm32f1xx_it.c串口中断函数中使用
//记得在stm32f1xx_it.c中引用该头文件
//Usart1_IDLE();                        //IDIE接受
	
#if 1   
//  struct __FILE //该段在keil内不报错，vscode中报错，如不报错可去除注释
//  { 
//    int handle; 
//  }; 

//FILE __stdout;  //定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x) 
{ 
  x = x; 
} 
//重定向fputc函数S
int fputc(int ch,FILE *p)
{
	while(!(USART1->SR & (1<<7)));
	USART1->DR = ch;
	return ch;
}
#endif

//volatile保证共享内存使所有线程的工作都可以获得数据改变
volatile uint32_t rx1_len = 0;        //接收一帧数据的长度
volatile uint8_t rec1_end_flag = 0;   //一帧数据接收完成标志
uint8_t rx1_buffer[BUFFER_SIZE]={0};  //接收数据缓存数组

uint32_t i;
uint8_t multi1,multi2;
uint8_t Subscript_Flag;
uint32_t Data_Buffer1,Data_Buffer2;

void Usart1_IDLE(void)
{
  uint32_t tmp_flag = 0;
  uint32_t temp;
  tmp_flag = __HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE);         //获取IDIE标志位
  if((tmp_flag != RESET))                                         //判断是否进入空闲中断
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);                           //清除标志位
    HAL_UART_DMAStop(&huart1);                                    //停止DMA传输
    temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);                //获取未传输的数据个数
    rx1_len = BUFFER_SIZE - temp;
    rec1_end_flag = 1;
  }
}

void Usart1_Handle(void)                                         //对接受的一帧数据进行处理
{
  // if((rx1_buffer[0] == 'A') && (rx1_buffer[rx1_len-1] == 'S'))   //当串口发送器不发送新行时，有时串口2,3(不是串口1的时钟线)用这个判断
  if((rx1_buffer[0] == 'A') && (rx1_buffer[rx1_len-3] == 'S') && (rx1_buffer[rx1_len-2] == 0x0D) && ((rx1_buffer[rx1_len-1] == 0x0A)))
  {
//    if(rx1_buffer[1] == 'O')                                   //测试函数
//    {
//      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,RESET);
//    }
//    if(rx1_buffer[1] == 'F')
//    {
//      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,SET);
//    }
  }


//	cJSON* cJson_Target = NULL;                      //cJSON赋值函数
//    	cJSON* cjtemp = NULL;	  
	 
//	cJson_Target = cJSON_Parse((char*)rx1_buffer);
//	  for(i = 0;i < sizeofkey();i++)
//	  {
//		  cjtemp = cJSON_GetObjectItem(cJson_Target,cJson_key[i]);
//		  if(cjtemp != NULL)
//		  {
//			  *cJson_value[i] = cjtemp->valueint;
//		  }
//	  }
//	  cJSON_Delete(cJson_Target);


//	Data_Buffer1 = 0;
//	multi1 = 1;
//	Data_Buffer2 = 0;
//	multi2 = 1;
//	for(i = 0;i < rx1_len;i++)                //取值函数
//	  {
//		  if((rx1_buffer[i] >= '0') && (rx1_buffer[i] <= '9'))
//		  {
//			  rx1_buffer[i] = rx1_buffer[i]-48;
//		  }
//		  if(rx1_buffer[i] == 'B')
//		  {
//			  Subscript_Flag = i;
//		  }
//	  }
//	for(int k = Subscript_Flag - 1;k > 0;k--)
//	  {
//		  Data_Buffer1 += multi1 * rx1_buffer[k];
//		  multi1 *= 10;
//	  }
//	for(int p = rx1_len - 4;p > Subscript_Flag;p--)
//	  {
//		  Data_Buffer2 += multi2 * rx1_buffer[p];
//		  multi2 *= 10;
//	  }

  // DMA_Usart1_Send(rx1_buffer,rx1_len);                           //将接受的数据发回发送端
  rx1_len = 0;                                                   //清除计数
	if(rx1_buffer[rx1_len - 3] == 'S')                               //防止数据间隔后导致数据丢失（仅测试）
  {
		rec1_end_flag = 0;                                             //清除结束标志位
  }
  HAL_UART_Receive_DMA(&huart1,rx1_buffer,BUFFER_SIZE);          //重新打开DMA接受
}

void DMA_Usart1_Send(uint8_t *buf,uint8_t len)                   //向串口发送
{
  if(HAL_UART_Transmit_DMA(&huart1,buf,len) != HAL_OK)           //如果异常进入异常中断
  {
    Error_Handler();
  }
}


