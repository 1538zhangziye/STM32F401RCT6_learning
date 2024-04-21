#include "stm32f4xx.h" // Device header
#include "stdio.h"

static uint8_t RxData;
static uint8_t RxFlag;

void Uart_Init(uint32_t Baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStructure);

    USART_ClearFlag(USART1, USART_FLAG_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Data)
{
    USART_SendData(USART1, Data);
    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE))
        ;
}

void Serial_SendArray(uint8_t *Data, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
        Serial_SendByte(Data[i]);
}

void Serial_SendString(char *Data)
{
    while (*Data)
    {
        Serial_SendByte(*Data);
        Data++;
    }
}

void Serial_SendNum(uint32_t Num)
{
    char buffer[10] = {0};
    sprintf(buffer, "%d", Num);
    Serial_SendString(buffer);
}

int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

uint8_t Serial_Available()
{
    return RxFlag;
}

uint8_t Serial_Read()
{
    RxFlag = 0;
    return RxData;
}

void USART1_IRQHandler()
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        RxData = USART_ReceiveData(USART1);
        RxFlag = 1;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
