#include "stm32f4xx.h" // Device header

#define LED_PORT    GPIOA
#define LED_PIN_1   GPIO_Pin_3
#define LED_PIN_2   GPIO_Pin_4

void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  LED_PIN_1 | LED_PIN_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    GPIO_WriteBit(LED_PORT, LED_PIN_1, Bit_SET);
    GPIO_WriteBit(LED_PORT, LED_PIN_2, Bit_SET);
}

/*void Led_Reverse(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, (BitAction)!GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin));
}*/

void Led_Reverse1()
{
    GPIO_WriteBit(LED_PORT, LED_PIN_1, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_1));
}

void Led_Reverse2()
{
    GPIO_WriteBit(LED_PORT, LED_PIN_2, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_2));
}
