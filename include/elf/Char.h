#ifndef CHAR_H
#define CHAR_H
//License: Public Domain
//Author: elf
//EMail: elf198012@gmail.com

#include "Type.h"

#define CASE_CHAR_UPPER \
     case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': \
     case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': \
     case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': \
     case 'Y': case 'Z'
#define CASE_CHAR_LOWER \
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': \
    case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': \
    case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': \
    case 'y': case 'z'

#define CASE_CHAR_DIGIT \
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': \
    case '8': case '9'

static inline Bool Char_IsUpper(Char c){
    return c >= 'A' && c <= 'Z';
}

static inline Bool Char_IsLower(Char c){
    return c >= 'a' && c <= 'z';
}

#endif // CHAR_H
