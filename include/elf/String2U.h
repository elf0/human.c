#ifndef STRING2U_H
#define STRING2U_H

//License: Public Domain
//Author: elf
//EMail: elf@elf0.org

//String to unsigned integer

//From 'pBegin' to 'pEnd' MUST be a valid U32 number.
static inline U32 String_ToU32(const Char *pBegin, const Char *pEnd);

//From 'pBegin' to 'pEnd' MUST be a valid U64 number.
static inline U64 String_ToU64(const Char *pBegin, const Char *pEnd);

static inline Bool String_ParseU8(const Char **ppszNumber, U8 *puValue);
static inline Bool String_ParseU16(const Char **ppszNumber, U16 *puValue);
static inline Bool String_ParseU32(const Char **ppszNumber, U32 *puValue);
static inline Bool String_ParseU64(const Char **ppszNumber, U64 *puValue);

//Parse '0b' prefix youself
static inline Bool String_ParseBinaryU32(const Char **ppszNumber, U32 *puValue);
static inline Bool String_ParseBinaryU64(const Char **ppszNumber, U64 *puValue);

//Parse '0o' prefix youself
static inline Bool String_ParseOctalU32(const Char **ppszNumber, U32 *puValue);
static inline Bool String_ParseOctalU64(const Char **ppszNumber, U64 *puValue);

//Parse '0x' prefix youself
static inline Bool String_ParseHexU32(const Char **ppszNumber, U32 *puValue);
static inline Bool String_ParseHexU64(const Char **ppszNumber, U64 *puValue);
static inline Bool String_ParseUHexU64(const Char **ppszNumber, U64 *puValue);

static inline Bool String_ParseIp(const Char **ppIp, U32 *puIp);
////////////////////////////////////////////////////////////////
static inline U32 String_ToU32(const Char *pBegin, const Char *pEnd){
    const Char *p = pBegin;
    U32 uValue = *p++ - '0';

    while(p != pEnd)
        uValue = 10 * uValue + (*p++ - '0');

    return uValue;
}

static inline U64 String_ToU64(const Char *pBegin, const Char *pEnd){
    const Char *p = pBegin;
    U64 uValue = *p++ - '0';

    while(p != pEnd)
        uValue = 10 * uValue + (*p++ - '0');


    return uValue;
}

static inline Bool String_ParseU8(const Char **ppszNumber, U8 *puValue){
    const Char *p = *ppszNumber;
    U8 uValue = *puValue;
    //Max: 255
#define U8_OVERFLOW_BEFORE_MUL 25U
#define U8_OVERFLOW_BEFORE_ADD 250U

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 9)
            break;


        if(uValue < U8_OVERFLOW_BEFORE_MUL)
            uValue = uValue * 10 + uRange;
        else if(uValue > U8_OVERFLOW_BEFORE_MUL || uRange > 5){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }else
            uValue = U8_OVERFLOW_BEFORE_ADD + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseU16(const Char **ppszNumber, U16 *puValue){
    const Char *p = *ppszNumber;
    U16 uValue = *puValue;
    //Max: 65535
#define U16_OVERFLOW_BEFORE_MUL 6553U
#define U16_OVERFLOW_BEFORE_ADD 65530U

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 9)
            break;


        if(uValue < U16_OVERFLOW_BEFORE_MUL)
            uValue = uValue * 10 + uRange;
        else if(uValue > U16_OVERFLOW_BEFORE_MUL || uRange > 5){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }else
            uValue = U16_OVERFLOW_BEFORE_ADD + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseU32(const Char **ppszNumber, U32 *puValue){
    const Char *p = *ppszNumber;
    U32 uValue = *puValue;
    //Max: 4294967295
#define U32_OVERFLOW_BEFORE_MUL 429496729U
#define U32_OVERFLOW_BEFORE_ADD 4294967290U

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 9)
            break;


        if(uValue < U32_OVERFLOW_BEFORE_MUL)
            uValue = uValue * 10 + uRange;
        else if(uValue > U32_OVERFLOW_BEFORE_MUL || uRange > 5){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }else
            uValue = U32_OVERFLOW_BEFORE_ADD + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseU64(const Char **ppszNumber, U64 *puValue){
    const Char *p = *ppszNumber;
    U64 uValue = *puValue;

    //Max: 18446744073709551615
#define U64_OVERFLOW_BEFORE_MUL 1844674407370955161LLU
#define U64_OVERFLOW_BEFORE_ADD 18446744073709551610LLU

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 9)
            break;

        if(uValue < U64_OVERFLOW_BEFORE_MUL)
            uValue = uValue * 10 + uRange;
        else if(uValue > U64_OVERFLOW_BEFORE_MUL || uRange > 5){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }else
            uValue = U64_OVERFLOW_BEFORE_ADD + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

#define I32_MIN 0x80000000
#define I64_MIN 0x8000000000000000LL

static inline Bool String_ParseBinaryU32(const Char **ppszNumber, U32 *puValue){
    const Char *p = *ppszNumber;
    U32 uValue = *puValue;
    //Max: 0b11111111111111111111111111111111
#define BINARY_U32_OVERFLOW_BEFORE_MUL 0x7FFFFFFFU

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 1)
            break;

        if(uValue > BINARY_U32_OVERFLOW_BEFORE_MUL){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }

        uValue = (uValue << 1) + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseBinaryU64(const Char **ppszNumber, U64 *puValue){
    const Char *p = *ppszNumber;
    U64 uValue = *puValue;
    //Max: 0b1111111111111111111111111111111111111111111111111111111111111111
#define BINARY_U64_OVERFLOW_BEFORE_MUL 0x7FFFFFFFFFFFFFFFLLU

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 1)
            break;

        if(uValue > BINARY_U64_OVERFLOW_BEFORE_MUL){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }

        uValue = (uValue << 1) + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseOctalU32(const Char **ppszNumber, U32 *puValue){
    const Char *p = *ppszNumber;
    U32 uValue = *puValue;
    //Max: 0o37777777777
#define OCTAL_U32_OVERFLOW_BEFORE_MUL 03777777777U

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 7)
            break;

        if(uValue > OCTAL_U32_OVERFLOW_BEFORE_MUL){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }

        uValue = (uValue << 3) + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

static inline Bool String_ParseOctalU64(const Char **ppszNumber, U64 *puValue){
    const Char *p = *ppszNumber;
    U64 uValue = *puValue;
    //Max: 0o1777777777777777777777
#define OCTAL_U64_OVERFLOW_BEFORE_MUL 0177777777777777777777LLU

    while(true){
        U8 uRange = *p - (Char)'0';
        if(uRange > 7)
            break;

        if(uValue > OCTAL_U64_OVERFLOW_BEFORE_MUL){
            *ppszNumber = p;
            *puValue = uValue;
            return true;
        }

        uValue = (uValue << 3) + uRange;

        ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return false;
}

//Max: 0xFFFFFFFF
#define HEX_U32_OVERFLOW_BEFORE_MUL 0xFFFFFFFU

static inline Bool String_ParseHexU32(const Char **ppszNumber, U32 *puValue){
    const Char *p = *ppszNumber;
    U32 uValue = *puValue;
    Bool bOverflow = false;
    U8 uRange;
    while(true){
      uRange = *p - (Char)'0';
      if(uRange < 10){
        if(uValue > HEX_U32_OVERFLOW_BEFORE_MUL){
          bOverflow = true;
          break;
        }
        else
          uValue = uValue << 4 | uRange;
      }
      else{
        uRange -= 17;
        if(uRange < 6){
          if(uValue > HEX_U32_OVERFLOW_BEFORE_MUL){
            bOverflow = true;
            break;
          }
          else
            uValue = uValue << 4 | (uRange + 10);
        }
        else{
          uRange -= 32;
          if(uRange > 5)
            break;

          if(uValue > HEX_U32_OVERFLOW_BEFORE_MUL){
            bOverflow = true;
            break;
          }
          else
            uValue = uValue << 4 | (uRange + 10);
        }
      }

      ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return bOverflow;
}

//Max: 0xFFFFFFFFFFFFFFFF
#define HEX_U64_OVERFLOW_BEFORE_MUL 0xFFFFFFFFFFFFFFFLLU

static inline Bool String_ParseHexU64(const Char **ppszNumber, U64 *puValue){
    const Char *p = *ppszNumber;
    U64 uValue = *puValue;
    Bool bOverflow = false;
    U8 uRange;
    while(true){
      uRange = *p - (Char)'0';
      if(uRange < 10){
        if(uValue > HEX_U64_OVERFLOW_BEFORE_MUL){
          bOverflow = true;
          break;
        }
        else
          uValue = uValue << 4 | uRange;
      }
      else{
        uRange -= 17;
        if(uRange < 6){
          if(uValue > HEX_U64_OVERFLOW_BEFORE_MUL){
            bOverflow = true;
            break;
          }
          else
            uValue = uValue << 4 | (uRange + 10);
        }
        else{
          uRange -= 32;
          if(uRange > 5)
            break;

          if(uValue > HEX_U64_OVERFLOW_BEFORE_MUL){
            bOverflow = true;
            break;
          }
          else
            uValue = uValue << 4 | (uRange + 10);
        }
      }

      ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return bOverflow;
}

static inline Bool String_ParseUHexU64(const Char **ppszNumber, U64 *puValue){
    const Char *p = *ppszNumber;
    U64 uValue = *puValue;
    Bool bOverflow = false;
    U8 uRange;
    while(true){
      uRange = *p - (Char)'0';
      if(uRange < 10){
        if(uValue > HEX_U64_OVERFLOW_BEFORE_MUL){
          bOverflow = true;
          break;
        }
        else
          uValue = uValue << 4 | uRange;
      }
      else{
        uRange -= 17;
        if(uRange > 5)
          break;

        if(uValue > HEX_U64_OVERFLOW_BEFORE_MUL){
          bOverflow = true;
          break;
        }
        else
          uValue = uValue << 4 | (uRange + 10);
      }

      ++p;
    }

    *ppszNumber = p;
    *puValue = uValue;
    return bOverflow;
}

static inline Bool String_ParseIp(const Char **ppIp, U32 *puIp){
    const Char *p = *ppIp;

    if(!Char_IsDigit(*p))
        return false;

    union{
        U32 uIp;
        U8 szIp[4];
    }ip;

    if(String_ParseU8(&p, &ip.szIp[0])){
        *ppIp = p;
        return false;
    }

    if(*p != '.'){
        *ppIp = p;
        return false;
    }
    ++p;

    if(!Char_IsDigit(*p)){
        *ppIp = p;
        return false;
    }

    if(String_ParseU8(&p, &ip.szIp[1])){
        *ppIp = p;
        return false;
    }

    if(*p != '.'){
        *ppIp = p;
        return false;
    }
    ++p;

    if(!Char_IsDigit(*p)){
        *ppIp = p;
        return false;
    }

    if(String_ParseU8(&p, &ip.szIp[2])){
        *ppIp = p;
        return false;
    }

    if(*p != '.'){
        *ppIp = p;
        return false;
    }
    ++p;

    if(!Char_IsDigit(*p)){
        *ppIp = p;
        return false;
    }

    if(String_ParseU8(&p, &ip.szIp[3])){
        *ppIp = p;
        return false;
    }

    *ppIp = p;
    *puIp = ip.uIp;
    return true;
}

#endif // STRING2U_H