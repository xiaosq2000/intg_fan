/**
 * @file main.c
 * @author 
 * @brief Intelligent Fan
 * @version 0.4
 * @date 2021-04-24
 * 
 */

/**
 * todo 1. Auto control mode & control strategy
 * todo 2. Soft On/Off
 * todo 3. Use timer to control nixie
 * ? Current value too small
 * ? temp string on Eink screen
 */

/* Includes  -------------------------------------------------- */ 

#include <msp430.h>
#include "eink_driver.h"
#include "nixie_driver.h"
#include "i2c.h"
#include "tmp421.h"
#include "intg_fan.h"

/**
 * @brief The entry of the application
 */

void main(void)
{

    /**
     * @brief Initialize MSP430 system 
     * 
     */

    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    __enable_interrupt();               // Enable global interruption
    InitClock();                        // Configure system clock

    /**
     * @brief Initialize HCI
     * 
     */

    InitHCI();

    /**
     * @brief Initialize motor
     * 
     */

    InitMotorPwm();                     // Timer_A0 configuration
    InitMotorDriver();
    InitCurrentSensor();

    /**
     * @brief Initialize E-ink Screen
     * 
     */

    PaperIO_Int();                      // Hardware configuration
    INIT_SSD1673();                     // Hardware configuration
    Init_buff();                        // Clear 
    InitEinkRefreshCounter();           // Timer_A1 configuration

    /**
     * @brief Initialize LED nixie tube 
     * 
     */

    InitNixieGpio();            
    
    /**
     * @brief Initialize temperature sensor TMP421
     * 
     */

    InitIIC();
    InitTmp();

    /**
     * @brief Initialize the status of the fan
     * 
     */

    intg_fan_status.power = POWER_ON;
	intg_fan_status.fan_mode = FAN_MANUAL_MODE;
	intg_fan_status.motor_mode = MOTOR_TURN;
	intg_fan_status.motor_speed_level = 1;
    intg_fan_status.local_temperature = 0;
    intg_fan_status.motor_current = 0;

    while (TRUE)
    {
        
        MeasureTemperature();
        MeasureMotorCurrent();

        DisplayNixie();

        if (intg_fan_status.power == POWER_ON)
        { 
            if (intg_fan_status.fan_mode == FAN_AUTO_MODE)
            {
                MotorAutoControl();
            }
            if (intg_fan_status.fan_mode == FAN_MANUAL_MODE)
            {
                MotorManualControl();
            }
        }
        if (intg_fan_status.power == POWER_OFF)
        {
            ;
        }
         
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void ISR_SwitchPower(void)
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
__interrupt void ISR_SwitchModeAndSpeed(void)
{

    if ( ( P2IFG & BIT3 ) == 0 ? FALSE : TRUE) 
    {
        intg_fan_status.fan_mode = !intg_fan_status.fan_mode;
        P2IFG &= ~BIT3;
    }

    if ( ( P2IFG & BIT6 ) == 0 ? FALSE : TRUE) 
    {
        if (intg_fan_status.motor_speed_level == MOTOR_SPEED_7)
        {
            intg_fan_status.motor_speed_level = MOTOR_SPEED_0;
        }
        else 
        {
            intg_fan_status.motor_speed_level ++; 
        }
        P2IFG &= ~BIT6;
    }

}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void ISR_EinkDisplayRefresh()
{

    eink_refresh_time_counter ++;
    if (eink_refresh_time_counter > kEinkRefreshTimeCounterMax)
    {
        ClearNixie();
        DisplayEinkScreen();
        eink_refresh_time_counter = 0;
    }

}

// #pragma vector = TIMER2_A0_VECTOR
// __interrupt void ISR_NixieDisplayRefresh()
// {

//     nixie_refresh_time_counter ++;
//     if (nixie_refresh_time_counter > kNixieRefreshTimeCounterMax)
//     {
//         DisplayNixie();
//         nixie_refresh_time_counter = 0;
//     }

// }
