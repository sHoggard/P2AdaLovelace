#include <asf.h>
#include "I2CFunctions.h"
#include "test.h"

/*int main (void)
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
		//Lyft vinglas
		//Case 3
		send_package(0x24, TWI_SLAVE_ADR_PAB);
		//Lämna av object
		//Case 4
		send_package(0x25, TWI_SLAVE_ADR_PAB);
		
		
			//	Uppstart POSITIONERING
			//send_package(0x20, TWI_SLAVE_ADR_POS);
			delay_ms(1000);
			// Läser från påbyggnaden och skriver ut från på byggnaden
			read_package(TWI_SLAVE_ADR_POS);
			int i;
			for(i=0; i<10 ;i++)
			{
				if (i == 0)
				{
					x_koord_Box = rec_data_pos[i];
				}
				if (i == 1)
				{
					y_koord_Box = rec_data_pos[i];
				}
				if (i == 2)
				{
					x_koord_Kub = rec_data_pos[i];
				}
				if (i == 3)
				{
					x_koord_Kub = rec_data_pos[i];
				}
				if (i == 4)
				{
					x_koord_Kula = rec_data_pos[i];
				}
				if (i == 5)
				{
					y_koord_Kula = rec_data_pos[i];
				}
				if (i == 6)
				{
					x_koord_Vinglas = rec_data_pos[i];
				}
				if (i == 7)
				{
					y_koord_Vinglas = rec_data_pos[i];
				}
				if (i == 8)
				{
					x_koord_Robot = rec_data_pos[i];
				}
				if (i == 9)
				{
					y_koord_Robot = rec_data_pos[i];
				}
			}
				rec_data_pos[i]
				
				printf(" %d",);
			}
		
	}*/
	
