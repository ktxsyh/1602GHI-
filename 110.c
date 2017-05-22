/***************************/
//Project:
//Dots;1602
//Driver_IC:ST7032I
//Panel_Mode:STN
//Writer:JWan
//VDD:5.0V
//Vop:5.0V/4.5V(0x78;0x5d;0x6a) 3.0V/4.45V(0x7f;0x5f;0x6a) 3.0V/5.04V(0x70;0x5f;0x6c)
//Date:2011.4.22
/**************************/
#include<reg51.H>
#include<intrins.H>
#define unchar unsigned char
#define unint unsigned int
#define nops() {_nop_();_nop_();_nop_();_nop_();_nop_();} //5us delay_time

sbit RES = P3^2; //RST EQU P3.0
sbit SDA = P1^7;
sbit SCL = P1^6;
sbit AOUTOB = P2^1; //S_S EQU P2.1 pause the display when it is '0'
sbit STEP = P2^0; //STP EQU P2.0

void Inter_code();
void Delay_ms(unint tt);
void Test(dat);
void Pause();
void stop();
void start();
void Write_byte(unchar dat);
void Write_Command(unchar dat);
void Write_Data(unchar dat);
void WriteCgram(unchar *p);
void displaychar(unsigned char *P);
//bit Ack();

unsigned char code test[]=
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,
0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x1f,
};
unsigned char code pic0[]=
{
0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,
0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
0x59,0x5a,0xe5,0x24,0x5c,0x5e,0x5f,0x5e,
};
unsigned char code pic1[]=
{
0x49,0x20,0x4c,0x6f,0x76,0x65,0x20,0x59, //I Love Y
0x6f,0x75,0x20,0x4d,0x6f,0x72,0x65,0x20, //ou More
0x54,0x68,0x61,0x6e,0x20,0x49,0x20,0x43, //Than I C
0x61,0x6e,0x20,0x53,0x61,0x79,0x20,0x21, //an Say !
};
unsigned char code pic2[]=
{
0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
};

main()
{
	RES = 1;
	Delay_ms(10);
	RES = 0; //复位，低有效
	Delay_ms(50);
	RES = 1;
	Delay_ms(100);
	Inter_code();
	WriteCgram(test);
	while(1)
	{
	Test(0);
	Delay_ms(1000);
	Pause();
	
	Test(1);
	Delay_ms(1000);
	Pause();
	
	Test(2);
	Delay_ms(1000);
	Pause();
	Test(3);
	
	Delay_ms(1000);
	Pause();
	Test(4);
	
	Delay_ms(1000);
	Pause();
	Test(5);
	
	Delay_ms(1000);
	Pause();
	displaychar(pic0);
	Delay_ms(1000);
	Pause();
	//displaychar(pic1);
	//Delay_ms(1000);
	//Pause();
	displaychar(pic2);
	Delay_ms(1000);
	Pause();
}
}

/******************Delay_ms********************/
void Delay_ms(unint tt)
{
	unchar TT;
	while(--tt)
	for(TT=0;TT<100;TT++)
		;
}

/***********Aouto and Step********************/
void Pause()
{
	while(AOUTOB==1&STEP==0)
	{}
	if(STEP==1)
	{
	Delay_ms(10);
	while(AOUTOB==0)
	{}
	}
	else if  (AOUTOB==1)
	{
	Delay_ms(10);
	}
}

/**************START****************/
void start()
{
	SDA=1;
	nops();
	SCL=1;
	nops();
	SDA=0;
	nops();
	SCL=0;
	nops();
}

/***************END*****************/
void stop()
{
	SCL=0;
	nops();
	SDA=0;
	nops();
	SCL=1;
	nops();
	SDA=1;
	nops();
}

/************Write_byte*****************/
void Write_byte(unchar dat)
{
	unchar i;
	for(i=0;i<8;i++)
	{
	 nops();
	 SCL=0;
	 if((dat<<i)&0x80)
	 SDA=1;
	 else
	 SDA=0;
	 _nop_();
	 SCL=1;
	 nops();
	 SCL=0;
	}
	SDA=1;
	nops();
	SCL=1;
	nops();
	while(1==SDA)
	{
	 nops();
	}
	 SCL=0;
	 nops();
}

/***********MCU REV Ack*******************/
/*
bit Ack()
{
	bit flag;
	SDA=1;
	nops();
	SCL=1;
	nops();
	flag=SDA;
	SCL=0;
	nops();
	return flag;
}
*/

/***********Write_Command***************/
void Write_Command(unchar dat)
{
	Write_byte(0x80);
	Write_byte(dat);
}

/***********Write_Data******************/
void Write_Data(unchar dat1)
{
	Write_byte(dat1);
}

/**************Write_Cgram**************/
void WriteCgram(unchar *p)
{
	unchar i;
	start();
	Write_byte(0x7c);
	Write_Command(0x20);
	Write_Command(0x40);
	Write_byte(0x40);
	for(i=0;i<48;i++)
	{
	Write_Data(*p++);
	}
	stop();
}

/*************Test**********************/
void Test(dat)
{
	unint i,j;
	start();
	Write_byte(0x7c);
	Write_Command(0x39);
	Write_Command(0x80);
	Write_byte(0x40);
	for(i=0;i<16;i++)
	{
	Write_Data(dat);
	}
	stop();
	start();
	Write_byte(0x7c);
	Write_Command(0x39);
	Write_Command(0xc0);
	Write_byte(0x40);
	for(j=0;j<16;j++)
	{
	 Write_Data(dat);
	}
	stop();
}

/*************displaychar******************/
void displaychar(unsigned char *p)
{
	unint i,j;
	start();
	Write_byte(0x7c);
	Write_Command(0x38);
	Write_Command(0x80);
	Write_byte(0x40);
	for(i=0;i<16;i++)
	{
  	 Write_Data(*p++);
	}
	stop();
	start();
	Write_byte(0x7c);
	Write_Command(0x38);
	Write_Command(0xc0);
	Write_byte(0x40);
	for(j=0;j<16;j++)
	{
	  Write_Data(*p++);
	}
	stop();
	Delay_ms(100);
}

/****************Inter_code*******************/
void Inter_code()
{
	start();
	Write_byte(0x7c); //Slave address
	Write_Command(0x38); //set function D=1 DH=0 IS=0
	Write_Command(0x39); //set function D=1 DH=0 IS=1
	Write_Command(0x14); //set BAIS=1/5 OSC
	Write_Command(0x78); //set voltage follower	
	Write_Command(0x5d); //set Icon=0 Bon=1
	Write_Command(0x6a); //set Fon=1 Ra/Rb=2.0
	Write_Command(0x0c); //set D=1 C=0 B=0 Display on
	//Write_Command(0x01); //clear
	//Write_Command(0x06); //set enter mode
	stop();
}