/**
 * @file main.c
 * @author 
 * @brief Intelligent Fan
 * @version 0.2
 * @date 2021-04-18
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
    __enable_interrupt();       // Enable global interruption

    // Initialize basic on-board components
    InitClock();
    InitGpio();
    InitTimerA();
    // InitAdc();

    // Initialize E-ink Screen
    PaperIO_Int();
    INIT_SSD1673();
    Init_buff();

    // Initialize LED nixie tube
    InitNixieGpio();

    // Initialize counters
    eink_refresh_time_counter = 0;
    nixie_refresh_time_counter = 0;
    nixie_digit = 0;

    // Initialize the status of the fan
    intg_fan_status.power = POWER_OFF;
	intg_fan_status.fan_mode = FAN_AUTO_MODE;
	intg_fan_status.motor_mode = MOTOR_TURN;
	intg_fan_status.motor_speed = MOTOR_SPEED_0;
    intg_fan_status.temperature = 0;
    intg_fan_status.motor_current = 0;

    while (TRUE)
    {

        MotorManualControl();
        
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void SwitchPower(void)
{

    if ( ( P1IFG & BIT2 ) == 0 ? FALSE : TRUE) 
    {
        intg_fan_status.power = POWER_ON;
        P1IFG &= ~BIT2;
    }

    if ( ( P1IFG & BIT3 ) == 0 ? FALSE : TRUE) 
    {
        intg_fan_status.power = POWER_OFF;
        P1IFG &= ~BIT3;
    }

}

#pragma vector = PORT2_VECTOR
__interrupt void SwitchModeAndSpeed(void)
{

    if ( ( P2IFG & BIT3 ) == 0 ? FALSE : TRUE) 
    {
        intg_fan_status.fan_mode = ! intg_fan_status.fan_mode;
        P2IFG &= ~BIT3;
    }

    if ( ( P2IFG & BIT6 ) == 0 ? FALSE : TRUE) 
    {
        intg_fan_status.motor_speed <<= 0x01; 
        if (intg_fan_status.motor_speed == MOTOR_SPEED_7)
        {
            intg_fan_status.motor_speed = MOTOR_SPEED_0;
        }
        P2IFG &= ~BIT6;
    }

}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void EinkDisplayRefresh()
{

    eink_refresh_time_counter ++;
    if (eink_refresh_time_counter > kEinkRefreshTimeCounterMax)
    {
        DisplayEinkScreen();
        eink_refresh_time_counter = 0;
    }

}

#pragma vector = TIMER2_A0_VECTOR
__interrupt void NixieDisplayRefresh()
{

    // nixie_refresh_time_counter ++;
    // if (nixie_refresh_time_counter > kNixieRefreshTimeCounterMax)
    // {
    //     DisplayNixie();
    //     nixie_refresh_time_counter = 0;
    // }

    nixie_refresh_time_counter ++;
    if (nixie_refresh_time_counter > kNixieRefreshTimeCounterMax)
    {
        DisplayNixie();
        ClearNixie();
    }


}
