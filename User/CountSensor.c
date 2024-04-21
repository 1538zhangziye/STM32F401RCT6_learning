#include "stm32f4xx.h" // Device header

static uint16_t count = 0;

void CountSensor_Init()
{
    // 开启时钟，数据选择器选引脚，EXTI选中断触发模式，NVIC选中断优先级
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  // 开启GPIOx时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 开启SYSCFG时钟(数据选择器AFIO)

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 使用PB1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, GPIO_PinSource1); // 数据选择器选择中断源,GPIOx为源头，x为0,1,2...15,GPIO_PinSourcex为引脚编号，x为0,1,2...15

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_GetCount()
{
    return count;
}

void CountSensor_Reset()
{
    count = 0;
}

void EXTI1_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        // if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_x) == 0)
        count++;
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
