#include "stm32f4xx.h" // Device header

void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}

void Led_Reverse(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, (BitAction)!GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin));
}