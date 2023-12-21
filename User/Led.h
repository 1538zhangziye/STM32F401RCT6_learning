#ifndef __LED_H
#define __LED_H

void Led_Init(void);
void Led_Reverse(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin);

#endif
