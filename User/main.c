#include "stm32f4xx.h" // Device header
#include "Delay.h"
#include "OLED.h"

void begin()
{
    OLED_Init();
    OLED_Clear();
    RCC_ClocksTypeDef get_rcc_clock;
    RCC_GetClocksFreq(&get_rcc_clock);
    OLED_ShowString(1, 3, "Freq");
    OLED_ShowNum(1, 8, get_rcc_clock.SYSCLK_Frequency / 1000000, 3);
    OLED_ShowString(1, 11, "MHz");

    GPIO_InitTypeDef GPIO_InitStructure1;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
    GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);

    GPIO_InitTypeDef GPIO_InitStructure2;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure2);

    OLED_ShowString(3, 3, "Button 1");
    OLED_ShowString(4, 3, "Button 2");
    OLED_ShowNum(3, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
    OLED_ShowNum(4, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
}

uint8_t isPressed(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin)
{
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
    {
        Delay_ms(10);
        while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
            ;
        while (1)
        {
            Delay_ms(10);
            if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_SET)
                return 1;
            while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
                ;
        }
    }
    return 0;
}

int main(void)
{
    begin();
    while (1)
    {
        if (isPressed(GPIOA, GPIO_Pin_6))
        {
            GPIO_WriteBit(GPIOA, GPIO_Pin_3, (BitAction)!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3));
            OLED_ShowNum(3, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3), 1);
        }
        if (isPressed(GPIOA, GPIO_Pin_7))
        {
            GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4));
            OLED_ShowNum(4, 13, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4), 1);
        }
    }
}
