/***************************/
//Project:5.7F only
//Dots;640*480
//Driver_IC:tbd
//Panel_Mode:TFT
//Writer:JWan
//Vdd:3.3V
//Date:2013.3.14
/**************************/
#include<REG51.H>
#include<INTRINS.H>


#define unchar unsigned char
#define unint  unsigned int


#define GATE 480
#define SOURCE 640



sbit  RS  = P3^0;
sbit  CS  = P3^1;
sbit  WRB = P3^7;
sbit  RDB = P3^4;

sbit  RES = P3^6;

sbit AOUTOB = P2^1;      //Pause the display when it is '0'
sbit  STEP  = P2^0;      //Step



void Write_Command_SSD1963(unchar dat);
void Write_Parameter_SSD1963(unchar dat);
void Initial_SSD1963();
void SSD1963_Show_RGB(unchar dat1,unchar dat2,unchar dat3);
void Piex_Show_RGB(unchar dat1,unchar dat2,unchar dat3);
void Delay_ms(unint tt);
void SSD1963_RAM_Address();
void Pause();
void Frame();
void Show_gary();

unsigned char code color[]=
{
0x00,0x00,0x00,
0x00,0x00,0xff,
0x00,0xff,0xff,
0x00,0xff,0x00,
0xff,0xff,0x00,
0xff,0x00,0x00,
0xff,0x00,0xff,
0xff,0xff,0xff,
};

unsigned char code gray[]=
{
0xfc,0xf4,
0xec,0xe4,
0xdc,0xd4,
0xcc,0xc4,
0xbc,0xb4,
0xac,0xa4,
0x9c,0x94,
0x8c,0x84,
0x7c,0x74,
0x6c,0x64,
0x5c,0x54,
0x4c,0x44,
0x3c,0x34,
0x2c,0x24,
0x1c,0x14,
0x0c,0x04,
};

main()
{
	RES = 0; 		//Active low
	Delay_ms(50);
	RES = 1;
	Delay_ms(100);

        Initial_SSD1963();

        while(1)
        {
        Frame();
	Delay_ms(1000);
        Pause();

	SSD1963_Show_RGB(0xff,0xff,0xff);
	Delay_ms(1000);
        Pause();

	SSD1963_Show_RGB(0xff,0x00,0x00);
	Delay_ms(1000);
        Pause();

        SSD1963_Show_RGB(0x00,0xff,0x00);
	Delay_ms(1000);
        Pause();

	SSD1963_Show_RGB(0x00,0x00,0xff);
	Delay_ms(1000);
        Pause();

        Show_gary();
	Delay_ms(1000);
        Pause();
        }
}

/******************Delay_ms********************/
void Delay_ms(unint tt)
  {
    unchar TT;
    while(--tt)
	for(TT=0;TT<100;TT++);

   }

/***********Aouto and Step********************/
 void Pause()
{
while(AOUTOB==1&STEP==0)
	{
        }
	if(STEP==1)
          {
	  Delay_ms(10);
	   while(AOUTOB==0)
		{}
	  }
	else if(AOUTOB==1)
		{
		Delay_ms(10);
		}
}





/************************************************/
//Write Command for SSD1963 with 8080 8 bits system in parellel
/************************************************/
void Write_Command_SSD1963(unchar dat)
{
        RDB=1;
        RS=0;
        WRB=0;
        CS=0;
        P1=dat;
        CS=1;
        WRB=1;
}


/*************************************************/
//Write data for SSD1963 with 6800 8 bits system in parellel
/*************************************************/
void Write_Parameter_SSD1963(unchar dat)
 {
        RDB=1;
        RS=1;
        WRB=0;
        CS=0;
        P1=dat;
        CS=1;
        WRB=1;
 }



/*************************************************/
//Set SSD1963 Ram address
/*************************************************/
void SSD1963_RAM_Address()
{
        Write_Command_SSD1963(0x2a);	//SET column address
        Write_Parameter_SSD1963(0x00);	//SET start column address=0
        Write_Parameter_SSD1963(0x00);
        Write_Parameter_SSD1963((SOURCE-1)>>8);	//SET end column address
        Write_Parameter_SSD1963(SOURCE-1);

        Write_Command_SSD1963(0x2b);	//SET page address
        Write_Parameter_SSD1963(0x00);	//SET start page address=0
        Write_Parameter_SSD1963(0x00);
        Write_Parameter_SSD1963((GATE-1)>>8);	//SET end page address
        Write_Parameter_SSD1963(GATE-1);

        Write_Command_SSD1963(0x2c);
}

/*******************************************/
//Write for one piex color
/*******************************************/
void Piex_Show_RGB(unchar dat1,unchar dat2,unchar dat3)
{
        Write_Parameter_SSD1963(dat1);
        Write_Parameter_SSD1963(dat2);
        Write_Parameter_SSD1963(dat3);
}


/*******************************************/
//Test for all white or black or red or blue or green
/*******************************************/
void SSD1963_Show_RGB(unchar dat1,unchar dat2,unchar dat3)
{
      unint i,j;

      SSD1963_RAM_Address();

      for(i=0;i<GATE;i++)
         for(j=0;j<SOURCE;j++)
            {
            Write_Parameter_SSD1963(dat1);
            Write_Parameter_SSD1963(dat2);
            Write_Parameter_SSD1963(dat3);
            }
}


/*******************************************/
//Display Frame
/*******************************************/
void Frame()
{
      unint i,j;

      SSD1963_RAM_Address();

      for(i=0;i<1;i++)
         {
         Piex_Show_RGB(0xff,0x00,0x00);
         for(j=0;j<638;j++)
            {
            Piex_Show_RGB(0xff,0xff,0xff);
            }
         Piex_Show_RGB(0x00,0x00,0xff);
         }

      for(i=0;i<478;i++)
         {
         Piex_Show_RGB(0xff,0x00,0x00);
         for(j=0;j<638;j++)
            {
            Piex_Show_RGB(0x00,0x00,0x00);
            }
         Piex_Show_RGB(0x00,0x00,0xff);
         }

      for(i=0;i<1;i++)
         {
         Piex_Show_RGB(0xff,0x00,0x00);
         for(j=0;j<638;j++)
            {
            Piex_Show_RGB(0xff,0xff,0xff);
            }
         Piex_Show_RGB(0x00,0x00,0xff);
         }
}


/*******************************************/
//Display Gtay
/*******************************************/
void Show_gary()
{
        unint i,j,k;
        unint x;
        unint GATE2,SOURCE8,SOURCE32;

        GATE2   =GATE/2;
        SOURCE8 =SOURCE/8;
        SOURCE32=SOURCE/32;

        SSD1963_RAM_Address();

        for(i=0;i<GATE2;i++)
           {
           for(j=0;j<8;j++)
              {
              x=j*3;
              for(k=0;k<SOURCE8;k++)
                 {
                 Piex_Show_RGB(color[x],color[x+1],color[x+2]);
                 }
              }
           }
        for(i=0;i<GATE2;i++)
           {
           for(j=0;j<32;j++)
              {
              for(k=0;k<SOURCE32;k++)
                 {
                 Piex_Show_RGB(gray[j],gray[j],gray[j]);
                 }
              }
           }
}


/*********************************************/
//initial_code for the LCD
/*********************************************/
void Initial_SSD1963()
{

         Write_Command_SSD1963(0x01);
         Delay_ms(10);
         Write_Command_SSD1963(0xe0);    //START PLL
         Write_Parameter_SSD1963(0x01);
         Delay_ms(5);
         Write_Command_SSD1963(0xe0);    //LOCK PLL
         Write_Parameter_SSD1963(0x03);
         Delay_ms(5);

         Write_Command_SSD1963(0xb0);  //SET LCD MODE  SET TFT 18Bits MODE
         Write_Parameter_SSD1963(0x0c);   //SET TFT MODE & hsync+Vsync+DEN MODE
         Write_Parameter_SSD1963(0x80);   //SET TFT MODE & hsync+Vsync+DEN MODE
         Write_Parameter_SSD1963((SOURCE-1)>>8);   //SET horizontal size=640-1 HightByte
         Write_Parameter_SSD1963(SOURCE-1);      //SET horizontal size=640-1 LowByte
         Write_Parameter_SSD1963((GATE-1)>>8);   //SET vertical size=480-1 HightByte
         Write_Parameter_SSD1963(GATE-1);   //SET vertical size=480-1 LowByte
         Write_Parameter_SSD1963(0x00);   //SET even/odd line RGB seq.=RGB

         Write_Command_SSD1963(0xf0); //SET pixel data I/F format=8bit
         Write_Parameter_SSD1963(0x00);
         Write_Command_SSD1963(0x3a);   // SET R G B format = 6 6 6
         Write_Parameter_SSD1963(0x60);

         //Set the MN of PLL
         //Write_Command_SSD1963(0xe2);   //100MHz PLL frequency
         //Write_Parameter_SSD1963(0x1d);   //M
         //Write_Parameter_SSD1963(0x02); //N
         //Write_Parameter_SSD1963(0x54);

         Write_Command_SSD1963(0xe6);   	//
         Write_Parameter_SSD1963(0x02);
         Write_Parameter_SSD1963(0xFF); //55
         Write_Parameter_SSD1963(0xFF);


         //Set front porch and back porch
         Write_Command_SSD1963(0xb4);
         Write_Parameter_SSD1963(0x03); //horizontal total period HT
         Write_Parameter_SSD1963(0x20); //HT=
         Write_Parameter_SSD1963(0x00); //HPS
         Write_Parameter_SSD1963(0x90);
         Write_Parameter_SSD1963(0x10); //HPW
         Write_Parameter_SSD1963(0x00); //SET Hsync pulse start position
         Write_Parameter_SSD1963(0x00); //Set the horizontal sync pulse width (LLINE) in start.
         Write_Parameter_SSD1963(0x00);

         Write_Command_SSD1963(0xb6);
         Write_Parameter_SSD1963(0x02); //VT=
         Write_Parameter_SSD1963(0x0D);
         Write_Parameter_SSD1963(0x00); //VPS
         Write_Parameter_SSD1963(0x23);
         Write_Parameter_SSD1963(0x0A); //VPW
         Write_Parameter_SSD1963(0x00); //FPS
         Write_Parameter_SSD1963(0x00);

         Write_Command_SSD1963(0x2a);	//SET column address
         Write_Parameter_SSD1963(0x00);	//SET start column address=0
         Write_Parameter_SSD1963(0x00);
         Write_Parameter_SSD1963((SOURCE-1)>>8);	//SET end column address
         Write_Parameter_SSD1963(SOURCE-1);

         Write_Command_SSD1963(0x2b);	//SET page address
         Write_Parameter_SSD1963(0x00);	//SET start page address=0
         Write_Parameter_SSD1963(0x00);
         Write_Parameter_SSD1963((GATE-1)>>8);	//SET end page address
         Write_Parameter_SSD1963(GATE-1);

         Write_Command_SSD1963(0x29);
         Write_Command_SSD1963(0x2c);
}
