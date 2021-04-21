#include <msp430.h>
#include "type.h"
#ifndef _I2C_H_
#define _I2C_H_

#define IIC_DIR P3DIR
#define IIC_OUT P3OUT
#define IIC_IN  P3IN

#define IIC_SCL BIT1 					//SCL定义
#define IIC_SDA BIT0						//SDA定义

#define S_SDA	IIC_OUT |= IIC_SDA	//SDA置位
#define S_SCL 	IIC_OUT |= IIC_SCL	//SCL置位
#define C_SDA	IIC_OUT &= ~IIC_SDA	//SDA复位
#define C_SCL  IIC_OUT &= ~IIC_SCL	//SCL复位

#define SDA_IN   IIC_DIR &= ~IIC_SDA  //设置SDA为输入
#define SDA_OUT  IIC_DIR |= IIC_SDA	  //设置SDA为输出

#define READ_SDA  (IIC_IN&IIC_SDA)	  //读SDA电平

#define FREQUENCY	4000
#define LOOPBODY	8
#define LOOPCNT	(unsigned int)((FREQUENCY/LOOPBODY))

void InitIIC();
uchar W_I2C(uint device,uint adr,uchar data);
uchar R_I2C(uint device,uint adr);
void Clockint();
void DelayMs(uint ms);

#endif
