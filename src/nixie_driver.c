#include <msp430.h>
#include "nixie_driver.h"

volatile int i = 0;

void InitNixieGpio()
{
	NIXIE_ENABLE_PORT_DIR_0 |= NIXIE_ENABLE_CHANNEL_0;
	NIXIE_ENABLE_PORT_DIR_1 |= NIXIE_ENABLE_CHANNEL_1;
	NIXIE_ENABLE_PORT_DIR_2 |= NIXIE_ENABLE_CHANNEL_2;
	NIXIE_ENABLE_PORT_DIR_3 |= NIXIE_ENABLE_CHANNEL_3;
	NIXIE_CTRL_PORT_DIR_0 |= NIXIE_CTRL_CHANNEL_0;
	NIXIE_CTRL_PORT_DIR_1 |= NIXIE_CTRL_CHANNEL_1;
	NIXIE_CTRL_PORT_DIR_2 |= NIXIE_CTRL_CHANNEL_2;
	NIXIE_CTRL_PORT_DIR_3 |= NIXIE_CTRL_CHANNEL_3;
	NIXIE_CTRL_PORT_DIR_4 |= NIXIE_CTRL_CHANNEL_4;
	NIXIE_CTRL_PORT_DIR_5 |= NIXIE_CTRL_CHANNEL_5;
	NIXIE_CTRL_PORT_DIR_6 |= NIXIE_CTRL_CHANNEL_6;
	NIXIE_CTRL_PORT_DIR_7 |= NIXIE_CTRL_CHANNEL_7;
}

void ClearNixie()
{
	NIXIE_ENABLE_PORT_OUT_0 |= NIXIE_ENABLE_CHANNEL_0;
	NIXIE_ENABLE_PORT_OUT_1 |= NIXIE_ENABLE_CHANNEL_1;
	NIXIE_ENABLE_PORT_OUT_2 |= NIXIE_ENABLE_CHANNEL_2;
	NIXIE_ENABLE_PORT_OUT_3 |= NIXIE_ENABLE_CHANNEL_3;
	NIXIE_CTRL_PORT_OUT_0 &= ~NIXIE_CTRL_CHANNEL_0;
	NIXIE_CTRL_PORT_OUT_1 &= ~NIXIE_CTRL_CHANNEL_1;
	NIXIE_CTRL_PORT_OUT_2 &= ~NIXIE_CTRL_CHANNEL_2;
	NIXIE_CTRL_PORT_OUT_3 &= ~NIXIE_CTRL_CHANNEL_3;
	NIXIE_CTRL_PORT_OUT_4 &= ~NIXIE_CTRL_CHANNEL_4;
	NIXIE_CTRL_PORT_OUT_5 &= ~NIXIE_CTRL_CHANNEL_5;
	NIXIE_CTRL_PORT_OUT_6 &= ~NIXIE_CTRL_CHANNEL_6;
	NIXIE_CTRL_PORT_OUT_7 &= ~NIXIE_CTRL_CHANNEL_7;
}

void DisplayOneDigit(int digit, int num)
{

	ClearNixie();
	
	switch (digit)
	{
	case 0:
		NIXIE_ENABLE_PORT_OUT_0 &=~ NIXIE_ENABLE_CHANNEL_0;
		break;
	case 1:
		NIXIE_ENABLE_PORT_OUT_1 &=~ NIXIE_ENABLE_CHANNEL_1;
		break;
	case 2:
		NIXIE_ENABLE_PORT_OUT_2 &=~ NIXIE_ENABLE_CHANNEL_2;
		break;
	case 3:
		NIXIE_ENABLE_PORT_OUT_3 &=~ NIXIE_ENABLE_CHANNEL_3;
		break;
	default:
		break;
	}

	for (i = 0; i < 8; i++)
	{
		switch (num)
		{
		case 0:
			if ( ((0x7E&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 1:
			if ( ((0x30&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 2:
			if ( ((0x6D&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 3:
			if ( ((0x79&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 4:
			if ( ((0x33&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 5:
			if ( ((0x5D&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 6:
			if ( ((0x5F&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 7:
			if ( ((0x70&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 8:
			if ( ((0x7F&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		case 9:
			if ( ((0x7B&(0x80>>i))<<i) == 0x80 )
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 |= NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 |= NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 |= NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 |= NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 |= NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 |= NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 |= NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 |= NIXIE_CTRL_CHANNEL_7;
				}
			}
			else
			{
				if (i==0)
				{
					NIXIE_CTRL_PORT_OUT_0 &=~ NIXIE_CTRL_CHANNEL_0;
				}
				if (i==1)
				{
					NIXIE_CTRL_PORT_OUT_1 &=~ NIXIE_CTRL_CHANNEL_1;
				}
				if (i==2)
				{
					NIXIE_CTRL_PORT_OUT_2 &=~ NIXIE_CTRL_CHANNEL_2;
				}
				if (i==3)
				{
					NIXIE_CTRL_PORT_OUT_3 &=~ NIXIE_CTRL_CHANNEL_3;
				}
				if (i==4)
				{
					NIXIE_CTRL_PORT_OUT_4 &=~ NIXIE_CTRL_CHANNEL_4;
				}
				if (i==5)
				{
					NIXIE_CTRL_PORT_OUT_5 &=~ NIXIE_CTRL_CHANNEL_5;
				}
				if (i==6)
				{
					NIXIE_CTRL_PORT_OUT_6 &=~ NIXIE_CTRL_CHANNEL_6;
				}
				if (i==7)
				{
					NIXIE_CTRL_PORT_OUT_7 &=~ NIXIE_CTRL_CHANNEL_7;
				}
			}
			break;
		default:
			break;
		}
	}

}