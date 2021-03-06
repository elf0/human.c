#ifndef TEXTWRITER_H
#define TEXTWRITER_H

//License: Public Domain
//Author: elf
//EMail: elf@iamelf.com

#include "TextFile.h"

//typedef struct{
//    U32 nOffset;
//    U32 nSize;
//}Line;




typedef struct{
    TextFile file;
    U64 nBlockOffset;
    B bModifed;
}TextWriter;

#define OFFSET_ALIGNMENT 16

static inline B TextWriter_NotAligned(U64 nValue){
 return nValue & (OFFSET_ALIGNMENT - 1);
}

static inline U64 TextWriter_Align(U64 nValue){
 return (nValue & ~(OFFSET_ALIGNMENT - 1)) + OFFSET_ALIGNMENT;
}

static inline B TextWriter_Create(TextWriter *pWriter, const C *pszPathName){
    memset(pWriter, 0, sizeof(TextWriter));

    if(!File_CreateForWrite(&pWriter->file.file, pszPathName))
        return false;

    pWriter->file.file.nOffset = sizeof(TextBlock);
    return true;
}

static inline B TextWriter_WriteBlockHeader(TextWriter *pWriter){
    return File_WriteAt(&pWriter->file.file, (const P)&pWriter->file.tbBlock, sizeof(TextBlock), pWriter->nBlockOffset) == sizeof(TextBlock);
}

static inline I32 TextWriter_WriteLine(TextWriter *pWriter, const C *pLine, U32 nSize){
    TextBlock *ptbBlock = &pWriter->file.tbBlock;
    if(TextBlock_Full(ptbBlock)){
        U64 nNextBlockOffset = pWriter->file.file.nOffset;
        if(TextWriter_NotAligned(nNextBlockOffset))
            nNextBlockOffset = TextWriter_Align(nNextBlockOffset);

        ptbBlock->nNext = nNextBlockOffset - pWriter->nBlockOffset;
        ptbBlock->nSum = TextFile_VerifyCode((const P)ptbBlock + 3, (const P)(ptbBlock + 1));
        if(!TextWriter_WriteBlockHeader(pWriter))
            return -TextFile_ErrorCode_WriteHeader;

        memset(ptbBlock, 0, sizeof(TextBlock));
        pWriter->bModifed = false;
        pWriter->nBlockOffset = nNextBlockOffset;
        pWriter->file.file.nOffset = nNextBlockOffset + sizeof(TextBlock);
    }

    if(File_Write(&pWriter->file.file, pLine, nSize) != (I32)nSize)
        return -TextFile_ErrorCode_WriteLine;

    ptbBlock->szLines[ptbBlock->nCount].nSum = TextFile_VerifyCode(pLine, pLine + nSize);
    ptbBlock->szLines[ptbBlock->nCount].nSize = nSize;
    ++ptbBlock->nCount;

    pWriter->bModifed = true;
    return TextFile_ResultCode_Ok;
}

static inline B TextWriter_Close(TextWriter *pWriter){
    if(pWriter->bModifed){
        TextBlock *ptbBlock = &pWriter->file.tbBlock;
        ptbBlock->nSum = TextFile_VerifyCode((const P)ptbBlock + 3, (const P)(ptbBlock + 1));
        if(!TextWriter_WriteBlockHeader(pWriter))
            return false;
    }
    File_Close(&pWriter->file.file);
    return true;
}

#endif // TEXTWRITER_H
