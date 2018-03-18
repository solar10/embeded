#include "util.h"
#include "STM32F10x_usart.h"
#include "cabin_lib.h"
void ClassUtil::Delay(u32 delay)
{
  for (int i=0; i<delay; i++);
}

void ClassUtil::DelayMs(u16 delay)
{
  volatile u16 i,j;
  
  for (; delay>0; delay--)
  {
    for (i=0;i<500;i++)
      for (j=0;j<5;j++);
  }
}

void ClassUtil::SerialSendChar(u8 ch)
{
  if (ch != '\0' && ch != '_')
  {
    while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
    USART_SendData(USART2, ch);
  }
}

void ClassUtil::SerialSendString(u8 *st)
{
  while (*st != '\0' && *st != '_')
  {
    SerialSendChar(*st);
    st++;
  }
}

void ClassUtil::IntToString(u32 IntVal, char *StringVal)
{
  u8 temp, temp2 = 0;
  
  if (IntVal >= 1000000)
  {
    temp = IntVal/1000000;
    temp2 += temp;
    IntVal -= 1000000*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
    
  if (IntVal >= 100000)
  {
    temp = IntVal/100000;
    temp2 += temp;
    IntVal -= 100000*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
    
  if (IntVal >= 10000)
  {
    temp = IntVal/10000;
    temp2 += temp;
    IntVal -= 10000*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
    
  if (IntVal >= 1000)
  {
    temp = IntVal/1000;
    temp2 += temp;
    IntVal -= 1000*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
      
  if (IntVal >= 100)
  {
    temp = IntVal/100;
    temp2 += temp;
    IntVal -= 100*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
      
  if (IntVal >= 10)
  {
    temp = IntVal/10;
    temp2 += temp;
    IntVal -= 10*temp;
    *StringVal = temp+0x30; StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
      
  if (IntVal > 0)
  {
    *StringVal = IntVal+0x30; StringVal++;
  }
  else
  {
    if (IntVal==0)
    {
      *StringVal = '0'; StringVal++;
    }
  }
  *StringVal = '_';
}

void ClassUtil::ShortToString(u16 IntVal, char *StringVal)
{
  u8 temp = 0, temp2 = 0;
  
  if (IntVal >= 100)
  {
    temp = IntVal/100;
    IntVal -= 100*temp;
    temp2 += temp;
    *StringVal = temp+0x30; 
    StringVal++;
  }
  else
  {
    if (temp2>0)
    {
      *StringVal = '0'; 
      StringVal++;
    }
  }
    
  if (IntVal >= 10)
  {
    temp = IntVal/10;
    IntVal -= 10*temp;
    temp2 += temp;
    *StringVal = temp+0x30; 
    StringVal++;
  }
  else
  {
    if (temp2>0 || temp==0)
    {
      *StringVal = '0'; 
      StringVal++;
    }
  }
  
  if (IntVal > 0)
  {
    *StringVal = IntVal+0x30;
    StringVal++;
  }
  else
  {
    *StringVal = '0'; 
    StringVal++;
  }
  *StringVal = '_';
}

void ClassUtil::HundredToString(u16 IntVal, char *StringVal)
{
  u8 temp = 0, temp2 = 0;
  
  if (IntVal >= 100)
  {
    temp = IntVal/100;
    IntVal -= 100*temp;
    temp2 += temp;
    *StringVal = temp+0x30; 
    StringVal++;
  }
  else
  {
    if (temp2>0 || temp==0)
    {
      *StringVal = '0'; 
      StringVal++;
    }
  }
    
  if (IntVal >= 10)
  {
    temp = IntVal/10;
    IntVal -= 10*temp;
    temp2 += temp;
    *StringVal = temp+0x30; 
    StringVal++;
  }
  else
  {
    if (temp2>0 || temp==0)
    {
      *StringVal = '0'; 
      StringVal++;
    }
  }
  
  if (IntVal > 0)
  {
    *StringVal = IntVal+0x30;
    StringVal++;
  }
  else
  {
    *StringVal = '0'; 
    StringVal++;
  }
  *StringVal = '_';
}

u32 ClassUtil::GetAverage(u16 val[200])
{
  u32 iSum = 0;
  for (int i=0;i<200;i++)
    iSum += val[i];
  
  return iSum / 200;
}

u32 ClassUtil::GetStandardDeviation(u32 avg, u16 val[200])
{
  u32 Sqare = 0;
  
  for (int i=0;i<200;i++)
    Sqare = (val[i] - avg)^2;
  
  return Sqare / 200;
}

void ClassUtil::TrimData(u32 avg, u32 variation, u16 val[200])
{
  for (int i=0; i<200; i++)
  {
    if ((u32)val[i]-avg  > variation)
      val[i] = (u16)avg;
    else if ((u32)val[i]-avg  > variation)
      val[i] = (u16)avg;
  }
}

u32 ClassUtil::GetMemorySector(u8 WeekDay)
{
  u32 MemorySector;
  
  switch(WeekDay)
  {
  case 1 : //sunday
    MemorySector = 0;
    break;
  case 2 : //monday
    MemorySector = 0x10000;
    break;
  case 3 :
    MemorySector = 0x20000;
    break;
  case 4 :
    MemorySector = 0x30000;
    break;
  case 5 :
    MemorySector = 0x40000;
    break;
  case 6 :
    MemorySector = 0x50000;
    break;
  case 7 :
    MemorySector = 0x60000;
    break;
  default :
    MemorySector = 0;
    break;
  }
  return MemorySector;
}

void ClassUtil::AllocCharToPointer(char *val, char *pointer)
{
  while (*val != '_')
  {
    *pointer = *val;
    
    pointer++;
    val++;
  }
  
  *pointer = '_';
}
