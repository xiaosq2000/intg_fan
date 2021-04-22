#ifndef _INTG_FAN_H_
#define _INTG_FAN_H_

/* Includes  -------------------------------------------------- */ 

#include <msp430.h>
#include <string.h>
#include <stdlib.h>
#include "eink_fonts_imgs.h"
#include "nixie_driver.h"

/* Macros    -------------------------------------------------- */

#define TRUE 1
#define FALSE 0

#define EINK_REFRESH_TIME 1000  //microseconds
#define NIXIE_REFRESH_TIME 500 //microseconds
#define PWM_PEROID 2000         

#define POWER_OFF 0
#define POWER_ON 1

#define FAN_AUTO_MODE 0
#define FAN_MANUAL_MODE 1

#define MOTOR_TURN 0
#define MOTOR_REVERSE 1

#define MOTOR_SPEED_0 BIT0
#define MOTOR_SPEED_1 BIT1
#define MOTOR_SPEED_2 BIT2
#define MOTOR_SPEED_3 BIT3
#define MOTOR_SPEED_4 BIT4
#define MOTOR_SPEED_5 BIT5
#define MOTOR_SPEED_6 BIT6
#define MOTOR_SPEED_7 BIT7

/* External varibles    -------------------------------------------------- */

extern const double kMotorPwmRatio[]; 
extern const int kEinkRefreshTimeCounterMax;
extern const int kNixieRefreshTimeCounterMax;

/* Struct ------------------------------------------- */

struct IntgFanStatus
{

    int power;
    int fan_mode;
    int motor_mode;
    int motor_speed_level;
    unsigned int motor_current;
    unsigned int local_temperature; //  centigrade degree, multiplied by 100

}       intg_fan_status;

/* Function prototypes ----------------------------------------- */

void InitClock(void);
void InitGpio(void);
void InitAdc(void);
void InitTimerA(void);

void PowerOn(void);
void PowerOff(void);

void MeasureTemperature(void);
void MeasureMotorCurrent(void);

void MotorAutoControl(void);
void MotorManualControl(void);

void DisplayEinkScreen(void);
void DisplayNixie(void);

#endif

/*

    1    2    3    4    5    6    7    8
P1       1    1    1    1                     
P2       1    1    1    1    1    1          
P3       1    1                           
P4                                        
P5                                        
P6                                        
P7                                        
P8                                        

*/
