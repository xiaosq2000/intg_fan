#include "tmp421.h"
#include "i2c.h"

void InitTmp(void)
{
	W_I2C(0x54,0x9,0x4);
	W_I2C(0x54,0x21,0x3);
	W_I2C(0x54,0x0b,0x07);
}
