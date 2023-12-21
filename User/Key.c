#include "stm32f4xx.h" // Device header
#include "Delay.h"

uint8_t previous_state1 = Bit_SET;
uint8_t previous_state2 = Bit_SET;

void Key_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_isPressed(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin)
{
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
    {
        Delay_ms(10);
        while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
            ;
        Delay_ms(10);
        return 1;
    }
    return 0;
}

uint8_t Key_state1()
{
    uint8_t output = 0;
    uint8_t current_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
    if (previous_state1 == Bit_RESET && current_state == Bit_RESET)
        output = 1;
    else if (current_state != previous_state1)
    {
        Delay_ms(10);
        if (current_state == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
            if (current_state == Bit_SET && previous_state1 == Bit_RESET)
                output = 2;
    }
    previous_state1 = current_state;
    return output;
}

uint8_t Key_state2()
{
    uint8_t output = 0;
    uint8_t current_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
    if (previous_state2 == Bit_RESET && current_state == Bit_RESET)
        output = 1;
    else if (current_state != previous_state2)
    {
        Delay_ms(10);
        if (current_state == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))
            if (current_state == Bit_SET && previous_state2 == Bit_RESET)
                output = 2;
    }
    previous_state2 = current_state;
    return output;
}
