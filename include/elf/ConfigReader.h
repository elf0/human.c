#ifndef CONFIGREADER_H
#define CONFIGREADER_H

//License: Public Domain
//Author: elf
//EMail: elf@elf0.org

//Buffer must ends with ":\n"
//Line: "Key:Value\n"

#include "String.h"

typedef E8 (*ConfigReader_Handler)(void *pContext, const C *pKey, const C *pKeyEnd, const C *pValue, const C *pValueEnd);

static inline E8 ConfigReader_Parse(void *pContext, const C *pBegin, const C *pEnd, ConfigReader_Handler onKV){
  size_t nSize = pEnd - pBegin;
  if(nSize < 2)
    return 1;

  const C *pEnd0 = &pEnd[-2];
  const C *pEnd1 = &pEnd[-1];
  if(*pEnd0 != 0x3A || *pEnd1 != 0x0A)
    return 1;

  E8 err;
  const C *pKey, *pKeyEnd;
  const C *pValue;
  const C *p = pBegin;
  while(true){
    pKeyEnd = String_SkipUntil(pKey = p, 0x3A);
    p = String_SkipUntil(pValue = pKeyEnd + 1, 0x0A);
    if(p == pEnd1)
      break;

    err = onKV(pContext, pKey, pKeyEnd, pValue, p++);
    if(err)
      return err;
  }

  return 0;
}

#endif // CONFIGREADER_H
