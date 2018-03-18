#include "ov7670.h"
#include "stm32f10x_conf.h"
#include "cabin_lib.h"
#include "util.h"
void ClassCamera::InitCamera(void)
{

  send_cam(REG_COM7, 0x80); // reset to default values 
  send_cam(REG_CLKRC, 0x80); //clk
  send_cam(REG_COM11, 0x0A);
  send_cam(REG_TSLB, 0x04);
  send_cam(REG_TSLB, 0x04);
  send_cam(REG_COM7, 0x04); // output format: rgb 

  send_cam(REG_RGB444, 0x00); // disable RGB444 
  send_cam(REG_COM15, 0xD0); // set RGB565 

  // not even sure what all these do, gonna check the oscilloscope and go
  // from there... 
  send_cam(REG_HSTART, 0x16);
  send_cam(REG_HSTOP, 0x04);
  send_cam(REG_HREF, 0x24);
  send_cam(REG_VSTART, 0x02);
  send_cam(REG_VSTOP, 0x7a);
  send_cam(REG_VREF, 0x0a);
  send_cam(REG_COM10, 0x02);
  send_cam(REG_COM3, 0x04);
  send_cam(REG_MVFP, 0x3f);

  // 160x120, i think 
  //send_cam(REG_COM14, 0x1a); // divide by 4
  //send_cam(0x72, 0x22); // downsample by 4
  //send_cam(0x73, 0xf2); // divide by 4

  // 320x240: 
  send_cam(REG_COM14, 0x19);
  send_cam(0x72, 0x11);
  send_cam(0x73, 0xf1);

  // test pattern
  //send_cam(0x70, 0xf0);
  //send_cam(0x71, 0xf0);

  // COLOR SETTING
  send_cam(0x4f, 0x80);
  send_cam(0x50, 0x80);
  send_cam(0x51, 0x00);
  send_cam(0x52, 0x22);
  send_cam(0x53, 0x5e);
  send_cam(0x54, 0x80);
  send_cam(0x56, 0x40);
  send_cam(0x58, 0x9e);
  send_cam(0x59, 0x88);
  send_cam(0x5a, 0x88);
  send_cam(0x5b, 0x44);
  send_cam(0x5c, 0x67);
  send_cam(0x5d, 0x49);
  send_cam(0x5e, 0x0e);
  send_cam(0x69, 0x00);
  send_cam(0x6a, 0x40);
  send_cam(0x6b, 0x0a); //pll
  send_cam(0x6c, 0x0a);
  send_cam(0x6d, 0x55);
  send_cam(0x6e, 0x11);
  send_cam(0x6f, 0x9f);

  send_cam(0xb0, 0x84);//*/
}

void ClassCamera::Capture(void)
{  
  while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)); //wait for an old frame to end
  while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)); //wait for a new frame to start
  GPIO_ResetBits(GPIOA, GPIO_Pin_10); //enable writing to fifo
  while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)) //wait for the current frame to end
  GPIO_SetBits(GPIOA, GPIO_Pin_10); //disable writing to fifo
}

void ClassCamera::CameraRRST(void)
{
  ClassUtil util;
  GPIO_ResetBits(GPIOA, GPIO_Pin_9); //RRST bit
  util.Delay(10000);
  GPIO_SetBits(GPIOA, GPIO_Pin_11); //RCK
  util.Delay(10000);
  GPIO_SetBits(GPIOA, GPIO_Pin_9); //RRST bit
  GPIO_ResetBits(GPIOA, GPIO_Pin_11); //RCK
}

u8 ClassCamera::GetCameraPixel(void)
{
  u8 val;
  GPIO_SetBits(GPIOA, GPIO_Pin_11); //RCK
  val = (u8)(GPIO_ReadInputData(GPIOC) >> 8);
  GPIO_ResetBits(GPIOA, GPIO_Pin_11); //RCK
  return val;
}