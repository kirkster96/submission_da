/*
 * ADPS_master.h
 *
 * Created: 12/12/2019 8:27:26 PM
 *  Author: Kirks
 */ 


#ifndef ADPS_MASTER_H_
#define ADPS_MASTER_H_

#define APDS9960_WRITE 0x72
#define APDS9960_READ 0x73



void init_uart(uint16_t baudrate);
void uart_putc(unsigned char c);
void uart_puts(char *s);
void init_APDS9960(void);

#endif /* ADPS_MASTER_H_ */


