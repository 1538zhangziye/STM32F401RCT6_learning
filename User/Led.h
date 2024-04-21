#ifndef __LED_H
#define __LED_H

#define LED_PORT    GPIOA
#define LED_PIN_1   GPIO_Pin_3
#define LED_PIN_2   GPIO_Pin_4

void Led_Init(void);
/*void Led_Reverse(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin);
void Led_Reverse1(void);
void Led_Reverse2(void);
#define Led_Reverse1(void) GPIO_WriteBit(LED_PORT, LED_PIN_1, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_1));
#define Led_Reverse2(void) GPIO_WriteBit(LED_PORT, LED_PIN_2, (BitAction)!GPIO_ReadOutputDataBit(LED_PORT, LED_PIN_2));*/
#define Led_Reverse1(void) GPIO_ToggleBits(LED_PORT, LED_PIN_1);
#define Led_Reverse2(void) GPIO_ToggleBits(LED_PORT, LED_PIN_2);

#endif
