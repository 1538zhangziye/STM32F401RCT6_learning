#include "stm32f4xx.h" // Device header
#include "LED.H"

void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED_PIN_1 | LED_PIN_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    GPIO_WriteBit(LED_PORT, LED_PIN_1, Bit_SET);
    GPIO_WriteBit(LED_PORT, LED_PIN_2, Bit_SET);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/*void Led_Reverse(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, (BitAction)!GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin));
}

void Led_Reverse1()
{
    GPIO_WriteBit(LED_PORT, LED_PIN_1, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_1));
}

void Led_Reverse2()
{
    GPIO_WriteBit(LED_PORT, LED_PIN_2, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_2));
}*/
