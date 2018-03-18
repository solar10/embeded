#include "cabin_lib.h"

#define LCD_RS GPIO_Pin_1
#define LCD_CS GPIO_Pin_0
#define LCD_RD GPIO_Pin_3
#define LCD_WR GPIO_Pin_2
#define LCD_RESET GPIO_Pin_4

#define LCD_RS_H()    GPIOC->BSRR =LCD_RS
#define LCD_RS_L()    GPIOC->BRR  =LCD_RS

#define LCD_CS_H()    GPIOC->BSRR =LCD_CS
#define LCD_CS_L()    GPIOC->BRR  =LCD_CS

#define LCD_RD_H()    GPIOC->BSRR =LCD_RD
#define LCD_RD_L()    GPIOC->BRR  =LCD_RD

#define LCD_WR_H()    GPIOC->BSRR =LCD_WR
#define LCD_WR_L()    GPIOC->BRR  =LCD_WR

#define LCD_RESET_H()    GPIOC->BSRR =LCD_RESET
#define LCD_RESET_L()    GPIOC->BRR  =LCD_RESET

#define R00_ReadID             0x00
#define R01_DriverOutputControl            0x01
#define R02_LcdAcDriveControl            0x02
#define R03_EntryMode             0x03
#define R04_Resizing             0x04
//#define R5             0x05
//#define R6             0x06
#define R07_DisplayControl1             0x07
#define R08_DisplayControl2             0x08
#define R09_DisplayControl3             0x09
#define R0A_DisplayControl4            0x0A
#define R0C_ExternalInterfaceControl1            0x0C
#define R0D_FrameMarkerPosition            0x0D
//#define R14            0x0E
#define R0F_ExternalInterfaceControl2            0x0F
#define R10_PowerControl1            0x10
#define R11_PowerControl2            0x11
#define R12_PowerControl3            0x12
#define R13_PowerControl4            0x13
//#define R20            0x14
//#define R21            0x15
//#define R22            0x16
#define R17_PowerControl5            0x17
//#define R24            0x18
//#define R25            0x19
//#define R26            0x1A
//#define R27            0x1B
//#define R28            0x1C
//#define R29            0x1D
//#define R30            0x1E
//#define R31            0x1F
#define R20_GRamAddressSetHorizon            0x20
#define R21_GRamAddressSetVertical            0x21
#define R22_WriteDataToDRAM            0x22
//#define R36            0x24
//#define R37            0x25
#define R28_NvmReadData1            0x28
#define R29_NvmReadData2            0x29
//#define R43            0x2B
//#define R45            0x2D
#define R30_GammaControl1            0x30
#define R31_GammaControl2            0x31
#define R32_GammaControl3            0x32
#define R33_GammaControl4            0x33
#define R34_GammaControl5            0x34
#define R35_GammaControl6            0x35
#define R36_GammaControl7            0x36
#define R37_GammaControl8            0x37
#define R38_GammaControl9            0x38
#define R39_GammaControl10            0x39
#define R3B_GammaControl12            0x3B
#define R3C_GammaControl13            0x3C
#define R3D_GammaControl14            0x3D
//#define R62            0x3E
//#define R63            0x3F
//#define R64            0x40
//#define R65            0x41
//#define R66            0x42
//#define R67            0x43
//#define R68            0x44
//#define R69            0x45
//#define R70            0x46
//#define R71            0x47
//#define R72            0x48
//#define R73            0x49
//#define R74            0x4A
//#define R75            0x4B
//#define R76            0x4C
//#define R77            0x4D
//#define R78            0x4E
//#define R79            0x4F
#define R50_WindowHorizonRamAddressStart            0x50
#define R51_WindowHorizonRamAddressEnd            0x51
#define R52_WindowVerticalRamAddressStart            0x52
#define R53_WindowVerticalRamAddressEnd            0x53
#define R60_DriveOutputControl            0x60
#define R61_ImageDisplayControl            0x61
#define R6A_VerticalScrollingControl           0x6A
//#define R118           0x76
#define R80_DisplayPosition1           0x80
#define R81_GramStartlineAddress1           0x81
#define R82_GramEndlineAddress1           0x82
#define R83_DisplayPosition2           0x83
#define R84_GramStartlineAddress2           0x84
#define R85_GramEndlineAddress2           0x85
//#define R134           0x86
//#define R135           0x87
//#define R136           0x88
//#define R137           0x89
//#define R139           0x8B
//#define R140           0x8C
//#define R141           0x8D
//#define R143           0x8F
#define R90_PanelInterfaceControl1           0x90
//#define R145           0x91
#define R92_PanelInterfaceControl2           0x92
#define R93_PanelInterfaceControl3           0x93
//#define R148           0x94
#define R95_FrameCycleControl           0x95
//#define R150           0x96
#define R97_PanelInterfaceControl5           0x97
#define R98_PanelInterfaceControl6           0x98
//#define R153           0x99
//#define R154           0x9A
//#define R157           0x9D
//#define R192           0xC0
//#define R193           0xC1
#define R227           0xE3		
//#define R229           0xE5		
#define R231           0xE7		
#define R239           0xEF		

#define ColorWhite 0xFFFF
#define ColorBlack 0x0000
#define ColorRed 0xF800
#define ColorGreen 0x07E0
#define ColorBlue 0x001F
#define ColorYellow 0xFFE0
#define ColorCyan 0x07FF
#define ColorMagenta 0xF81F

struct ColorRect {
  u16 x1;
  u16 x2;
  u16 y1;
  u16 y2;
};

class ClassLCD
{
private:
  
public:
  void InitLCD(void);
  void InitLCD2(void);
  void WriteCommand(u16 address, u16 data);
  void WriteRamData(u16 data);
  void WriteAddress(u16 address);
  void SetColorWindow(ColorRect rect);
  void TestLCD(u8 fonts[41][31]);
  void ShowCharLCD(u8 ch, u8 position, u8 fonts[41][31]);
};
