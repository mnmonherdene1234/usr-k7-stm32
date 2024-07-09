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

#define USRK7_BUFFER_SIZE 512
#define USRK7_COMMAND_SIZE 512

#define USRK7_IP "192.168.1.8"
#define USRK7_SUBMASK "192.168.1.8"
#define USRK7_GATEWAY "192.168.1.1"
#define USRK7_DNS "8.8.8.8"

#define USRK7_SERVER_IP "192.168.1.10"
#define USRK7_SERVER_PORT 3399

typedef enum {
	USRK7_OK = 0, USRK7_ERROR = 1,
} USRK7_Status;

extern UART_HandleTypeDef *USRK7_UART;
extern char USRK7_BUFFER[USRK7_BUFFER_SIZE];
extern char USRK7_COMMAND[USRK7_COMMAND_SIZE];

HAL_StatusTypeDef USRK7_transmit(const char *command, int timeout);
USRK7_Status USRK7_receive(int attempt, int timeout);
USRK7_Status USRK7_transmit_receive(const char *command, int tTimeout,
		int rTimeout, int attempt);
int USRK7_init(UART_HandleTypeDef *huart);

#endif /* INC_USRK7_H_ */
