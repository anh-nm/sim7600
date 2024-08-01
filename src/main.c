
/* Includes */
#include "../middle/init.h"

int main(void)
{
  init();
  //led_on();

  uart_send_string(UART_PORT, "Test log\r\n");

  while (1)
  {
	  led_on();
	  gsm_data_receive();
	  loop();
	  //button_loop();
	  
  }

  return 0;
}
