/*
 * USRK7.h
 *
 *  Created on: Sep 15, 2023
 *      Author: mn
 */

#ifndef INC_USRK7_H_
#define INC_USRK7_H_

#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"

#define USRK7_BUFFER_SIZE 64
#define USRK7_COMMAND_SIZE 64

#define USRK7_SERVER_IP "185.80.128.201"
#define USRK7_SERVER_PORT 3911
#define USRK7_UDP_PORT 80

extern UART_HandleTypeDef *USRK7_UART;
extern char USRK7_BUFFER[USRK7_BUFFER_SIZE];
extern char USRK7_COMMAND[USRK7_COMMAND_SIZE];

int USRK7_init(UART_HandleTypeDef *huart);

#endif /* INC_USRK7_H_ */
