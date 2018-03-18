#ifndef UTIL_H_
#define UTIL_H_

#include "cabin_lib.h"

class ClassUtil
{
private:
  
public:
  void Delay(u32 delay);
  void DelayMs(u16 delay);
  void SerialSendChar(u8 ch);
  void SerialSendString(u8 *st);
  void SendSerialNumeric(u16 val, u8 div, u8 str[32]);
  void IntToString(u32 IntVal, char *StringVal);
  void ShortToString(u16 IntVal, char *StringVal);
  void HundredToString(u16 IntVal, char *StringVal);
  u32 GetAverage(u16 val[200]);
  u32 GetStandardDeviation(u32 avg, u16 val[200]);
  void TrimData(u32 avg, u32 variation, u16 val[200]);
  u32 GetMemorySector(u8 WeekDay);
  void AllocCharToPointer(char *val, char *pointer);
};

#endif