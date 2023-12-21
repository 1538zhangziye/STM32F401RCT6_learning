#include "stm32f4xx.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Led.h"
#include "CountSensor.h"

void begin()
{
    OLED_Init();
    OLED_Clear();
    Key_Init();
    Led_Init();
    CountSensor_Init();

    RCC_ClocksTypeDef get_rcc_clock;
    RCC_GetClocksFreq(&get_rcc_clock);
    OLED_ShowString(1, 3, "Freq");
    OLED_ShowNum(1, 8, get_rcc_clock.SYSCLK_Frequency / 1000000, 3);
    OLED_ShowString(1, 11, "MHz");
    OLED_ShowString(2, 3, "Count");
    OLED_ShowString(3, 3, "Button 1");
    OLED_ShowString(4, 3, "Button 2");
    OLED_ShowNum(3, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
    OLED_ShowNum(4, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4), 1);
}

int main(void)
{
    begin();
    while (1)
    {
        uint8_t state1 = Key_state1();
        uint8_t state2 = Key_state2();
        OLED_ShowNum(2, 10, CountSensor_GetCount(), 4);
        if (state1 == 1 && state2 == 1)
            CountSensor_Reset();
        else
        {
            if (state1 == 2)
            {
                Led_Reverse(GPIOA, GPIO_Pin_3);
                OLED_ShowNum(3, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
            }
            if (state2 == 2)
            {
                Led_Reverse(GPIOA, GPIO_Pin_4);
                OLED_ShowNum(4, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4), 1);
            }
        }
    }
}
