#include <asf.h>
#include "I2CFunctions.h"
#include "test.h"

int main (void)
{
	sysclk_init();
	board_init();
	delay_init();
	console_init();
	
	if(init_twi())
	{

		//	Uppstart 
		send_package(0x20, TWI_SLAVE_ADR_PAB);
		delay_ms(1000);
		// Läser från påbyggnaden och skriver ut från på byggnaden
		read_package(TWI_SLAVE_ADR_PAB);
		for(int i=0;i<10;i++)
		{
			printf(" %d",rec_data_pos[i]);
		}
		// Switchcase sats behövs
		// Lyft kula
		//Case 1
		send_package(0x21, TWI_SLAVE_ADR_PAB);
		//Lyft vinglas
		//Case 2
		send_package(0x23, TWI_SLAVE_ADR_PAB);
		//Avbryt lyft
		//Case 3
		send_package(0x24, TWI_SLAVE_ADR_PAB);
		//Lämna av object
		//Case 4
		send_package(0x25, TWI_SLAVE_ADR_PAB);
		
	}
	
}
