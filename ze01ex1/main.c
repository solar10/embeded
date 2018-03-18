#include "RTE_Components.h"
#include "RTE_Device.h"
#include "stm32f10x_conf.h"
#include "cabin_lib.h"
#include "font.h"
#include "ov7670.h"
#include "ili9325.h"
#include "util.h"
//#include "picdata.h"

unsigned short lcd_init();
void lcd_write(unsigned char reg,unsigned short data);
unsigned short lcd_read(unsigned char reg);
unsigned short lcd_rdata();
void lcd_data(unsigned short data);
void lcd_wratch();
void lcd_send_init();
void cursor(unsigned short x,unsigned short y);
void windowsize(unsigned short x,unsigned short y);
void drawpic(const unsigned char *picdata,unsigned short x,unsigned short y);
void drawpic1(const unsigned short *picdata,unsigned short x,unsigned short y);
void caminit();
void drawcam(unsigned short x,unsigned short y);
void cam7670_winset(u16 startx, u16 starty, u16 width, u16 height);
vu16 device=0,x=0,y=0,data=0x0,aaa=0,flag=1;
vu32 count=0;
// unsigned char picdata1[95*320*2]={0,};
struct Lcd {
	unsigned short reg;
	unsigned short val;
	};
unsigned short * picdata1 = (unsigned short *)0x068000000;

struct Lcd *lcda=(struct Lcd *)0x06c000000;
	
const unsigned char cam_setup[][2]=
{
 /*  {0x12, 0x46},*/
	{0x00, 0x00},
	{0x01, 0x80},
	{0x02, 0x80},
	{0x20, 0x04},
	{0x3a, 0x04},
	{0x40, 0xd0},
	{0x12, 0x14},//resolution
	{0x3e, 0x00},//resolution(manual)	
//	{0x17, 0x0},
//	{0x18, 0x60},	
//	{0x32, 0x80},
//	{0x19, 0x00},
//	{0x1a, 0x78},//0x7a,
//	{0x03, 0x00},//0x0a,
	{0x17, 0x16},
	{0x18, 0x06},
	{0x32, 0xa0},
	{0x19, 0x04},
	{0x1a, 0x9b},//0x7a,
	{0x03, 0x06},//0x0a,
	
	{0x0c, 0x00},
	{0x70, 0x00},
	{0x71, 0x00},
	{0x72, 0x11},
	{0x73, 0x00},//resolution(manual)	
	{0xa2, 0x00},//pix delay
	{0x11, 0x30}, //clock prescaler  0x34 

	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},
	{0x7d, 0x3c},
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},
	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},
	{0x87, 0xc4},
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	{0x00, 0x00},//AGC
	{0x10, 0x00},
//	{0x0d, 0x30},//windows size
//	{0x42, 0xc0},
	{0x14, 0x20},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},
	{0x24, 0x75},
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},
	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},
	{0xaa, 0x94},
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
	{0x1e, 0x37},//0x07,
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
	{0x35, 0x0b},
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},//
	{0x3c, 0x78},
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x0c},///////////////////////
//	{0x6b, 0x80},//PLL
	{0x74, 0x19},
	{0x8d, 0x4f},
	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
	{0xb3, 0x82},
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
	{0x5b, 0x44},
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},
	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},
	{0x6e, 0x11},
	{0x6f, 0x9f},//0x9e for advance AWB
	{0x6a, 0x40},
	{0x01, 0x40},
	{0x02, 0x40},
	{0x13, 0xe7},
	{0x15, 0x20},
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
	{0x58, 0x9e},	
	{0x41, 0x08},
	{0x3f, 0x00},
	{0x75, 0x05},
	{0x76, 0xe1},
	{0x4c, 0x00},
	{0x77, 0x01},
	{0x3d, 0xc2},	//0xc0,
	{0x4b, 0x09},
	{0xc9, 0x60},
	{0x41, 0x38},
	{0x56, 0x40},//0x40,  change according to Jim's request	
	{0x34, 0x11},
	{0x3b, 0x02},//0x00,//0x02,
	{0xa4, 0x89},//0x88,
	{0x96, 0x00},
	{0x97, 0x30},
	{0x98, 0x20},
	{0x99, 0x30},
	{0x9a, 0x84},
	{0x9b, 0x29},
	{0x9c, 0x03},
	{0x9d, 0x4c},
	{0x9e, 0x3f},
	{0x78, 0x04},	
	{0x79, 0x01},
	{0xc8, 0xf0},
	{0x79, 0x0f},
	{0xc8, 0x00},
	{0x79, 0x10},
	{0xc8, 0x7e},
	{0x79, 0x0a},
	{0xc8, 0x80},
	{0x79, 0x0b},
	{0xc8, 0x01},
	{0x79, 0x0c},
	{0xc8, 0x0f},
	{0x79, 0x0d},
	{0xc8, 0x20},
	{0x79, 0x09},
	{0xc8, 0x80},
	{0x79, 0x02},
	{0xc8, 0xc0},
	{0x79, 0x03},
	{0xc8, 0x40},
	{0x79, 0x05},
	{0xc8, 0x30},
	{0x79, 0x26},
	{0x09, 0x03},
	{0x55, 0x00},
	{0x56, 0x40},	
	{0x3b, 0x42},//0x82,//0xc0,//0xc2,	//night mode
	  /* color matrix coefficient */
#if 1
  {0x4f, 0xb3},
  {0x50, 0xb3},
  {0x51, 0x00},
  {0x52, 0x3d},
  {0x53, 0xa7},
  {0x54, 0xe4},
  {0x58, 0x9e},
#else
  {0x4f, 0x80},
  {0x50, 0x80},
  {0x51, 0x00},
  {0x52, 0x22},
  {0x53, 0x5e},
  {0x54, 0x80},
  {0x58, 0x9e},
#endif

  /* 3a */
//  {0x13, 0x84},
//  {0x14, 0x0a},   // AGC Ceiling = 2x
//  {0x5F, 0x2f},   // AWB B Gain Range (empirically decided)
//                  // without this bright scene becomes yellow (purple). might be because of color matrix
//  {0x60, 0x98},   // AWB R Gain Range (empirically decided)
//  {0x61, 0x70},   // AWB G Gain Range (empirically decided)
//  {0x41, 0x38},   // edge enhancement, de-noise, AWG gain enabled
	

  /* gamma curve */
#if 1
  {0x7b, 16},
  {0x7c, 30},
  {0x7d, 53},
  {0x7e, 90},
  {0x7f, 105},
  {0x80, 118},
  {0x81, 130},
  {0x82, 140},
  {0x83, 150},
  {0x84, 160},
  {0x85, 180},
  {0x86, 195},
  {0x87, 215},
  {0x88, 230},
  {0x89, 244},
  {0x7a, 16},
#else
  /* gamma = 1 */
  {0x7b, 4},
  {0x7c, 8},
  {0x7d, 16},
  {0x7e, 32},
  {0x7f, 40},
  {0x80, 48},
  {0x81, 56},
  {0x82, 64},
  {0x83, 72},
  {0x84, 80},
  {0x85, 96},
  {0x86, 112},
  {0x87, 144},
  {0x88, 176},
  {0x89, 208},
  {0x7a, 64},
#endif

	
	//240*320
				{0x3a, 0x0c},
        {0x40, 0xd0},
        {0x12, 0x14},
				
//	{0x17, 0x16},
//	{0x18, 0x06},
//	{0x32, 0xa0},
//	{0x19, 0x04},
//	{0x1a, 0x9b},//0x7a,
//	{0x03, 0x06},//0x0a,				
				
        {0x17, 0x16},
        {0x18, 0x04},
        {0x32, 0x80},
        {0x19, 0x02},//иобу?им
        {0x1a, 0x7a},//0x7a,
        {0x03, 0x03},//иобу?им
        {0x3e, 0x00},//
        {0x70, 0x00},
        {0x71, 0x00},
        {0x72, 0x11},
        {0x73, 0x00},//
        {0xa2, 0x02},
//        {0x11, 0x01},
        {0x7a, 0x20},
        {0x7b, 0x1c},
        {0x7c, 0x28},
        {0x7d, 0x3c},
        {0x7e, 0x55},
        {0x7f, 0x68},
        {0x80, 0x76},
        {0x81, 0x80},
        {0x82, 0x88},
        {0x83, 0x8f},
        {0x84, 0x96},
        {0x85, 0xa3},
        {0x86, 0xaf},
        {0x87, 0xc4},
        {0x88, 0xd7},
        {0x89, 0xe8},
        {0x13, 0xe7},
        {0x00, 0x00},//AGC
        {0x10, 0x00},
        {0x0d, 0x00},
        {0x14, 0x20},//0x38, limit the max gain
        {0xa5, 0x05},
        {0xab, 0x07},
        {0x24, 0x75},
        {0x25, 0x63},
        {0x26, 0xA5},
        {0x9f, 0x78},
        {0xa0, 0x68},
        {0xa1, 0x03},
        {0xa6, 0xdf},
        {0xa7, 0xdf},
        {0xa8, 0xf0},
        {0xa9, 0x90},
        {0xaa, 0x94},
        {0x13, 0xe7},
        {0x0e, 0x61},
        {0x0f, 0x82},
        {0x16, 0x02},
        {0x1e, 0x07},
        {0x21, 0x02},
        {0x22, 0x91},
        {0x29, 0x07},
        {0x33, 0x0b},
        {0x35, 0x0b},
        {0x37, 0x1d},
        {0x38, 0x71},
        {0x39, 0x2a},//
        {0x3c, 0x78},
        {0x4d, 0x40},
        {0x4e, 0x20},
        {0x69, 0x0c},
        {0x6b, 0xc0},//PLL
        {0x74, 0x19},
        {0x8d, 0x4f},
        {0x8e, 0x00},
        {0x8f, 0x00},
        {0x90, 0x00},
        {0x91, 0x00},
        {0x92, 0x00},
        {0x96, 0x00},
        {0x9a, 0x80},
        {0xb0, 0x84},
        {0xb1, 0x0c},
        {0xb2, 0x0e},
        {0xb3, 0x82},
        {0xb8, 0x0a},
        {0x43, 0x14},
        {0x44, 0xf0},
        {0x45, 0x34},
        {0x46, 0x58},
        {0x47, 0x28},
        {0x48, 0x3a},
        {0x59, 0x88},
        {0x5a, 0x88},
        {0x5b, 0x44},
        {0x5c, 0x67},
        {0x5d, 0x49},
        {0x5e, 0x0e},
        {0x64, 0x04},
        {0x65, 0x20},
        {0x66, 0x05},
        {0x94, 0x04},
        {0x95, 0x08},
        {0x6c, 0x0a},
        {0x6d, 0x55},
        {0x6e, 0x11},
        {0x6f, 0x9f},//0x9e for advance AWB
        {0x6a, 0x40},
        {0x01, 0x40},
        {0x02, 0x40},
        {0x13, 0xe7},
        {0x15, 0x18},
        {0x4f, 0x80},
        {0x50, 0x80},
        {0x51, 0x00},
        {0x52, 0x22},
        {0x53, 0x5e},
        {0x54, 0x80},
        {0x58, 0x9e},        
        {0x41, 0x08},
        {0x3f, 0x00},
        {0x75, 0x05},
        {0x76, 0xe1},
        {0x4c, 0x00},
        {0x77, 0x01},
        {0x3d, 0xc0},
        {0x4b, 0x09},
        {0xc9, 0x60},
        {0x41, 0x38},
        {0x56, 0x40},        
        {0x34, 0x11},
        {0x3b, 0x02},
        {0xa4, 0x89},
        {0x96, 0x00},
        {0x97, 0x30},
        {0x98, 0x20},
        {0x99, 0x30},
        {0x9a, 0x84},
        {0x9b, 0x29},
        {0x9c, 0x03},
        {0x9d, 0x4c},
        {0x9e, 0x3f},
        {0x78, 0x04},        
        {0x79, 0x01},
        {0xc8, 0xf0},
        {0x79, 0x0f},
        {0xc8, 0x00},
        {0x79, 0x10},
        {0xc8, 0x7e},
        {0x79, 0x0a},
        {0xc8, 0x80},
        {0x79, 0x0b},
        {0xc8, 0x01},
        {0x79, 0x0c},
        {0xc8, 0x0f},
        {0x79, 0x0d},
        {0xc8, 0x20},
        {0x79, 0x09},
        {0xc8, 0x80},
        {0x79, 0x02},
        {0xc8, 0xc0},
        {0x79, 0x03},
        {0xc8, 0x40},
        {0x79, 0x05},
        {0xc8, 0x30},
        {0x79, 0x26},
        {0x09, 0x03},
        {0x55, 0x00},
        {0x56, 0x40},        
        {0x3b, 0x42},
        {0x07, 0x08},
        {0x10, 0x80}	
	
	
/**
  * @brief  config_OV7660_window 
  * @param  //(140,16,640,480) is good for VGA
  *			//(272,16,320,240) is good for QVGA
  * @retval None
 */
//void OV7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height)
//{
//	uint16_t endx=(startx+width);
//	uint16_t endy=(starty+height*2);// must be "height*2"
//	uint8_t temp_reg1, temp_reg2;
//	uint8_t state,temp;
//	
//	state = state;	   //Prevent report warning

//	state = DCMI_SingleRandomRead(0x03, &temp_reg1 );
//	temp_reg1 &= 0xC0;
//	state = DCMI_SingleRandomRead(0x32, &temp_reg2 );
//	temp_reg2 &= 0xC0;
//	
//	// Horizontal
//	temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
//	state = DCMI_SingleRandomWrite(0x32, temp );
//	temp = (startx&0x7F8)>>3;
//	state = DCMI_SingleRandomWrite(0x17, temp );
//	temp = (endx&0x7F8)>>3;
//	state = DCMI_SingleRandomWrite(0x18, temp );
//	
//	// Vertical
//	temp = temp_reg1|((endy&0x7)<<3)|(starty&0x7);
//	state = DCMI_SingleRandomWrite(0x03, temp );
//	temp = (starty&0x7F8)>>3;
//	state = DCMI_SingleRandomWrite(0x19, temp );
//	temp = (endy&0x7F8)>>3;
//	state = DCMI_SingleRandomWrite(0x1A, temp );
//}
 			
  /* fps */
//  {0x6B, 0x4a}, //PLL  x4
//  {0x11, 0x00}, // pre-scalar = 1/1

  /* others */
//  {0x1E, 0x31}, //mirror flip
//  {0x42, 0x08}, // color bar
};	
//typedef struct
//{
//	unsigned short reg;
//	unsigned short val;
//} LCD_TypeDef;

//#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
//#define lcda         ((LCD_TypeDef *) LCD_BASE)

int main(){
	RCC->CR=0x00030083;
	RCC->CFGR=0x001D0400;
	RCC->CFGR=0x061D0402;
	RCC->CR=0x01030083;
	RCC->APB2ENR=0x000001FD;
	RCC->APB1ENR=0x00404000;
	RCC->AHBENR|=0x100;
//	GPIOA->CRH=0x44444444;
//	GPIOA->CRL=0x44444434;
//	GPIOB->CRH=0x44444444;
//	GPIOB->CRL=0x44444444;
//	GPIOD->CRH=0x33444333;
//	GPIOD->CRL=0x44334433;
//	GPIOE->CRH=0x33333333;
//	GPIOE->CRL=0x33333333;
//	GPIOF->CRH=0x44444444;
//	GPIOF->CRL=0x44444443;
//	GPIOG->CRH=0x44434444;
//	GPIOG->CRL=0x44444444;

	GPIOA->CRH=0x4444444b;//mco altpushpull
	GPIOA->CRL=0x44444434;
	GPIOB->CRH=0x4444ff84;
	GPIOB->CRL=0xb4844444;
	GPIOA->BRR=0x100;
	GPIOB->BRR=0x220;
	GPIOD->CRH=0xbb444bbb;
	GPIOD->CRL=0x88bb84bb;
	GPIOD->BRR=0xc8;
	GPIOC->CRL=0x88888888;
	GPIOC->BRR=0x00ff;
	GPIOE->CRH=0xbbbbbbbb;
	GPIOE->CRL=0xb3333388;
	GPIOE->BRR=0x03;
	GPIOF->CRH=0x88888888;
	GPIOF->CRL=0x4444444b;
	GPIOF->BRR=0xff00;
	GPIOG->CRH=0x488b4b84;
	GPIOG->CRL=0x44444444;
	GPIOG->BRR=0x6600;
	FSMC_Bank1->BTCR[6]=0x1010;	//sram bank4
	FSMC_Bank1->BTCR[7]=0x00000202;
	FSMC_Bank1E->BWTR[6]=0x00000202;
	FSMC_Bank1->BTCR[6]|=0x01;
	
	FSMC_Bank1->BTCR[4]=0x1010; //sram bank3
	FSMC_Bank1->BTCR[5]=0x00000202;
	FSMC_Bank1E->BWTR[4]=0x00000202;
	FSMC_Bank1->BTCR[4]|=0x01;

I2C2->CR1|=0x8000;
	I2C2->CR1&=~0x8000;
	I2C2->CCR=0x0168;
//	I2C2->CCR=0x02d;
	I2C2->OAR1=0x0066;
	I2C2->CR2=0x0024;			//freq
	I2C2->CR1=0x0081;			//nostretch pe
	I2C2->TRISE=0x25;		//trise
	AFIO->EXTICR[0]=0x00000044;
	AFIO->EXTICR[2]=0x00000010;
	EXTI->RTSR=0x00000203;
	EXTI->FTSR=0x00000000;
  NVIC->ISER[0]=0x008000c0;							//nvic intrrupt enable
	SCB->AIRCR=0x05fa0000;						//priority group,sub group
	NVIC->IP[6]=0x10;											// priority 
	NVIC->IP[7]=0x00;
	NVIC->IP[23]=0x20;
//	
//	FSMC_Bank1->BTCR[4]=0x30d2;
//	FSMC_Bank1->BTCR[5]=0x0fffffff;
//	FSMC_Bank1E->BWTR[4]=0x0fffffff;
//	FSMC_Bank1->BTCR[2]=0x30d2;
//	FSMC_Bank1->BTCR[3]=0x0fffffff;
//	FSMC_Bank1E->BWTR[2]=0x0fffffff;
//	FSMC_Bank1->BTCR[0]=0x30db;
//	FSMC_Bank1->BTCR[1]=0x0fffffff;
//	FSMC_Bank1E->BWTR[0]=0x0fffffff;	

	GPIOA->BSRR=0x02;
	Systick_setup();	
	device=lcd_init();
//	drawpic(picdata,320,240);Delay_ms(1000);
	ClassCamera cam;
	cam.InitCamera();
//	caminit();
//	windowsize(320,240);
//	cursor(0,0);
//	cam7670_winset(272,16,320,480);	
//	EXTI->IMR=0x000203;
	flag=0;//EXTI->IMR=0x0203;
//	lcd_write(0x012,0x00);
//	lcd_write(0x07,0x0000);
	for(;;){
//		if(flag==1){flag=0;}
		if(flag==2){drawpic1(picdata1,320,240);flag=0;count=0;}
//		drawcam(320,240);
		if(flag==0){
			picdata1[count]=0x0ff0;
			if(count++>3000){flag=2;count=0;}
		}
	}
}

void cam7670_winset(u16 startx, u16 starty, u16 width, u16 height){
	send_cam(0x17,(startx&0x7ff8)>>3);
	send_cam(0x18,((startx+width)&0x7ff8)>>3);
	send_cam(0x32,(((width+startx)&0x07)<<3)|(startx&0x07));

	send_cam(0x19,(starty&0x7ffc)>>2);
	send_cam(0x1a,((starty+(height))&0x7ffc)>>2);
	send_cam(0x03,(((height+starty)&0x03)<<2)|(starty&0x03));
}

void EXTI0_IRQHandler(){	//hor
	if((y++)==20){flag=2;}
	//	cursor(0,y++);lcda->reg=0x22;
//	GPIOC->ODR=0;
//	data=0;
	EXTI->PR = 0x01;
}

void EXTI1_IRQHandler(){	//ver
	y=0;

	EXTI->PR = 0x02;
}

void EXTI9_5_IRQHandler(){	//pix
	if((GPIOE->IDR&0x1)&(flag==0)){
	picdata1[count++]=(unsigned char)GPIOC->IDR;
	}
//	union{
//		struct{
//			unsigned char    :3;
//			unsigned char d3 :1;
//			unsigned char    :2;
//			unsigned char d67:2;
//			unsigned char dum;
//		};
//		unsigned short data;
//	}rd;
//	union{
//		struct{
//			unsigned char dum;
//			unsigned char    :1;
//			unsigned char g910:2;
//			unsigned char    :2;
//			unsigned char g1314 :2;
//			unsigned char    :1;
//		};
//		unsigned short data;
//	}rg;
//	union{
//		struct{
//			unsigned char    :5;
//			unsigned char b5 :1;
//			unsigned char    :2;
//			unsigned char dum;
//		};
//		unsigned short data;
//	}rb;
//	
//	rd.data=GPIOD->IDR;
//	rg.data=GPIOG->IDR;
//	rb.data=GPIOB->IDR;	
//	
//	if(GPIOC->ODR){
//		lcda->val=(GPIOC->ODR)|((rd.d67<<1)|(rd.d3)|(rg.g1314<<5)|(rg.g910<<3)|(rb.b5<<7));	
//		GPIOC->ODR=0;
//	}else{
//		GPIOC->ODR=((rd.d67<<1)|(rd.d3)|(rg.g1314<<5)|(rg.g910<<3)|(rb.b5<<7))<<8;		
//	}
//	if(aaa^=1){
//		data=GPIOC->IDR<<8;
//	}else{
//		lcda->val=(GPIOC->IDR&0xff)|data;
//		data=0;
//	}
	EXTI->PR = 0x200; 
}

void caminit(){
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		unsigned char a=I2C2->SR1;
		I2C2->DR=0x042;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=0x0a;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;		
		I2C2->CR1|=0x200;								//stop
		Delay_us(20);
//	return;	
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		a=I2C2->SR1;
		I2C2->DR=0x043;
		while(!(I2C2->SR1&0x02)){}			//addr
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		while(!(I2C2->SR1&0x40)){}		//rxne
		a=I2C2->DR;
		I2C2->CR1|=0x200;								//stop
		if(a!=0x76) return;
			
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		a=I2C2->SR1;
		I2C2->DR=0x042;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=0x0b;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;		
		I2C2->CR1|=0x200;								//stop
		Delay_us(20);
//	return;	
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		a=I2C2->SR1;
		I2C2->DR=0x043;
		while(!(I2C2->SR1&0x02)){}			//addr
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		while(!(I2C2->SR1&0x40)){}		//rxne
		a=I2C2->DR;
		I2C2->CR1|=0x200;								//stop
		if(a!=0x73) return;
//		while(1){}	
		for(int i=0;i<(sizeof(cam_setup)/sizeof(cam_setup[0]));i++){
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		a=I2C2->SR1;
		I2C2->DR=0x042;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=cam_setup[i][0];
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=cam_setup[i][1];
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;		
		I2C2->CR1|=0x200;								//stop
		Delay_us(20);
	}
}

void windowsize(unsigned short x,unsigned short y){
	unsigned short xx=160-(x/2);
	unsigned short yy=120-(y/2);
	lcd_write(0x50,yy);
	lcd_write(0x51,yy+y-1);
	lcd_write(0x52,xx);
	lcd_write(0x53,xx+x-1);
}

void drawcam(unsigned short x,unsigned short y){
	windowsize(x,y);
	unsigned int data=0;
	unsigned short a=0b0000000011001000;
	unsigned short b=0b0110011000000000;
	unsigned short c=0b0000000000100000;
	unsigned short d=0x07;
	unsigned short e=0x078;
	lcda->reg=0x22;
	for(int i=0;i<(unsigned int)x*y;i++){
	GPIOC->ODR=0x00;
	GPIOC->BSRR=(((a>>2)|a)>>3)&GPIOD->IDR&d;
	GPIOC->BSRR=(((b>>2)|b)>>6)&GPIOG->IDR&e;
	GPIOC->BSRR=((GPIOB->IDR&c)<<2);
	data=GPIOC->ODR<<8;
	GPIOC->ODR=0x00;
	GPIOC->BSRR=(((a>>2)|a)>>3)&GPIOD->IDR&d;
	GPIOC->BSRR=(((b>>2)|b)>>6)&GPIOG->IDR&e;
	GPIOC->BSRR=((GPIOB->IDR&c)<<2);
	data|=(unsigned char)GPIOC->ODR;
	lcda->val=(unsigned short)data;
	}
}

void drawpic1(const unsigned short *picdata,unsigned short x,unsigned short y){
	windowsize(x,y);
	for(int i=0;i<(unsigned int)x*y;i++){
		lcd_write(0x22,*(picdata+i));	
	}
}

void drawpic(const unsigned char *picdata,unsigned short x,unsigned short y){
	windowsize(x,y);
	unsigned short data=0;
	for(int i=0;i<(unsigned int)x*y*2;i++){
		data=(*(picdata+i)|(*(picdata+i+1)<<8));i++;
		lcd_write(0x22,data);	
	}
}

void cursor(unsigned short x,unsigned short y){
	lcd_write(0x20,y);
	lcd_write(0x21,x);
}

void lcd_write(unsigned char reg,unsigned short data){
	lcda->reg=reg;
	lcda->val=data;
}

unsigned short lcd_read(unsigned char reg){

	lcda->reg=reg;
//	GPIOD->CRH=0x44444444;
//	GPIOD->CRL=0x4b334444;
//	GPIOE->CRH=0x44444444;
//	GPIOE->CRL=0x33333333;
//	AFIO->MAPR2&=~0x400;
	reg=lcda->val; 
//	AFIO->MAPR2|=0x400;
//	GPIOD->CRH=0xbb444bbb;
//	GPIOD->CRL=0x4bbb44bb;
//	GPIOE->CRH=0xbbbbbbbb;
//	GPIOE->CRL=0xb3333333;
//	return reg;
	unsigned short a=0b0000000000000011;
	unsigned short b=0b0000000000001100;
	unsigned short c=0b1110000000000000;
	unsigned short d=0b0001111111110000;
	unsigned short e=0b1100011100000011;
	unsigned short f=0b1111111110000000;
	unsigned short temp=GPIOE->ODR;
	GPIOE->ODR=0x00;
	GPIOE->BSRR=((GPIOD->IDR&a)<<2);
	GPIOE->BSRR=((GPIOD->IDR&e)>>14);
	GPIOE->BSRR=(((GPIOD->IDR&e)<<5)&c);
	GPIOE->BSRR=((GPIOE->IDR&f)>>3);
	a=GPIOE->ODR;
	GPIOE->ODR=temp;
	return a;
//	GPIOD->CRH=0xbb444bbb;
//	GPIOD->CRL=0x4bbb44bb;
//	GPIOE->CRH=0xbbbbbbbb;
//	GPIOE->CRL=0xb3333333;
//	return reg;
}

//void lcd_write(unsigned char reg,unsigned short data){
//	lcd_send_init();
//	lcd_data(reg);
//	lcd_wratch();
//	GPIOF->BSRR=(1<<0);	 //rs
//	lcd_data(data);
//	lcd_wratch();
//	GPIOG->BSRR=(1<<12);  //cs
//}

//unsigned short lcd_read(unsigned char reg){
//	lcd_send_init();
//	lcd_data(reg);
//	lcd_wratch();
//	GPIOF->BSRR=(1<<0);	 //rs
//	GPIOD->CRH=0x44444444;
//	GPIOD->CRL=0x44334444;
//	GPIOE->CRH=0x44444444;
//	GPIOE->CRL=0x33333333;
//	GPIOD->BRR=(1<<4);	 //rd-
//	GPIOD->BSRR=(1<<4);	 //rd
//	unsigned short readdata =	lcd_rdata();;
//	GPIOG->BSRR=(1<<12);  //
//	GPIOD->CRH=0x33444333;
//	GPIOD->CRL=0x44334433;
//	GPIOE->CRH=0x33333333;
//	GPIOE->CRL=0x33333333;
//	return readdata;
//}

unsigned short lcd_rdata(){
	unsigned short a=0b0000000000000011;
	unsigned short b=0b0000000000001100;
	unsigned short c=0b1110000000000000;
	unsigned short d=0b0001111111110000;
	unsigned short e=0b1100011100000011;
	unsigned short f=0b1111111110000000;
	unsigned short temp=GPIOE->ODR;
	GPIOE->ODR=0x00;
	GPIOE->BSRR=((GPIOD->IDR&a)<<2);
	GPIOE->BSRR=((GPIOD->IDR&e)>>14);
	GPIOE->BSRR=(((GPIOD->IDR&e)<<5)&c);
	GPIOE->BSRR=((GPIOE->IDR&f)>>3);
	a=GPIOE->ODR;
	GPIOE->ODR=temp;
	return a;
}

void lcd_data(unsigned short data){
	unsigned short a=0b0000000000000011;
	unsigned short b=0b0000000000001100;
	unsigned short c=0b1110000000000000;
	unsigned short d=0b0001111111110000;
	unsigned short e=0b1100011100000011;
	unsigned short f=0b1111111110000000;
	GPIOD->BRR=e;
	GPIOE->BRR=f;
	GPIOD->BSRR=((data&b)>>2);
	GPIOD->BSRR=((data&a)<<14);
	GPIOD->BSRR=((data&c)>>5);
	GPIOE->BSRR=((data&d)<<3);
}

void lcd_wratch(){
	GPIOD->BRR=(1<<5);	 //wr-
	GPIOD->BSRR=(1<<5);	 	 //wr
}

void lcd_send_init(){
	GPIOG->BSRR=(1<<12);  //cs
	GPIOF->BSRR=(1<<0);	  //rs
	GPIOD->BSRR=(1<<5);	  //wr
	GPIOD->BSRR=(1<<4);	  //rd
	
	GPIOG->BRR=(1<<12);  //cs-
	GPIOF->BRR=(1<<0);	 //rs-
}

unsigned short lcd_init(){
	unsigned short code=0;
	Delay_ms(50);
	Delay_ms(50);
	code=lcd_read(0x00);
	if (code!=0x9325) return code;
	lcd_write(0x00,0x01);
	lcd_write(0x01,0x0100);
	lcd_write(0x02,0x0700);
	lcd_write(0x03,0x01038);
	lcd_write(0x04,0x00);
	lcd_write(0x08,0x0202);
	lcd_write(0x09,0x00);
	lcd_write(0x0a,0x00);
	lcd_write(0x0c,0x00);
	lcd_write(0x0d,0x00);
	lcd_write(0x0f,0x00);
	lcd_write(0x010,0x00);
	lcd_write(0x011,0x00);
	lcd_write(0x012,0x00);
	lcd_write(0x013,0x00);
	Delay_ms(50);
	lcd_write(0x010,0x017b0);
	lcd_write(0x011,0x0667);
	Delay_ms(50);
	lcd_write(0x012,0x0138);
	lcd_write(0x02b,0x0d);
	Delay_ms(50);
	lcd_write(0x013,0x01700);
	lcd_write(0x029,0x0d);  //frame
	Delay_ms(50);
	lcd_write(0x020,0x00);
	lcd_write(0x021,0x00);
	lcd_write(0x030,0x01);
	lcd_write(0x031,0x0606);
	lcd_write(0x032,0x0304);
	lcd_write(0x033,0x0202);
	lcd_write(0x034,0x0202);
	lcd_write(0x035,0x0103);
	lcd_write(0x036,0x011d);
	lcd_write(0x037,0x0404);
	lcd_write(0x038,0x0404);
	lcd_write(0x039,0x0404);
	lcd_write(0x03c,0x0700);
	lcd_write(0x03d,0x0a1f);
	lcd_write(0x050,0x00);
	lcd_write(0x051,0x0ef);
	lcd_write(0x052,0x00);
	lcd_write(0x053,0x013f);
	lcd_write(0x060,0x02700); ///
	lcd_write(0x061,0x01);
	lcd_write(0x06a,0x00);
	lcd_write(0x090,0x010);
	lcd_write(0x092,0x00);
	lcd_write(0x093,0x03);
	lcd_write(0x095,0x0101);
	lcd_write(0x097,0x00);
	lcd_write(0x098,0x00);
	lcd_write(0x07,0x021);
	Delay_ms(50);
	lcd_write(0x07,0x031);
	Delay_ms(50);
	lcd_write(0x07,0x0173);
	Delay_ms(50);
	return code;
}
