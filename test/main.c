/**
 *  ! Error log
 *  * isr_trap.asm
 *  ? long type not need for REFRESH_TIME/1000*(8000000/65535)
 *  * header files
 *  ? how to encode register macros
 *  TODO conflicts of GPIOs
 */ 

/**
 * @file main.c
 * @author 
 * @brief Intelligent Fan
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 *
 */

/* Includes  -------------------------------------------------- */ 

#include <msp430.h>
#include "eink_driver.h"
#include "nixie_driver.h"
#include "intg_fan.h"


/**
 * @brief The entry of the application
 */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    __enable_interrupt();

    eink_refresh_time_counter = 0;
    nixie_refresh_time_counter = 0;
    nixie_digit = 0;

    InitClock();
    InitGpio();
    // InitAdc();
    InitTimerA();

    // PaperIO_Int();
    // INIT_SSD1673();
    // Init_buff();

    InitNixieGpio();

	intg_fan_status.fan_mode = FAN_AUTO_MODE;
	intg_fan_status.motor_mode = MOTOR_PARK;
	intg_fan_status.motor_speed = MOTOR_LOW_SPEED;

    while (1)
    {
        // MeasureTemperature();
        // MeasureMotorCurrent();
        // MotorController();
    }
}

// #pragma vector = 
// __interrupt void PanelControl()
// {

// }

#pragma vector = TIMER1_A0_VECTOR
__interrupt void EinkDisplayRefresh()
{
    eink_refresh_time_counter ++;
    if (eink_refresh_time_counter > kEinkRefreshTimeCounterMax)
    {
        // DisplayEinkScreen();
        eink_refresh_time_counter = 0;
    }
}

#pragma vector = TIMER2_A0_VECTOR
__interrupt void NixieDisplayRefresh()
{
    nixie_refresh_time_counter ++;
    if (nixie_refresh_time_counter > kNixieRefreshTimeCounterMax)
    {
        DisplayOneDigit(nixie_digit,6);
        nixie_refresh_time_counter = 0;
    }

    nixie_digit ++;
    if (nixie_digit == 4)
    {
        nixie_digit = 0;
    }
}
