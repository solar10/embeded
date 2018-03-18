#include "ili9325.h"
#include "stm32f10x_conf.h"
#include "cabin_lib.h"
#include "util.h"
void ClassLCD::InitLCD(void)
{
  ClassUtil Util;
  
  GPIO_SetBits(GPIOA, LCD_RS); //initial state
  GPIO_SetBits(GPIOA, LCD_CS); //initial state
  GPIO_SetBits(GPIOA, LCD_RD); //initial state
  GPIO_SetBits(GPIOA, LCD_WR); //initial state

  LCD_RESET_L(); //Reset LCD
  Util.Delay(10000);
  LCD_RESET_H();
  Util.Delay(10000);

  //GPIO_ResetBits(GPIOA, LCD_CS); //LCD select
  LCD_CS_L();

  WriteCommand(R227, 0x3008); /* Set internal timing */
  WriteCommand(R231, 0x0012); /* Set internal timing */
  WriteCommand(R239, 0x1231); /* Set internal timing */
  WriteCommand(R01_DriverOutputControl, 0x0000);   /* Set SS and SM bit */
  WriteCommand(R02_LcdAcDriveControl, 0x0700);   /* Set 1 line inversion */
  WriteCommand(R03_EntryMode, 0x0030);   /* Set GRAM write direction and BGR=1. */
  WriteCommand(R04_Resizing, 0x0000);   /* Resize register */
  WriteCommand(R08_DisplayControl2, 0x0202);   /* Set the back porch and front porch */
  WriteCommand(R09_DisplayControl3, 0x0000);   /* Set non-display area refresh cycle ISC[3:0] */
  WriteCommand(R0A_DisplayControl4, 0x0000);  /* FMARK function */
  WriteCommand(R0C_ExternalInterfaceControl1, 0x0001);  /* RGB interface setting */
  WriteCommand(R0D_FrameMarkerPosition, 0x0000);  /* Frame marker Position */
  WriteCommand(R0F_ExternalInterfaceControl2, 0x0000);  /* RGB interface polarity */
  /* Power On sequence -------------------------------------------------------*/
  WriteCommand(R10_PowerControl1, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  WriteCommand(R11_PowerControl2, 0x0000);  /* DC1[2:0], DC0[2:0], VC[2:0] */
  WriteCommand(R12_PowerControl3, 0x0000);  /* VREG1OUT voltage */
  WriteCommand(R13_PowerControl4, 0x0000);  /* VDV[4:0] for VCOM amplitude */
  Util.Delay(20000);                /* Dis-charge capacitor power voltage (200ms) */  
  WriteCommand(R11_PowerControl2, 0x0007);  /* DC1[2:0], DC0[2:0], VC[2:0] */
  Util.Delay(5000);                 /* Delay 50 ms */
  WriteCommand(R10_PowerControl1, 0x12B0);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  Util.Delay(5000);                  /* Delay 50 ms */
  WriteCommand(R12_PowerControl3, 0x01BD);  /* External reference voltage= Vci */
  Util.Delay(5000);                 /* Delay 50 ms */ 
  WriteCommand(R13_PowerControl4, 0x1400);       /* VDV[4:0] for VCOM amplitude */
  WriteCommand(R29_NvmReadData2, 0x000E);  /* VCM[4:0] for VCOMH */
  Util.Delay(5000);                 /* Delay 50 ms */
  WriteCommand(R20_GRamAddressSetHorizon, 0x0000);  /* GRAM horizontal Address */
  WriteCommand(R21_GRamAddressSetVertical, 0x013F);  /* GRAM Vertical Address */
  /* Adjust the Gamma Curve --------------------------------------------------*/
  WriteCommand(R30_GammaControl1, 0x0007);
  WriteCommand(R31_GammaControl2, 0x0302);
  WriteCommand(R32_GammaControl3, 0x0105);
  WriteCommand(R35_GammaControl6, 0x0206);
  WriteCommand(R36_GammaControl7, 0x0808);
  WriteCommand(R37_GammaControl8, 0x0206);
  WriteCommand(R38_GammaControl9, 0x0504);
  WriteCommand(R39_GammaControl10, 0x0007);
  WriteCommand(R3C_GammaControl13, 0x0105);
  WriteCommand(R3D_GammaControl14, 0x0808);
  /* Set GRAM area -----------------------------------------------------------*/
  WriteCommand(R50_WindowHorizonRamAddressStart, 0x0000);  /* Horizontal GRAM Start Address */
  WriteCommand(R51_WindowHorizonRamAddressEnd, 0x00EF);  /* Horizontal GRAM End Address */
  WriteCommand(R52_WindowVerticalRamAddressStart, 0x0000);  /* Vertical GRAM Start Address */
  WriteCommand(R53_WindowVerticalRamAddressEnd, 0x013F);  /* Vertical GRAM End Address */
  WriteCommand(R60_DriveOutputControl,  0xA700); /* Gate Scan Line */
  WriteCommand(R61_ImageDisplayControl,  0x0001); /* NDL,VLE, REV */
  WriteCommand(R6A_VerticalScrollingControl, 0x0000); /* Set scrolling line */
  /* Partial Display Control -------------------------------------------------*/
  WriteCommand(R80_DisplayPosition1, 0x0000);
  WriteCommand(R81_GramStartlineAddress1, 0x0000);
  WriteCommand(R82_GramEndlineAddress1, 0x0000);
  WriteCommand(R83_DisplayPosition2, 0x0000);
  WriteCommand(R84_GramStartlineAddress2, 0x0000);
  WriteCommand(R85_GramEndlineAddress2, 0x0000);
  /* Panel Control -----------------------------------------------------------*/
  WriteCommand(R90_PanelInterfaceControl1, 0x0010);
  WriteCommand(R92_PanelInterfaceControl2, 0x0000);
  WriteCommand(R93_PanelInterfaceControl3, 0x0003);
  WriteCommand(R95_FrameCycleControl, 0x0110);
  WriteCommand(R97_PanelInterfaceControl5, 0x0000);
  WriteCommand(R98_PanelInterfaceControl6, 0x0000);
  /* Set GRAM write direction and BGR = 1
     I/D=01 (Horizontal : increment, Vertical : decrement)
     AM=1 (address is updated in vertical writing direction) */
  WriteCommand(R03_EntryMode, 0x1000);//1018
  WriteCommand(R07_DisplayControl1, 0x0112);   /* 262K color and display ON */

  WriteCommand(R50_WindowHorizonRamAddressStart, 0x0000);
  WriteCommand(R51_WindowHorizonRamAddressEnd, 0x00EF);
  WriteCommand(R52_WindowVerticalRamAddressStart, 0x0000);
  WriteCommand(R53_WindowVerticalRamAddressEnd, 0x013F);
  
  WriteCommand(R20_GRamAddressSetHorizon, 0); //Horizontal GRAM address
  WriteCommand(R21_GRamAddressSetVertical, 0); //Vertical GRAM address
  
  WriteAddress(R22_WriteDataToDRAM); //write RAM data instruction
  
  for (u32 i=0; i<76800; i++)
  {
    WriteRamData(0x0000);
  }

  //GPIO_SetBits(GPIOA, LCD_CS); //initial state
  LCD_CS_H();
}

void ClassLCD::InitLCD2(void)
{
  ClassUtil Util;
  
  GPIO_SetBits(GPIOA, LCD_RS); //initial state
  GPIO_SetBits(GPIOA, LCD_CS); //initial state
  GPIO_SetBits(GPIOA, LCD_RD); //initial state
  GPIO_SetBits(GPIOA, LCD_WR); //initial state

  LCD_RESET_L(); //Reset LCD
  Util.Delay(10000);
  LCD_RESET_H();
  Util.Delay(10000);

  //GPIO_ResetBits(GPIOA, LCD_CS); //LCD select
  LCD_CS_L();

  WriteCommand(0x0001,0x0100);   
  WriteCommand(0x0002,0x0700);    
  WriteCommand(0x0003,0x1008);  //0x1030 
  WriteCommand(0x0008,0x0302);   
  WriteCommand(0x0009,0x0000);  
  WriteCommand(0x000A,0x0008);   
  //*******POWER CONTROL REGISTER INITIAL*******//    
  WriteCommand(0x0010,0x0790);   
  WriteCommand(0x0011,0x0005);   
  WriteCommand(0x0012,0x0000);  
  WriteCommand(0x0013,0x0000);   
  Util.Delay(500000);
  //delayms(50, 
  //********POWER SUPPPLY STARTUP 1 SETTING*******//    
  WriteCommand(0x0010,0x12B0);   
  Util.Delay(500000);
  // delayms(50,  
  WriteCommand(0x0011,0x0007);   
  Util.Delay(500000);
  //delayms(50,  
  //********POWER SUPPLY STARTUP 2 SETTING******//    
  WriteCommand(0x0012,0x008C);   
  WriteCommand(0x0013,0x1700);   
  WriteCommand(0x0029,0x0022);   
  Util.Delay(500000);
  // delayms(50,   
  //******GAMMA CLUSTER SETTING******//    
  WriteCommand(0x0030,0x0000);   
  WriteCommand(0x0031,0x0505);   
  WriteCommand(0x0032,0x0205);   
  WriteCommand(0x0035,0x0206);   
  WriteCommand(0x0036,0x0408);   
  WriteCommand(0x0037,0x0000);   
  WriteCommand(0x0038,0x0504);
  WriteCommand(0x0039,0x0206);   
  WriteCommand(0x003C,0x0206);   
  WriteCommand(0x003D,0x0408);   
  // -----------DISPLAY WINDOWS 240*320-------------//    
  WriteCommand(0x0050,0x0000);
  WriteCommand(0x0051,0x00EF);  
  WriteCommand(0x0052,0x0000);  
  WriteCommand(0x0053,0x013F);  
  //-----FRAME RATE SETTING-------//    
  WriteCommand(0x0060,0xA700);  
  WriteCommand(0x0061,0x0001);  
  WriteCommand(0x0090,0x0033);
  //RTNI setting
  //-------DISPLAY ON------//    
  WriteCommand(0x0007,0x0133);   
  WriteCommand(0x0001,0x0100);   
  WriteCommand(0x0002,0x0700);   
  WriteCommand(0x0003,0x1028);     //0x1030  ?????? ????? ???? : ??->??, ??->??, ????  ???
  WriteCommand(0x0008,0x0302);   
  WriteCommand(0x0009,0x0000);  
  WriteCommand(0x000A,0x0008);   
  //*******POWER CONTROL REGISTER INITIAL*******//    
  WriteCommand(0x0010,0x0790);   
  WriteCommand(0x0011,0x0005);   
  WriteCommand(0x0012,0x0000);  
  WriteCommand(0x0013,0x0000);   
  Util.Delay(500000);
  //delayms(50, 
  //********POWER SUPPPLY STARTUP 1 SETTING*******//    
  WriteCommand(0x0010,0x12B0);   
  Util.Delay(500000);
  // delayms(50,  
  WriteCommand(0x0011,0x0007);   
  Util.Delay(500000);
  // delayms(50,  
  //********POWER SUPPLY STARTUP 2 SETTING******//    
  WriteCommand(0x0012,0x008C);   
  WriteCommand(0x0013,0x1700);   
  WriteCommand(0x0029,0x0022);   
  Util.Delay(500000);
  // delayms(50,   
  //******GAMMA CLUSTER SETTING******//    
  WriteCommand(0x0030,0x0000);   
  WriteCommand(0x0031,0x0505);   
  WriteCommand(0x0032,0x0205);   
  WriteCommand(0x0035,0x0206);   
  WriteCommand(0x0036,0x0408);   
  WriteCommand(0x0037,0x0000);   
  WriteCommand(0x0038,0x0504);
  WriteCommand(0x0039,0x0206);   
  WriteCommand(0x003C,0x0206);   
  WriteCommand(0x003D,0x0408);   
  // -----------DISPLAY WINDOWS 240*320-------------//    
  WriteCommand(0x0050,0x0000);
  WriteCommand(0x0051,0x00EF);  
  WriteCommand(0x0052,0x0000);  
  WriteCommand(0x0053,0x013F);  
  //-----FRAME RATE SETTING-------//    
  WriteCommand(0x0060,0xA700);   
  WriteCommand(0x0061,0x0001);   
  WriteCommand(0x0090,0x0033);
  //RTNI setting
  //-------DISPLAY ON------//    
  WriteCommand(0x0007,0x0133);

  WriteCommand(R50_WindowHorizonRamAddressStart, 0x0000);
  WriteCommand(R51_WindowHorizonRamAddressEnd, 0x00EF);
  WriteCommand(R52_WindowVerticalRamAddressStart, 0x0000);
  WriteCommand(R53_WindowVerticalRamAddressEnd, 0x013F);
  
  WriteCommand(R20_GRamAddressSetHorizon, 0); //Horizontal GRAM address
  WriteCommand(R21_GRamAddressSetVertical, 0); //Vertical GRAM address
  
  WriteAddress(R22_WriteDataToDRAM); //write RAM data instruction
  
  for (u32 i=0; i<76800; i++)
  {
    WriteRamData(0x0000);
  }

  LCD_CS_H();
}

void ClassLCD::WriteCommand(u16 address, u16 data)
{
  Gpio gpio;
  LCD_CS_L();
  LCD_RS_L();
  gpio.Set(address);
  LCD_WR_L();
  LCD_WR_H();

  LCD_RS_H();
  gpio.Set(data);
  LCD_WR_L();
  LCD_WR_H();
  LCD_CS_H();
}

void ClassLCD::WriteRamData(u16 data)
{
  Gpio gpio;
  LCD_CS_L();
  gpio.Set(data);
  LCD_WR_L();
  LCD_WR_H();
  LCD_CS_H();
}

void ClassLCD::WriteAddress(u16 address)
{
  Gpio gpio;
  LCD_CS_L();
  LCD_RS_L();
  gpio.Set(address);
  LCD_WR_L();
  LCD_WR_H();
  LCD_RS_H();
  LCD_CS_H();
}

void ClassLCD::SetColorWindow(ColorRect rect)
{
  WriteCommand(R50_WindowHorizonRamAddressStart, rect.x1);
  WriteCommand(R51_WindowHorizonRamAddressEnd, rect.x2);
  WriteCommand(R52_WindowVerticalRamAddressStart, rect.y1);
  WriteCommand(R53_WindowVerticalRamAddressEnd, rect.y2);
  
  WriteCommand(R20_GRamAddressSetHorizon, rect.x1); //Horizontal GRAM address
  WriteCommand(R21_GRamAddressSetVertical, rect.y1); //Vertical GRAM address
  WriteAddress(R22_WriteDataToDRAM); //write RAM data instruction
}

void ClassLCD::TestLCD(u8 fonts[41][31])
{
  ClassUtil Util;

  ColorRect rect;
  
  rect.x1 = 100;
  rect.x2   = 111;//239
  rect.y1 = 100;
  rect.y2   = 116;//319

  SetColorWindow(rect);
  //WriteAddress(R22_WriteDataToDRAM); //write RAM data instruction
  
  u16 color=0;
  //for (int color=0;color<8;color++)
  {
    for (u32 i=0; i<(rect.x2-rect.x1+1)*(rect.y2-rect.y1+1); i++)
      WriteRamData(ColorRed); //dump graphic data

    for (u32 i=0; i<(rect.x2-rect.x1+1)*(rect.y2-rect.y1+1); i++)
    {
      if (i%10 == 0)
      {
        color++;
        Util.Delay(50);
      }
      if (color%8==0)
        WriteRamData(ColorWhite); //dump graphic data
      else if (color%8==1)
        WriteRamData(ColorRed); //dump graphic data
      else if (color%8==2)
        WriteRamData(ColorGreen); //dump graphic data
      else if (color%8==3)
        WriteRamData(ColorBlue); //dump graphic data
      else if (color%8==4)
        WriteRamData(ColorYellow); //dump graphic data
      else if (color%8==5)
        WriteRamData(ColorCyan); //dump graphic data
      else if (color%8==6)
        WriteRamData(ColorMagenta); //dump graphic data
      else if (color%8==7)
        WriteRamData(ColorBlack); //dump graphic data
    }
  }

  Util.Delay(500000);
    
  for (u8 x=0;x<41;x++)
  {
    rect.x1 = 100;
    rect.x2   = 111;
    rect.y1 = 100;
    rect.y2   = 116;
    
    SetColorWindow(rect);
    //WriteAddress(R22_WriteDataToDRAM); //write RAM data instruction
    
    for (int j=1;j<31;j++)
    {
      for (int k=7;k>=0;k--)
      {
        if (((fonts[x][j] >> k) & 0x01) == 0x01)  //??T????????? 240?? ??T?????? ??? ????
          WriteRamData(ColorWhite);
        else
          WriteRamData(ColorBlack);
      }
    }
    Util.Delay(100000);
  }

  Util.Delay(100000);
  
  /*for (int l=0;l<10;l++)
  {
    rect.x1 = 100;
    rect.x2   = 199;
    rect.y1 = 100;
    rect.y2   = 199;

    SetColorWindow(rect);

    
    for (int i=0;i<10000;i++)
    {
      switch (l%7)
      {
        case 0 :  WriteRamData(ColorRed); break;
        case 1 :  WriteRamData(ColorGreen); break;
        case 2 :  WriteRamData(ColorBlue); break;
        case 3 :  WriteRamData(ColorYellow); break;
        case 4 :  WriteRamData(ColorCyan); break;
        case 5 :  WriteRamData(ColorMagenta); break;
        case 6 :  WriteRamData(ColorWhite); break;
        default : break;
      }
    }

    //LCD_CS_H();  
    Util.Delay(1000000);
  }*/
}

void ClassLCD::ShowCharLCD(u8 ch, u8 position, u8 fonts[41][31])
{
  ColorRect rect;
  
  rect.x1 = 100 + position * 10;
  rect.x2   = 111 + position * 10;//239
  rect.y1 = 100;
  rect.y2   = 116;//319

  SetColorWindow(rect);
  
  for (u8 c=0;c<42;c++)
  {
    if (fonts[c][0] == ch)
    {
      for (int j=1;j<31;j++)
      {
        for (int k=7;k>=0;k--)
        {
          if (((fonts[c][j] >> k) & 0x01) == 0x01)  //??T????????? 240?? ??T?????? ??? ????
            WriteRamData(ColorWhite);
          else
            WriteRamData(ColorBlack);
        }
      }
    }
  }
}
