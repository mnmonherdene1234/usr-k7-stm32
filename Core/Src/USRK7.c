#include "USRK7.h"

UART_HandleTypeDef *USRK7_UART;
char USRK7_BUFFER[USRK7_BUFFER_SIZE];
char USRK7_COMMAND[USRK7_COMMAND_SIZE];

static void USRK7_transmit(const char *command, int timeout) {
	HAL_UART_Transmit(USRK7_UART, (uint8_t*) command, strlen(command), timeout);
}

static void USRK7_receive(int timeout) {
	sprintf(USRK7_BUFFER, "");
	HAL_UART_Receive(USRK7_UART, (uint8_t*) USRK7_BUFFER, USRK7_BUFFER_SIZE,
			timeout);
}

static void USRK7_transmit_receive(const char *command, int tTimeout,
		int rTimeout) {
	USRK7_transmit(command, tTimeout);
	USRK7_receive(rTimeout);
}

int USRK7_init(UART_HandleTypeDef *uart) {
	USRK7_UART = uart;

	sprintf(USRK7_COMMAND, "+++");
	USRK7_transmit(USRK7_COMMAND, 3000);
	USRK7_receive(200);

	if (strstr(USRK7_BUFFER, "a")) {
		sprintf(USRK7_COMMAND, "a");
		USRK7_transmit(USRK7_COMMAND, 1000);

		// Step 4: Wait for '+ok' response
		USRK7_receive(3000);
		if (strstr(USRK7_BUFFER, "+ok")) {
			sprintf(USRK7_COMMAND, "AT+VER\r\n");
			USRK7_transmit_receive(USRK7_COMMAND, 200, 200);

			return 0; // Initialization successful
		}
	}

	return -1; // Initialization failed
}
