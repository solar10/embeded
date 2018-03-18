#include "cabin_lib.h"

unsigned int Sec=0;

void USART1_IRQHandler(void){
	
}

void SysTick_Handler(void){
 		Sec++;
 }

void Systick_setup(void){
	SysTick->LOAD=8999999;
	SysTick->CTRL=3;
 }

unsigned int Check_ms(void){
 return ((Sec*1000)+((9000000-SysTick->VAL)/9000));
 }

unsigned int Check_us(void){
 return ((Sec*1000000)+((9000000-SysTick->VAL)/9));
 }

void Delay_ms(unsigned int data){
	data=data*9000+(9000000-SysTick->VAL)+Sec*9000000;
	while(((9000000-SysTick->VAL)+Sec*9000000)<=data);
 }

void Delay_us(unsigned int data){
	data=data*9+(9000000-SysTick->VAL)+Sec*9000000;
	while(((9000000-SysTick->VAL)+Sec*9000000)<=data);
 }

void trans_16(vu32 *source,u32 *target,u32 s_mask,u32 t_mask){
	if (t_mask>=s_mask){
		for(char i=0;i<15;i++){
			if((s_mask<<i)==(t_mask)) {*target=((*source&s_mask)<<i)|(*target&=~t_mask);return;}
		}
	}else{
		for(char i=0;i<15;i++){
			if((s_mask>>i)==(t_mask)) {*target=((*source&s_mask)>>i)|(*target&=~t_mask);return;}
		}
	}
} 

void send_cam(u16 reg,u16 data){
		I2C2->CR1|=0x0100;							//start
		while(!(I2C2->SR1&0x01)){}			//sb
		unsigned a=I2C2->SR1;
		I2C2->DR=0x042;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=reg;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;
		I2C2->DR=data;
		while(!(I2C2->SR1&0x80)){}		//txe
		I2C2->SR1&=(~0x400);					//af
		a=I2C2->SR1;
		a=I2C2->SR2;		
		I2C2->CR1|=0x200;								//stop
		Delay_us(20);
}

void Gpio::Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  RCC_DeInit();
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //for I2C
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  GPIO_Write(GPIOC, 0x003F);
  Set(0xFFFF);
}

void Gpio::Pinon(u16 PinNumber)
{
  GPIO_SetBits(GPIOC, PinNumber);
}

void Gpio::Pinoff(u16 PinNumber)
{
  GPIO_ResetBits(GPIOC, PinNumber);
}

void Gpio::Set(u16 value)
{
  GPIO_Write(GPIOA, (value | 0xFF00) & 0xFBFF);
  GPIO_Write(GPIOB, value | 0x00FF);
}

char Gpio::Get(u16 PinNumber)
{
  return GPIO_ReadInputDataBit(GPIOC, PinNumber);
}

void Gpio::Clock(void)
{
  RCC_DeInit();
  
  RCC_HSICmd(ENABLE);//active HSI(internal high speed oscillator)
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  
  RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = 64MHz, AHB
  RCC_PCLK1Config(RCC_HCLK_Div2); //APB1 = 32MHz
  RCC_PCLK2Config(RCC_HCLK_Div1); //APB2 = 64MHz
  
  FLASH_SetLatency(FLASH_Latency_2);
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while (RCC_GetSYSCLKSource() != 0x08);
}

//#ifdef __GNUC__  // With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar()
//	int __io_putchar(int ch)
//	#else
//	int fputc(int ch, FILE *f)
//#endif
//{
//  USART_SendData(EVAL_COM1, (uint8_t) ch);
//  while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
//  {}
//  return ch;
//}