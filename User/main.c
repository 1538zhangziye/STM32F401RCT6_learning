#include "stm32f4xx.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Led.h"
#include "CountSensor.h"
#include "Timer.h"
#include "TimerETR.h"
#define startColumn 1
uint32_t sysFreq;

void begin()
{
    OLED_Init();
    OLED_Clear();
    Key_Init();
    Led_Init();
    CountSensor_Init();
    Timer_Init();
    TimerETR_Init();
    RCC_ClocksTypeDef get_rcc_clock;
    RCC_GetClocksFreq(&get_rcc_clock);
    sysFreq = get_rcc_clock.SYSCLK_Frequency;
    OLED_ShowString(2, startColumn, "Count");
    OLED_ShowString(3, startColumn, "Button 1");
    OLED_ShowString(4, startColumn, "Button 2");
    OLED_ShowNum(3, startColumn + 10, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
    OLED_ShowNum(4, startColumn + 10, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4), 1);
}

int main(void)
{
    begin();
    while (1)
    {
        uint8_t state1 = Key_state1();
        uint8_t state2 = Key_state2();
        OLED_ShowNum(2, startColumn + 7, CountSensor_GetCount(), 4);
        OLED_ShowNum(2, startColumn + 13, TimerETR_GetTimes(), 3);
        if (Timer_GetCount() % 7 == 0)
        {
            OLED_ShowString(1, startColumn, "Freq");
            OLED_ShowNum(1, startColumn + 7, sysFreq / 1e6, 4);
            OLED_ShowString(1, startColumn + 13, "MHz");
        }
        else
        {
            OLED_ShowString(1, startColumn, "Time   ");
            OLED_ShowNum(1, startColumn + 7, Timer_GetCount(), 4);
            OLED_ShowNum(1, startColumn + 13, TimerETR_GetCount(), 3);
        }
        if (state1 == 1 && state2 == 1)
            CountSensor_Reset();
        else
        {
            if (state1 == 2)
            {
                Led_Reverse1();
                OLED_ShowNum(3, startColumn + 10, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
            }
            if (state2 == 2)
            {
                Led_Reverse2();
                OLED_ShowNum(4, startColumn + 10, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4), 1);
            }
        }
    }
}
