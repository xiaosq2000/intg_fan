#include <msp430.h>
#include "intg_fan.h"

// Eight fixed PWM ratio in manual mode 
const double kMotorPwmRatio[8] = {0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65};
// 0xFFFF and 0x0100 are consistent with the max value of Timer_As' main counter
const int kEinkRefreshTimeCounterMax = EINK_REFRESH_TIME/1000*(8000000/0xFFFF);
const int kNixieRefreshTimeCounterMax = NIXIE_REFRESH_TIME/1000*(8000000/0x0100);

volatile unsigned int eink_refresh_time_counter = 0;
volatile unsigned int nixie_refresh_time_counter = 0;
volatile int nixie_digit = 0;

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

}

void MeasureMotorCurrent(void)
{

}

void DisplayEinkScreen(void)
{

	char fan_mode[16] = "mode: "; 
	char motor_status[16] = "motor: ";
	char motor_speed[16] = "speed: "; 



	if (intg_fan_status.motor_mode == MOTOR_TURN)
	if (intg_fan_status.fan_mode == FAN_AUTO_MODE)
	{
		strcat(fan_mode, "auto");
	}
	if (intg_fan_status.fan_mode == FAN_MANUAL_MODE)
	{
		strcat(fan_mode, "manual");
	}




	if (intg_fan_status.motor_mode == MOTOR_TURN)
	// if (intg_fan_status.motor_mode == MOTOR_PARK)
	// {
	// 	strcat(motor_status, "park");
	// }
	{
		strcat(motor_status, "turn");
	}
	if (intg_fan_status.motor_mode == MOTOR_REVERSE)
	{
		strcat(motor_status, "reverse");
	}



	if (intg_fan_status.motor_speed == MOTOR_SPEED_0)
	{
		strcat(motor_speed, "1");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_1)
	{
		strcat(motor_speed, "2");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_2)
	{
		strcat(motor_speed, "3");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_3)
	{
		strcat(motor_speed, "4");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_4)
	{
		strcat(motor_speed, "5");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_5)
	{
		strcat(motor_speed, "6");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_6)
	{
		strcat(motor_speed, "7");
	}
	if (intg_fan_status.motor_speed == MOTOR_SPEED_7)
	{
		strcat(motor_speed, "8");
	}

    // MYRESET();
    display(fan_mode, 0, 0, TimesNewRoman, size8, 0, 0);
    display(motor_status, 0, 15,TimesNewRoman, size8, 0, 0);
    display(motor_speed, 0, 30, TimesNewRoman, size8, 0, 0);

    display("S1: on", 0, 90, TimesNewRoman, size8, 0, 0);
    display("S2: off", 80, 90, TimesNewRoman, size8, 0, 0);
    display("S3: mode", 0, 105, TimesNewRoman, size8, 0, 0);
    display("S4: speed", 80, 105, TimesNewRoman, size8, 0, 0);

	DIS_IMG(1);

}

void DisplayNixie(void)
{
	for ( nixie_digit = 0; nixie_digit < 4; nixie_digit++)
	{
		DisplayOneDigit(nixie_digit,6);
	}
}
