#include <msp430.h>
#include "intg_fan.h"

const double kMotorPwmRatio[8] = {0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70};
const int kEinkRefreshTimeCounterMax = EINK_REFRESH_TIME/1000*(8000000/0xFFFF);
// const int kNixieRefreshTimeCounterMax = NIXIE_REFRESH_TIME/1000*(8000000/0x1000);
volatile unsigned int eink_refresh_time_counter = 0;
// volatile unsigned int nixie_refresh_time_counter = 0;

void InitClock(void)
{
	/**
	 * @brief MCLK: 16MHz, SMCLK: 8MHz, ACLK: 32KHz
	 * 
	 */
	UCSCTL6 &= ~XT1OFF;          
	P5SEL |= BIT2 + BIT3;        
	UCSCTL6 &= ~XT2OFF;          
	__bis_SR_register(SCG0);
	UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
	UCSCTL1 = DCORSEL_4;
	UCSCTL2 = FLLD_5;
	UCSCTL3 = SELREF_5 + FLLREFDIV_3;
	UCSCTL4 = SELA_4 + SELS_3 +SELM_3;
	UCSCTL5 = DIVA_5 +DIVS_1;
}

void InitMotorDriver(void)
{

	/**
	 * @brief DRV8837 H-bridge driver
	 * 
	 */

    P1DIR |= BIT5;  // NSLEEP
    P1SEL |= BIT5;
    P2DIR |= BIT4;  // IN1
    P2OUT &= ~BIT4; 
    P2DIR |= BIT5;  // IN2
    P2OUT |= BIT5; 

}

void InitHCI(void)
{
	
	/**
	 * @brief Configure HCI Button S1,S2,S3,S4 as interrupt sources
	 * 
	 */

    P1REN |= BIT2;  // Button S1
    P1OUT |= BIT2;
    P1IES &= ~BIT2;
    P1IFG &= ~BIT2;
    P1IE |= BIT2;
    
    P1REN |= BIT3;  // Button S2
    P1OUT |= BIT3;
    P1IES &= ~BIT3;
    P1IFG &= ~BIT3;
    P1IE |= BIT3;
    
    P2REN |= BIT3;  // Button S3
    P2OUT |= BIT3;
    P2IES &= ~BIT3;
    P2IFG &= ~BIT3;
    P2IE |= BIT3;
    
    P2REN |= BIT6;  // Button S4
    P2OUT |= BIT6;
    P2IES &= ~BIT6;
    P2IFG &= ~BIT6;
    P2IE |= BIT6;

}

void InitCurrentSensor(void)
{
	/**
	 * @brief ADC for current sensor INA210
	 * 
	 */

	ADC12CTL0 |= ADC12MSC;     // Automatic loop sampling conversion
	ADC12CTL0 |= ADC12ON;      // Enable ADC12 module
	ADC12CTL1 |= ADC12CONSEQ1; // Single Channel mode
	ADC12CTL1 |= ADC12SHP;     // ZOH mode
	ADC12MCTL0 |= ADC12INCH_6; // Channel 6 connected with current sensor module (Pocket-Lab schematic)
	ADC12CTL0 |= ADC12ENC;
	ADC12CTL0 |= ADC12SC;
}

void InitMotorPwm(void)
{

	/**
	 * @brief Timer_A0 for PWM generating
	 * 
	 */

	TA0CTL |= TASSEL_2;// Timer_A0 clock source select: SMCLK 8MHz
	TA0CTL |= MC_1;// Mode control: up mode
	TA0CTL |= TACLR;// Timer_A0 clear

	// Timer_A0 Capture/Compare Control 4 Register
	TA0CCTL4 = OUTMOD_7;// Reset/set mode
	TA0CCR0 = PWM_PEROID;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.


	/**
	 * @brief Timer_A2 for LED-nixie refreshing
	 * 
	 */

	// TA2CTL |= TASSEL_2;// Timer_A2 clock source select: SMCLK 8MHz
	// TA2CTL |= MC_1;// Mode control: up mode
	// TA2CTL |= TACLR;// Timer_A2 clear
	// TA2CCTL0 = CCIE;// enable capture/compare interrupt
	// TA2CCR0 = 0x1000;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.

}

void InitEinkRefreshCounter(void)
{

	/**
	 * @brief Timer_A1 for E-Ink Screen refreshing
	 * 
	 */

	TA1CTL |= TASSEL_2;// Timer_A1 clock source select: SMCLK 8MHz
	TA1CTL |= MC_1;// Mode control: up mode
	TA1CTL |= TACLR;// Timer_A1 clear
	TA1CCTL0 = CCIE;// enable capture/compare interrupt
	TA1CCR0 = 0xFFFF;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.

}

void MotorAutoControl(void)
{

}

void MotorManualControl(void)
{

	switch (intg_fan_status.motor_speed_level)
	{
	case 0:
		TA0CCR4 = kMotorPwmRatio[0] * PWM_PEROID;
		break;
	case 1:
		TA0CCR4 = kMotorPwmRatio[1] * PWM_PEROID;
		break;
	case 2:
		TA0CCR4 = kMotorPwmRatio[2] * PWM_PEROID;
		break;
	case 3:
		TA0CCR4 = kMotorPwmRatio[3] * PWM_PEROID;
		break;
	case 4:
		TA0CCR4 = kMotorPwmRatio[4] * PWM_PEROID;
		break;
	case 5:
		TA0CCR4 = kMotorPwmRatio[5] * PWM_PEROID;
		break;
	case 6:
		TA0CCR4 = kMotorPwmRatio[6] * PWM_PEROID;
		break;
	case 7:
		TA0CCR4 = kMotorPwmRatio[7] * PWM_PEROID;
		break;
	default:
		break;
	}

}

void PowerOn(void)
{

}

void PowerOff(void)
{
    // MYRESET();
	// TA0CCR4 = 0;
}

void MeasureTemperature(void)
{

	unsigned char* p_temperature_integral_part = (R_I2C(0x55,0x00) - 64);
	unsigned char* p_temperature_decimal_part = (((R_I2C(0x55,0x10) >> 4) * 625) / 100);
	intg_fan_status.local_temperature = 100*(int)(*(&(p_temperature_integral_part))) + (int)(*(&(p_temperature_decimal_part)));

}

void MeasureMotorCurrent(void)
{

	volatile unsigned int motor_current_ad_value = ADC12MEM0;
	intg_fan_status.motor_current = motor_current_ad_value*3300/4095*0.98;

}

void DisplayEinkScreen(void)
{

	char str_fan_mode[16] = "mode: "; 
	char str_motor_status[16] = "motor: ";
	char str_motor_speed_level[16] = "speed: "; 
	char str_temperature[16] = "temp: ";

	// Fan mode
	switch (intg_fan_status.fan_mode)
	{
	case FAN_AUTO_MODE:
		strcat(str_fan_mode, "auto");
		break;
	
	case FAN_MANUAL_MODE:
		strcat(str_fan_mode, "manual");
		break;

	default:
		break;
	}

	// Motor mode
	switch (intg_fan_status.motor_mode)
	{
	case MOTOR_TURN:
		strcat(str_motor_status, "turn");
		break;
	
	case MOTOR_REVERSE:
		strcat(str_motor_status, "reverse");
		break;

	default:
		break;
	}

	// Fan status
	switch (intg_fan_status.motor_speed_level)
	{
	case MOTOR_SPEED_0:
		strcat(str_motor_speed_level, "1");
		break;

	case MOTOR_SPEED_1:
		strcat(str_motor_speed_level, "2");
		break;

	case MOTOR_SPEED_2:
		strcat(str_motor_speed_level, "3");
		break;

	case MOTOR_SPEED_3:
		strcat(str_motor_speed_level, "4");
		break;

	case MOTOR_SPEED_4:
		strcat(str_motor_speed_level, "5");
		break;

	case MOTOR_SPEED_5:
		strcat(str_motor_speed_level, "6");
		break;

	case MOTOR_SPEED_6:
		strcat(str_motor_speed_level, "7");
		break;

	case MOTOR_SPEED_7:
		strcat(str_motor_speed_level, "8");
		break;

	default:
		break;
	}

	// Temperature
	unsigned char temp[5] = {0};
	temp[0] = (intg_fan_status.local_temperature / 1000)+0x30;
	temp[1] = ( (intg_fan_status.local_temperature % 1000) / 100 )+0x30;
	temp[2] = '.';
	temp[3] = ( (intg_fan_status.local_temperature % 100) / 10 )+0x30;
	temp[4] = ( (intg_fan_status.local_temperature % 10) )+0x30;
	strcat(str_temperature, temp);

	// Refresh 
    Init_buff();

	// Display fixed instructions about the buttons
    display("S1: on", 0, 90, TimesNewRoman, size8, 0, 0);
    display("S2: off", 80, 90, TimesNewRoman, size8, 0, 0);
    display("S3: mode", 0, 105, TimesNewRoman, size8, 0, 0);
    display("S4: speed", 80, 105, TimesNewRoman, size8, 0, 0);

	// Display changeable information
    display(str_fan_mode, 0, 0, TimesNewRoman, size8, 0, 0);
    display(str_motor_status, 0, 15,TimesNewRoman, size8, 0, 0);
    display(str_motor_speed_level, 0, 30, TimesNewRoman, size8, 0, 0);
    display(str_temperature, 0, 45, TimesNewRoman, size8, 0, 0);

	DIS_IMG(1);

}

void DisplayNixie(void)
{
	/**
	 * @brief 1st digit: decimal of PWM ratio, 2nd digit: hundredth of PWM ratio, 
	 *        3rd digit: per 10 miliampere, 4th digit: per 1 miliampere 
	 * 
	 */
	int nixie_digit;
	volatile int i;
	for ( nixie_digit = 0; nixie_digit < 4; nixie_digit++)
	{
		switch (nixie_digit)
		{
		case 0:
			for ( i = 0; i < 30; i++)
			{
				DisplayOneDigit(nixie_digit, (int)(kMotorPwmRatio[intg_fan_status.motor_speed_level]*100)/10);
			}
			
			break;
		
		case 1:
			for ( i = 0; i < 30; i++)
			{
				DisplayOneDigit(nixie_digit, (int)(kMotorPwmRatio[intg_fan_status.motor_speed_level]*100)%10);
			}
			break;

		case 2:
			for ( i = 0; i < 30; i++)
			{
				DisplayOneDigit(nixie_digit, intg_fan_status.motor_current/10);
			}
			break;

		case 3:
			for ( i = 0; i < 30; i++)
			{
				DisplayOneDigit(nixie_digit, intg_fan_status.motor_current%10);
			}
			break;

		default:
			break;
		}
	}
}
