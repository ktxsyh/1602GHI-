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
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,
0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x1f,
};

unsigned char code pic1 [] =
{
0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,
0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
0x59,0x5a,0xe5,0x24,0x5c,0x5e,0x5f,0x5e,
};

void main ()
{
  
   RES = 1;
   Delay_ms (10);
   RES = 0;
   Delay_ms (50);
   RES = 1;
   Delay_ms (100);
      
       Inter_code ();
       WriteCgram (test);
       while (1)
       {
       
         Test (0);
         Delay_ms (1000);
         Pause ();
         
         Test (1);
         Delay_ms (1000);
         Pause ();
         
         Test (2);
         Delay_ms (1000);
         Pause ();
         
         Test (3);
         Delay_ms (1000);
         Pause ();
         
         Test (4);
         Delay_ms (1000);
         Pause();
         
         Test (5);
         Delay_ms (1000);
         Pause ();
         
         displaychar (pic1);
         Delay_ms (1000);
         Pause ();
       }
}


/*****************************************/
void Delay_ms (unint tt)
{
    unchar TT;
    while (--tt)
      for (TT=0; TT<100; TT++)
        ;
}
/***************************************/

/**************************************/
void Pause ()
{
  while (AOUTOB==1 & STEP==0)
    {}
    if (STEP == 1)
    {
      Delay_ms (10);
      while (AOUTOB == 0)
      {}
    }
    else if (AOUTOB == 1)
    {
      Delay_ms (10);
    }
}
/************************************/

/***********************************/
void start ()
{
 SDA = 1;
 nops ();
 SCL = 1;
 nops ();
 SDA = 0;
 nops ();
 SCL = 0;
 nops ();
}




