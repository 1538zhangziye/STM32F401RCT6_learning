#ifndef __KEY_H
#define __KEY_H

void Key_Init(void);
uint8_t Key_isPressed(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin);
uint8_t Key_state1(void);
uint8_t Key_state2(void);

#endif
