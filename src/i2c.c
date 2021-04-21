#include <msp430.h>
#include "i2c.h"
uchar pdin_data=0;

/***************************************************************************
进行短暂的延时，原因是MSP430的速度比较快。使用者可以根据时钟频率自行调节延时长短
***************************************************************************/
void delay()
{
	uchar q0;
	for(q0=0;q0<50;q0++)
	{
		_NOP();
	}
}
/***************************************************************************
进行延时10MS，原因是MSP430的速度比较快。使用者可以根据时钟频率自行调节延时长短
***************************************************************************/
void DelayMs(uint ms)
{
	uint iq0, iq1;
	for (iq0 = ms; iq0 > 0; iq0--)
	for (iq1 = LOOPCNT; iq1 > 0; iq1--)
	;
}
/***************************************************************************
启动IIC总线
***************************************************************************/
void Start()
{
	SDA_OUT;
	S_SDA;
	delay();
	S_SCL;
	delay();
	C_SDA;
	delay();
	C_SCL;
	delay();
}
/***************************************************************************
停止操作，释放IIC总线
***************************************************************************/
void Stop()
{
	SDA_OUT;
	C_SCL;
	delay();
	C_SDA;
	delay();
	S_SCL;
	delay();
	S_SDA;
	delay();
}
/***************************************************************************
IIC总线应答
***************************************************************************/
void Ack()
{
	SDA_OUT;
	C_SDA;
	delay();
	S_SCL;
	delay();
	C_SCL;
	delay();
	S_SDA;
}
/***************************************************************************
IIC总线无应答
***************************************************************************/
void NoAck()
{
	SDA_OUT;
	S_SDA;
	delay();
	S_SCL;
	delay();
	C_SCL;
	delay();
}
/***************************************************************************
IIC总线检验应答
返回值：IIC应答位的值0：应答   1：无应答
***************************************************************************/
uchar TestAck()
{
	uchar ack;
	delay();
	SDA_IN;
	delay();
	S_SCL;
	delay();
	ack=READ_SDA;
	delay();
	C_SCL;
	delay();
        if(ack==0x00)
	return 0;
        else return 1;
}
/***************************************************************************
IIC总线写8位数据
input：要写的8位数据
***************************************************************************/
void Write8Bit(uchar input)
{
	uchar temp,q0;
	SDA_OUT;
	for(temp=8;temp!=0;temp--)
	{
		q0=input&0x80;
		if(q0==0x80)
			S_SDA;
		else
			C_SDA;
      delay();
		S_SCL;
		delay();
		C_SCL;
		delay();
		input=input<<1;
	}
}
/***************************************************************************
IIC总线读8位数据
返回值：读出的8位数据
***************************************************************************/
uchar Read8Bit()
{
	uchar temp,q0,rbyte=0;
	SDA_IN;
	for(temp=8;temp!=0;temp--)
	{
		S_SCL;
		delay();
		rbyte=rbyte<<1;
		SDA_IN;
		q0=READ_SDA;
		if(q0==IIC_SDA)
			rbyte=rbyte|0x1;
		delay();
		C_SCL;
		delay();
	}
	return(rbyte);
}

/***************************************************************************
初始化IIC
***************************************************************************/
void InitIIC()
{
	IIC_DIR |= IIC_SCL;  //SCL管脚为输出
	IIC_DIR |= IIC_SDA; //SDA管脚为输入
	C_SCL;
	Stop();
}
/***************************************************************************
写多个字节
psrc_data：指向要写入数据数组的指针
adr：要写入数据的首地址
nbyte：写入的字节数
返回值:  0：执行完毕；1：执行出现错误
***************************************************************************/
uchar W_I2C(uint device,uint adr,uchar data)
{

		Start();					//启动IIC总线
		Write8Bit(device);	//写TCA6416A的芯片地址以及确定下面执行写操作
		if(TestAck()==1)			//检验应答
		return 1;					//若应答错误，则退出函数，返回错误

		Write8Bit((uchar)adr);			//写对TCA6416A操作的地址
		if(TestAck()==1)			//检验应答
			return 1;				//若应答错误，则退出函数，返回错误

		Write8Bit(data);		//向TCA6416A中写数据
		if(TestAck()==1)
			return 1;

		Stop();						//停止IIC总线
		DelayMs(10);				//写入延时
	return 0;
}
/***************************************************************************
读一个字节
pdin_data：指向要保存读出数据的变量的指针
adr：要读出数据的地址
返回值:  0：执行完毕；1：执行出现错误
***************************************************************************/
uchar R_I2C(uint device,uint adr)
{
	pdin_data=0;
	Start();						//启动IIC总线
	Write8Bit(device-1);		//写TCA6416A的芯片地址以及确定下面执行写操作
	if(TestAck()==1)
		return 1;

	Write8Bit((uchar)(adr));			//写对TCA6416A操作的地址
	if(TestAck()==1)
		return 1;

	Start();						//再次启动IIC总线
	Write8Bit(device);		//写TCA6416A的芯片地址以及确定下面执行读操作
	if(TestAck()==1)
	        return 1;
	pdin_data=Read8Bit();			//从TCA6416A中读数据，存入pdin_data所指的存储器中

//	Ack();							//IIC应答操作

//	pdin_data=Read8Bit();			//从TCA6416A中读数据，存入pdin_data所指的存储器中

	Stop();							//停止IIC总线
        return pdin_data;
}

void Clockint()
{
	 UCSCTL6 &= ~XT1OFF; //启动XT1
	 P5SEL |= BIT2 + BIT3; //XT2引脚功能选择
	 UCSCTL6 &= ~XT2OFF;          //打开XT2
	 __bis_SR_register(SCG0);
	 UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
	 UCSCTL1 = DCORSEL_4;       //DCO频率范围在28.2MHZ以下
	 UCSCTL2 = FLLD_5 + 1;       //D=16，N=1
	 UCSCTL3 = SELREF_5 + FLLREFDIV_3;    //n=8,FLLREFCLK时钟源为XT2CLK；DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
	 UCSCTL4 = SELA_4 + SELS_3 +SELM_3;    //ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
	 UCSCTL5 = DIVA_5 +DIVS_1;      //ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
	             //最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
}

