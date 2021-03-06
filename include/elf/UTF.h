#ifndef UTF_H
#define UTF_H

//License: Public Domain
//Author: elf
//EMail: elf@iamelf.com

#include "UTF8.h"
#include "UTF16.h"

#define UTF_IsHan(c) (c >= 0x4E00 && c < 0xA000)

//Out buffer bytes should >= 2 * In buffer bytes;
//caller must input valid utf-16 string
static inline C *UTF_16To8(C16 *p16Begin, C16 *p16End, C *p8Buffer){
 C32 value;
 C16 *p16 = p16Begin;
 C *p8 = p8Buffer;
 while(p16 != p16End){
  p16 = UTF16_GetValue(p16, &value);
  p8 = UTF_To8(value, p8);
 }
 return p8;
}

//Out buffer bytes should >= 2 * In buffer bytes;
//caller must input valid utf-8 string
static inline C16 *UTF_8To16(C *p8Begin, C *p8End, C16 *p16Buffer){
 C32 value;
 C *p8 = p8Begin;
 C16 *p16 = p16Buffer;
 while(p8 != p8End){
  p8 = UTF8_GetValue(p8, &value);
  p16 = UTF_To16(value, p16);
 }

 return p16;
}

#endif //UTF_H
