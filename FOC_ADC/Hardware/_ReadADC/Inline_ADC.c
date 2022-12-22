#include "Inline_ADC.h"

uint32_t ADC_Value_Temp[ADC_Channel_Num];
    
float ADC_Read_Filter(uint8_t channel)
{
    float Value,Value_Final;
    double Value_New,Value_Temp;
    Value_New = ADC_Value_Temp[channel];
    for(uint16_t Count = 0;Count < ADC_Buffer;Count++)  
    {
      Value_Temp += Value_New;
    }
    Value = Value_Temp / ADC_Buffer;
    Value_Final = Value * 3.3f /4096;

    return Value_Final;
}

void ADC_Start_lnit(void)
{
    HAL_ADC_Start_DMA(&hadcX,(uint32_t *)ADC_Value_Temp,ADC_Channel_Num);
}

