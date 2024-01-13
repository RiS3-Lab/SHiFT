/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}


/*
void putchar(uint8_t ch) {
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	io_write(io, (uint8_t *)ch, 1);
}



int _write (int fd, char *buf, int count) {
    struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	return io_write(io, (uint8_t *)buf, count);
 
}
*/

/*
 
 int _write (int fd, char *buf, int count) {
  int written = 0;

  for (; count != 0; --count) {
    if (usart_serial_putchar(&stdio_uart_module, (uint8_t)*buf++)) {
      return -1;
    }
    ++written;
  }
  return written;
}
 */