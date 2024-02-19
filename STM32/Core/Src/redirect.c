#include <stdio.h>
#include "main.h"

extern UART_HandleTypeDef huart2;


void __io_putchar(uint8_t ch) {
	HAL_UART_Transmit(&huart2, &ch, 1, 1);
}
