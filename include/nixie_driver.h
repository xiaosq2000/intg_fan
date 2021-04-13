/*
    |      |  DP  |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  (DEX)  |
    | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |  :--:   |
    |  0   |  0   |  1   |  1   |  1   |  1   |  1   |  1   |  0   |  0x7E   |
    |  1   |  0   |  0   |  1   |  1   |  0   |  0   |  0   |  0   |  0x30   |
    |  2   |  0   |  1   |  1   |  0   |  1   |  1   |  0   |  1   |  0x6D   |
    |  3   |  0   |  1   |  1   |  1   |  1   |  0   |  0   |  1   |  0x79   |
    |  4   |  0   |  0   |  1   |  1   |  0   |  0   |  1   |  1   |  0x33   |
    |  5   |  0   |  1   |  0   |  1   |  1   |  0   |  1   |  1   |  0x5D   |
    |  6   |  0   |  1   |  0   |  1   |  1   |  1   |  1   |  1   |  0x5F   |
    |  7   |  0   |  1   |  1   |  1   |  0   |  0   |  0   |  0   |  0x70   |
    |  8   |  0   |  1   |  1   |  1   |  1   |  1   |  1   |  1   |  0x7F   |
    |  9   |  0   |  1   |  1   |  1   |  1   |  0   |  1   |  1   |  0x7B   |
*/

#ifndef _NIXIE_DRIVER_H_
#define _NIXIE_DRIVER_H_

#include <msp430.h>

#define NIXIE_ENABLE_PORT_OUT_0  P1OUT
#define NIXIE_ENABLE_PORT_OUT_1  P2OUT
#define NIXIE_ENABLE_PORT_OUT_2  P1OUT
#define NIXIE_ENABLE_PORT_OUT_3  P7OUT

#define NIXIE_ENABLE_PORT_DIR_0  P1DIR
#define NIXIE_ENABLE_PORT_DIR_1  P2DIR
#define NIXIE_ENABLE_PORT_DIR_2  P1DIR
#define NIXIE_ENABLE_PORT_DIR_3  P7DIR

#define NIXIE_ENABLE_CHANNEL_0 BIT5
#define NIXIE_ENABLE_CHANNEL_1 BIT2
#define NIXIE_ENABLE_CHANNEL_2 BIT4
#define NIXIE_ENABLE_CHANNEL_3 BIT4

#define NIXIE_CTRL_PORT_DIR_0 P3DIR // dot
#define NIXIE_CTRL_PORT_DIR_1 P4DIR // A
#define NIXIE_CTRL_PORT_DIR_2 P3DIR // B
#define NIXIE_CTRL_PORT_DIR_3 P4DIR // C
#define NIXIE_CTRL_PORT_DIR_4 P2DIR // D
#define NIXIE_CTRL_PORT_DIR_5 P3DIR // E
#define NIXIE_CTRL_PORT_DIR_6 P2DIR // F
#define NIXIE_CTRL_PORT_DIR_7 P8DIR // G

#define NIXIE_CTRL_PORT_OUT_0 P3OUT
#define NIXIE_CTRL_PORT_OUT_1 P4OUT
#define NIXIE_CTRL_PORT_OUT_2 P3OUT
#define NIXIE_CTRL_PORT_OUT_3 P4OUT
#define NIXIE_CTRL_PORT_OUT_4 P2OUT
#define NIXIE_CTRL_PORT_OUT_5 P3OUT
#define NIXIE_CTRL_PORT_OUT_6 P2OUT
#define NIXIE_CTRL_PORT_OUT_7 P8OUT

#define NIXIE_CTRL_CHANNEL_0 BIT5
#define NIXIE_CTRL_CHANNEL_1 BIT3
#define NIXIE_CTRL_CHANNEL_2 BIT1
#define NIXIE_CTRL_CHANNEL_3 BIT0
#define NIXIE_CTRL_CHANNEL_4 BIT6
#define NIXIE_CTRL_CHANNEL_5 BIT7
#define NIXIE_CTRL_CHANNEL_6 BIT3
#define NIXIE_CTRL_CHANNEL_7 BIT2
// #define NIXIE_CTRL_CHANNEL_7 BIT1

void InitNixieGpio(void);
void ClearNixie(void);
void DisplayOneDigit(int, int);

#endif