#ifndef cabin_lib_H
#define cabin_lib_H

#include "RTE_Components.h"
#include "RTE_Device.h"
#include "stm32f10x_conf.h"

//#ifdef __GNUC__  // With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar()
//	int __io_putchar(int ch);
//	#else
//	int fputc(int ch, FILE *f);
//#endif

typedef unsigned int  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef volatile unsigned int  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

void Systick_setup(void);
void USART1_IRQHandler(void);
unsigned int Check_ms(void);
unsigned int Check_us(void);
void Delay_ms(unsigned int data);
void Delay_us(unsigned int data);
void trans_16(vu32 *source,u32 *target,u32 s_mask,u32 t_mask);
void send_cam(u16 reg,u16 data);

class Gpio
{
private:
  
public:
  void Init(void);
  void Clock(void);
  void Pinon(u16 PinNumber);
  void Pinoff(u16 PinNumber);
  char Get(u16 PinNumber);
  void Set(u16 value);
};

class I2c
{
private:

public:
  void Loopcnt(u16 MaxValue);
  void Init(void);
  void Setcamreg(u8 addr, u8 val);
  u16 GetTCN75(u8 addr);
  u8 GetCamera(u8 addr);
};

#endif