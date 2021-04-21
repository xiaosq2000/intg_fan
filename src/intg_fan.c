#include <msp430.h>
#include "intg_fan.h"

const double kMotorPwmRatio[8] = {0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65};

const int kEinkRefreshTimeCounterMax = EINK_REFRESH_TIME/1000*(8000000/0xFFFF);
const int kNixieRefreshTimeCounterMax = NIXIE_REFRESH_TIME/1000*(8000000/0x1000);

volatile unsigned int eink_refresh_time_counter = 0;
volatile unsigned int nixie_refresh_time_counter = 0;
volatile int nixie_digit = 0;

unsigned char temperature_integral_part=0;
unsigned char temperature_decimal_part=0;

void InitClock(void)
{
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

void InitGpio(void)
{
	// H-bridge drive circuit 
    P1DIR |= BIT5; // NSLEEP
    P1SEL |= BIT5;
    P2DIR |= BIT4; // IN1
    P2DIR |= BIT5; // IN2

    // Button S1
    P1DIR &= ~BIT2;
    P1REN |= BIT2;
    P1IES &= ~BIT2;
    P1IFG &= ~BIT2;
    P1IE |= BIT2;
    // Button S2
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1IES &= ~BIT3;
    P1IFG &= ~BIT3;
    P1IE |= BIT3;
    // Button S3
    P2DIR &= ~BIT3;
    P2REN |= BIT3;
    P2IES &= ~BIT3;
    P2IFG &= ~BIT3;
    P2IE |= BIT3;
    // Button S4
    P2REN |= BIT6;
    P2OUT |= BIT6;
    P2IES &= ~BIT6;
    P2IFG &= ~BIT6;
    P2IE |= BIT6;

}

void InitAdc(void)
{

}

void InitTimerA(void)
{

	// Timer_A0 Control Register
	TA0CTL |= TASSEL_2;// Timer_A0 clock source select: SMCLK 8MHz
	TA0CTL |= MC_1;// Mode control: up mode
	TA0CTL |= TACLR;// Timer_A0 clear
	// Timer_A0 Capture/Compare Control 4 Register
	TA0CCTL4 = OUTMOD_7;// Reset/set mode
	TA0CCR0 = PWM_PEROID;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.
	// pwm_ratio = TA0CCR4 / TA0CCR0

	// Timer_A1 Control Register
	TA1CTL |= TASSEL_2;// Timer_A1 clock source select: SMCLK 8MHz
	TA1CTL |= MC_1;// Mode control: up mode
	TA1CTL |= TACLR;// Timer_A1 clear
	TA1CCTL0 = CCIE;// enable capture/compare interrupt
	TA1CCR0 = 0xFFFF;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.

	// Timer_A2 Control Register
	TA2CTL |= TASSEL_2;// Timer_A2 clock source select: SMCLK 8MHz
	TA2CTL |= MC_1;// Mode control: up mode
	TA2CTL |= TACLR;// Timer_A2 clear
	TA2CCTL0 = CCIE;// enable capture/compare interrupt
	TA2CCR0 = 0x1000;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.

}

void MotorAutoControl()
{

}
void MotorManualControl()
{

	switch (intg_fan_status.motor_speed)
	{
	case MOTOR_SPEED_0:
		TA0CCR4 = kMotorPwmRatio[0] * PWM_PEROID;
		break;
	case MOTOR_SPEED_1:
		TA0CCR4 = kMotorPwmRatio[1] * PWM_PEROID;
		break;
	case MOTOR_SPEED_2:
		TA0CCR4 = kMotorPwmRatio[2] * PWM_PEROID;
		break;
	case MOTOR_SPEED_3:
		TA0CCR4 = kMotorPwmRatio[3] * PWM_PEROID;
		break;
	case MOTOR_SPEED_4:
		TA0CCR4 = kMotorPwmRatio[4] * PWM_PEROID;
		break;
	case MOTOR_SPEED_5:
		TA0CCR4 = kMotorPwmRatio[5] * PWM_PEROID;
		break;
	case MOTOR_SPEED_6:
		TA0CCR4 = kMotorPwmRatio[6] * PWM_PEROID;
		break;
	case MOTOR_SPEED_7:
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
    temperature_integral_part = R_I2C(0x55,0x00) - 64;
    temperature_decimal_part = ( (R_I2C(0x55,0x10) >> 4) * 625 ) / 100;
}

void MeasureMotorCurrent(void)
{

}

void DisplayEinkScreen(void)
{

	char fan_mode[16] = "mode: "; 
	char motor_status[16] = "motor: ";
	char motor_speed[16] = "speed: "; 
	char temperature[16] = "temp: ";

	// Fan mode
	switch (intg_fan_status.fan_mode)
	{
	case FAN_AUTO_MODE:
		strcat(fan_mode, "auto");
		break;
	
	case FAN_MANUAL_MODE:
		strcat(fan_mode, "manual");
		break;

	default:
		break;
	}

	// Motor mode
	switch (intg_fan_status.motor_mode)
	{
	case MOTOR_TURN:
		strcat(motor_status, "turn");
		break;
	
	case MOTOR_REVERSE:
		strcat(motor_status, "reverse");
		break;

	default:
		break;
	}

	// Fan status
	switch (intg_fan_status.motor_speed)
	{
	case MOTOR_SPEED_0:
		strcat(motor_speed, "1");
		break;

	case MOTOR_SPEED_1:
		strcat(motor_speed, "2");
		break;

	case MOTOR_SPEED_2:
		strcat(motor_speed, "3");
		break;

	case MOTOR_SPEED_3:
		strcat(motor_speed, "4");
		break;

	case MOTOR_SPEED_4:
		strcat(motor_speed, "5");
		break;

	case MOTOR_SPEED_5:
		strcat(motor_speed, "6");
		break;

	case MOTOR_SPEED_6:
		strcat(motor_speed, "7");
		break;

	case MOTOR_SPEED_7:
		strcat(motor_speed, "8");
		break;

	default:
		break;
	}

	// Temperature
	unsigned char temperature_decade = (temperature_integral_part/10);
	unsigned char temperature_unit = (temperature_integral_part%10);
	unsigned char temperature_tenth = (temperature_decimal_part/10);
	unsigned char temperature_hundredth = (temperature_decimal_part%10);

	strcat(temperature, &(&temperature_decade));
	strcat(temperature, &(&temperature_unit));
	strcat(temperature, ".");
	strcat(temperature, &(&temperature_tenth));
	strcat(temperature, &(&temperature_hundredth));

	// Refresh 
    Init_buff();

	// Display fixed instructions about the buttons
    display("S1: on", 0, 90, TimesNewRoman, size8, 0, 0);
    display("S2: off", 80, 90, TimesNewRoman, size8, 0, 0);
    display("S3: mode", 0, 105, TimesNewRoman, size8, 0, 0);
    display("S4: speed", 80, 105, TimesNewRoman, size8, 0, 0);

	// Display changeable information
    display(fan_mode, 0, 0, TimesNewRoman, size8, 0, 0);
    display(motor_status, 0, 15,TimesNewRoman, size8, 0, 0);
    display(motor_speed, 0, 30, TimesNewRoman, size8, 0, 0);
    display(temperature, 0, 45, TimesNewRoman, size8, 0, 0);

	DIS_IMG(1);

}

void DisplayNixie(void)
{
	for ( nixie_digit = 0; nixie_digit < 4; nixie_digit++)
	{
		DisplayOneDigit(nixie_digit,6);
	}
}
