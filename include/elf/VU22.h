#ifndef VU22_H
#define VU22_H

//License: Public Domain
//Author: elf
//EMail: elf@iamelf.com

// Range: [0, 0x3FFFFF]

inline
static U8 VU22_TailBytes(U8 uHead) {
  return uHead & 0x80? ((uHead >> 6) - 1) : 1;
}

inline
static U8 VU22_Bytes(U8 uHead) {
  return uHead & 0x80? (uHead >> 6) : 1;
}

inline
static U8 VU22_NeedBytes(U32 u22) {
  return u22 < 0x80? 1 : u22 < 0x4000? 2 : 3;
}

inline
static U32 VU22_Read(const Byte **ppVU22) {
  const Byte *p = *ppVU22;
  U8 uHead = *p++;
  U32 uValue = uHead;
  if (uHead & 0x80) {
    uValue &= 0x3F;
    if (uHead & 0x40) {
      uValue <<= 8;
      uValue |= *p++;
    }
    uValue <<= 8;
    uValue |= *p++;
  }
  *ppVU22 = p;
  return uValue;
}

inline
static B VU22_Valid(U32 u32) {
  return u32 < 0x400000;
}

inline
static B VU22_Invalid(U32 u32) {
  return u32 > 0x3FFFFF;
}

//u7 must in  range[0, 0x7F]. Check it youself!
inline
static Byte *VU22_FromU7(Byte *pVU22, U8 u7) {
  *pVU22++ = u7;
  return pVU22;
}

inline
static Byte *VU22_FromU8(Byte *pVU22, U8 u8) {
  if (u8 > 0x7F)
    *pVU22++ = 0x80;
  *pVU22++ = u8;
  return pVU22;
}

//u14 must in range[0, 0x3FFF]. Check it youself!
inline
static Byte *VU22_FromU14(Byte *pVU22, U16 u14) {
  if (u14 > 0x7F)
    *pVU22++ = (u14 >> 8) | 0x80;
  *pVU22++ = u14;
  return pVU22;
}

inline
static Byte *VU22_FromU16(Byte *pVU22, U16 u16) {
  if (u16 > 0x7F) {
    if (u16 < 0x4000)
      *pVU22++ = (u16 >> 8) | 0x80;
    else {
      *pVU22++ = 0xC0;
      *pVU22++ = u16 >> 8;
    }
  }
  *pVU22++ = u16;
  return pVU22;
}

//u22 must in range[0, 0x3FFFFF]. Check it youself!
inline
static Byte *VU22_FromU22(Byte *pVU22, U32 u22) {
  if (u22 > 0x7F) {
    if (u22 < 0x4000)
      *pVU22++ = (u22 >> 8) | 0x80;
    else {
      *pVU22++ = (u22 >> 16) | 0xC0;
      *pVU22++ = u22 >> 8;
    }
  }
  *pVU22++ = u22;
  return pVU22;
}

//(pEnd - pBegin) > 0
inline
static Byte *VU22_Sum(Byte *pVU22, const Byte *pBegin, const Byte *pEnd) {
  U32 uSum = *pBegin++;
  while (pBegin != pEnd)
    uSum += *pBegin++;
  if (uSum > 0x7F) {
    if (uSum < 0x4000)
      *pVU22++ = (uSum >> 8) | 0x80;
    else {
      *pVU22++ = (uSum >> 16) | 0xC0;
      *pVU22++ = uSum >> 8;
    }
  }
  *pVU22++ = uSum;
  return pVU22;
}

#endif //VU22_H

