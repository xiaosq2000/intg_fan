#ifndef _INTG_FAN_H_
#define _INTG_FAN_H_

/* Includes  -------------------------------------------------- */ 

#include <msp430.h>
#include <string.h>
#include <stdlib.h>
#include "eink_fonts_imgs.h"
#include "nixie_driver.h"

/* Macros    -------------------------------------------------- */

#define EINK_REFRESH_TIME 1000 //microseconds
#define NIXIE_REFRESH_TIME 100 //microseconds

#define FAN_AUTO_MODE 0
#define FAN_MANUAL_MODE 1

#define MOTOR_PARK 0
#define MOTOR_TURN 1
#define MOTOR_REVERSE 2

#define MOTOR_LOW_SPEED 0
#define MOTOR_NORMAL_SPEED 1
#define MOTOR_HIGH_SPEED 2

/* External varibles    -------------------------------------------------- */

extern const int kEinkRefreshTimeCounterMax;
extern volatile unsigned int eink_refresh_time_counter;
extern const int kNixieRefreshTimeCounterMax;
extern volatile unsigned int nixie_refresh_time_counter;
extern volatile int nixie_digit;
/* Struct ------------------------------------------- */

struct IntgFanStatus
{
    int fan_mode;
    int motor_current;
    int temperature;
    int motor_mode;
    int motor_speed;
} intg_fan_status;

/* Function prototypes ----------------------------------------- */

void InitClock(void);
void InitGpio(void);
//void InitAdc(void);
void InitTimerA(void);

//void MeasureTemperature(void);
//void MeasureMotorCurrent(void);

void DisplayEinkScreen(void);
void DisplayNixie(void);

//void MotorController(void);
//void PanelController(void);

#endif
