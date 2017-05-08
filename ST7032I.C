/**********************************/
//Project :
//Dots : 1602
//Driver_IC :ST7032I
//Panel_Model : STN
//Writer :unkwon
//Date :2017.5.8
/********************************/

#include <reg51.h>
#include <intrins.h>

#define unchar unsigned char
#define unint unsigned int
#define nops () {_nop_();_nop_();_nop_();_nop_();_nop_();}

sbit RES = P3^2;
sbit SDA = P1^7;
sbit SCL = P1^6;

sbit AOUTOB = P2^1;
sbit STEP = P2^0;

void Inter_code ();
void Delay_ms (unint tt);
void Test (dat);
void Pause ();
void stop ();
void start ();
void Write_byte (unchar dat);
void Write_Command (unchar dat);
void Write_Data (unchar dat);
void WriteCgram (unchar *p);
void displaychar (unchar *P);
//bit Ack ();

unsigned char code test[] = 
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x1f,
}
















