#include "USRK7.h"

UART_HandleTypeDef *USRK7_UART;
char USRK7_BUFFER[USRK7_BUFFER_SIZE];
char USRK7_COMMAND[USRK7_COMMAND_SIZE];

HAL_StatusTypeDef USRK7_transmit(const char *command, int timeout) {
	return HAL_UART_Transmit(USRK7_UART, (uint8_t*) command, strlen(command),
			timeout);
}

USRK7_Status USRK7_receive(int attempt, int timeout) {
	memset(USRK7_BUFFER, 0, USRK7_BUFFER_SIZE);

	for (int i = 0; i < attempt; i++) {
		HAL_UART_Receive(USRK7_UART, (uint8_t*) USRK7_BUFFER, USRK7_BUFFER_SIZE,
				timeout);

		if (strlen(USRK7_BUFFER) >= 1) {
			return USRK7_OK;
		}
	}

	return USRK7_ERROR;
}

USRK7_Status USRK7_transmit_receive(const char *command, int tTimeout,
		int rTimeout, int attempt) {
	HAL_StatusTypeDef transmitResult = USRK7_transmit(command, tTimeout);

	if (transmitResult != HAL_OK) {
		return USRK7_ERROR;
	}

	return USRK7_receive(attempt, rTimeout);
}

int USRK7_init(UART_HandleTypeDef *uart) {
	USRK7_UART = uart;

	USRK7_Status status = USRK7_OK;

	sprintf(USRK7_COMMAND, "AT+ENTM\r\n");
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	sprintf(USRK7_COMMAND, "+++");
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	if (!strstr(USRK7_BUFFER, "a")) {
		return USRK7_ERROR;
	}

	HAL_Delay(130);
	sprintf(USRK7_COMMAND, "a");
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	if (!strstr(USRK7_BUFFER, "+ok")) {
		return USRK7_ERROR;
	}

	sprintf(USRK7_COMMAND, "AT+WANN=static,%s,%s,%s\r\n", USRK7_IP,
	USRK7_SUBMASK, USRK7_GATEWAY);
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	sprintf(USRK7_COMMAND, "AT+SOCKA1=UDPC,%s,%d\r\n", USRK7_SERVER_IP,
	USRK7_SERVER_PORT);
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	sprintf(USRK7_COMMAND, "AT+DNS=%s\r\n", USRK7_DNS);
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	sprintf(USRK7_COMMAND, "AT+Z\r\n");
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	sprintf(USRK7_COMMAND, "AT+ENTM\r\n");
	status = USRK7_transmit_receive(USRK7_COMMAND, 1000, 150, 10);
	if (status != USRK7_OK) {
		return status;
	}

	return 0;
}
