#ifndef CONF_USART_SERIAL_H
#define CONF_USART_SERIAL_H

/* A reference setting for UART */
/** UART Interface */
//#define CONF_UART            CONSOLE_UART
/** Baudrate setting */
//#define CONF_UART_BAUDRATE   115200
/** Parity setting */
//#define CONF_UART_PARITY     UART_MR_PAR_NO


/* A reference setting for USART */
/** USART Interface */
#define CONF_UART               CONSOLE_UART
/** Baudrate setting */
#define CONF_UART_BAUDRATE      115200
/** Character length setting */
#define CONF_UART_CHAR_LENGTH   US_MR_CHRL_8_BIT
/** Parity setting */
#define CONF_UART_PARITY        US_MR_PAR_NO
/** Stop bits setting */
#define CONF_UART_STOP_BITS     US_MR_NBSTOP_1_BIT

#endif /* CONF_USART_SERIAL_H_INCLUDED */