#include <msp430.h>
#include "intg_fan.h"

const int kEinkRefreshTimeCounterMax = EINK_REFRESH_TIME/1000*(8000000/0xFFFF);
const int kNixieRefreshTimeCounterMax = NIXIE_REFRESH_TIME/1000*(8000000/0x0100);
volatile unsigned int eink_refresh_time_counter = 0;
volatile unsigned int nixie_refresh_time_counter = 0;
volatile int nixie_digit = 0;

void InitClock(void)
{
	UCSCTL6 &= ~XT1OFF;          //鍚姩XT1
	P5SEL |= BIT2 + BIT3;        //XT2寮曡剼鍔熻兘閫夋嫨
	UCSCTL6 &= ~XT2OFF;          //鎵撳紑XT2

	//璁剧疆绯荤粺鏃堕挓鐢熸垚鍣�1,FLL control loop鍏抽棴SCG0=1,鍏抽棴閿侀鐜紝鐢ㄦ埛鑷畾涔塙CSCTL0~1宸ヤ綔妯″紡
	__bis_SR_register(SCG0);

	//鎵嬪姩閫夋嫨DCO棰戠巼闃舵锛�8绉嶉樁姊級锛岀‘瀹欴CO棰戠巼澶ц嚧鑼冨洿銆�
	UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
	//DCO棰戠巼鑼冨洿鍦�28.2MHz浠ヤ笅锛孌CO棰戠巼鑼冨洿閫夋嫨锛堜笁涓猙it浣嶏紝鏀瑰彉鐩存祦鍙戠敓鍣ㄧ數鍘嬶紝杩涜�屾敼鍙楧CO杈撳嚭棰戠巼锛�
	UCSCTL1 = DCORSEL_4;
	//fDCOCLK/32锛岄攣棰戠幆鍒嗛鍣�
	UCSCTL2 = FLLD_5;

	//n=8,FLLREFCLK鏃堕挓婧愪负XT2CLK
	//DCOCLK=D*(N+1)*(FLLREFCLK/n)
	//DCOCLKDIV=(N+1)*(FLLREFCLK/n)
	UCSCTL3 = SELREF_5 + FLLREFDIV_3;
	//ACLK鐨勬椂閽熸簮涓篋COCLKDIV,MCLK\SMCLK鐨勬椂閽熸簮涓篋COCLK
	UCSCTL4 = SELA_4 + SELS_3 +SELM_3;
	//ACLK鐢盌COCLKDIV鐨�32鍒嗛寰楀埌锛孲MCLK鐢盌COCLK鐨�2鍒嗛寰楀埌
	UCSCTL5 = DIVA_5 +DIVS_1;
}

void InitGpio(void)
{
	P8DIR |= BIT1;
    P8OUT &=~ BIT1;
}

// void InitAdc(void)
// {

// }

void InitTimerA(void)
{
	// // Timer_A0 Control Register
	// TA0CTL |= TASSEL_2;// Timer_A0 clock source select: SMCLK 8MHz
	// TA0CTL |= MC_1;// Mode control: up mode
	// TA0CTL |= TACLR;// Timer_A0 clear
	// // Timer_A0 Capture/Compare Control 4 Register
	// TA0CCTL4 = OUTMOD_7;// Reset/set mode
    // // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// TA0CCR0 = ;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.

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
	TA2CCR0 = 0x0100;// TAxCCRn holds the data for the comparison to the timer in the Timer_A Register, TAR.
}

// void MeasureTemperature(void)
// {

// }

// void MeasureMotorCurrent(void)
// {

// }

void DisplayEinkScreen(void)
{

	char fan_mode[16] = "mode: "; 
	char motor_status[16] = "motor: ";
	char motor_speed[16] = "speed: "; 

	if (intg_fan_status.fan_mode == FAN_AUTO_MODE)
	{
		strcat(fan_mode, "auto");
	}
	if (intg_fan_status.fan_mode == FAN_MANUAL_MODE)
	{
		strcat(fan_mode, "manual");
	}
	if (intg_fan_status.motor_mode == MOTOR_PARK)
	{
		strcat(motor_status, "park");
	}
	if (intg_fan_status.motor_mode == MOTOR_TURN)
	{
		strcat(motor_status, "turn");
	}
	if (intg_fan_status.motor_mode == MOTOR_REVERSE)
	{
		strcat(motor_status, "reverse");
	}
	if (intg_fan_status.motor_speed == MOTOR_LOW_SPEED)
	{
		strcat(motor_speed, "low");
	}
	if (intg_fan_status.motor_speed == MOTOR_NORMAL_SPEED)
	{
		strcat(motor_speed, "normal");
	}
	if (intg_fan_status.motor_speed == MOTOR_HIGH_SPEED)
	{
		strcat(motor_speed, "high");
	}

    MYRESET();
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
	// DisplayOneDigit(0,0);
	// DisplayOneDigit(1,1);
	// DisplayOneDigit(2,2);
	// DisplayOneDigit(3,3);
}

// void MotorController(void)
// {

// }
