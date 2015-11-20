//
//  kmptool.c
//  KMPTool
//
//  Created by zlh on 11/19/15.
//  Copyright © 2015 zlh. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "kmptool.h"

#define INITSIZE 10
#define SIZEINC 10


static
void reAllKMPRes(KMPRes * res)
{
    
    res->matchPos = (int *)realloc(res->matchPos,
                                   sizeof(int) * (res->matchCapacity + SIZEINC));
    res->matchCapacity += SIZEINC;
    
    if (res->matchPos == NULL)
    {
        fprintf(stderr, "fatal error occur when realloc for KMPRes->matchPos.");
        exit(-1);
    }
    
}

void malKMPRes(KMPRes * res)
{
    if (res == NULL)
    {
        fprintf(stderr, "fatal error occur when malloc for KMPRes->matchPos.");
        exit(-1);
    }
    
    res->matchCount = 0;
    res->matchPos = (int *)malloc(INITSIZE * sizeof(int));
    res->matchCapacity = INITSIZE;
    
    if (res->matchPos == NULL)
    {
        fprintf(stderr, "fatal error occur when mallc for KMPRes->matchPos.");
        exit(-1);
    }
}


void delKMPRes(KMPRes * res)
{
    if (res->matchPos != NULL)
    {
        free(res->matchPos);
    }
}


/************************calculate partial match table********************************/
static void
calculatePartMatTable(int * _partMatTable, unsigned long _lenTable, const char * _partStr)
{
    
    int curTableIdx;    // curTableIdx should be second to last pattern string character
    for (curTableIdx = 1; curTableIdx < _lenTable; curTableIdx++)
    {
        int curPrefixIdx = 0, curSuffixIdx = 1;
        for (; curSuffixIdx <= curTableIdx; curSuffixIdx++)
        {
            
            int prefixBase = curPrefixIdx, suffixBase = curSuffixIdx;
            int count = 0, isMatch = 1;
            while (suffixBase <= curTableIdx)
            {
                if (_partStr[prefixBase] == _partStr[suffixBase])
                {
                    prefixBase ++;
                    suffixBase ++;
                    count ++;
                }
                else
                {
                    isMatch = 0;    // does not match
                    break;
                }
            }
            
            if (isMatch)
            {
                _partMatTable[curTableIdx] = count;
                break;
            }
        }
    }

}
/************************calculate partial match table********************************/


/******************************KMP match algorithm***********************************/
void kmpMatch(KMPRes * res, const char * matchedStr, const char * partStr)
{
    // partical match table of the pattern string
    unsigned long lenPartStr = strlen(partStr);
    unsigned long lenMatchedStr = strlen(matchedStr);
    int *partMatTable = (int *)malloc(lenPartStr * sizeof(int));
    if (partMatTable == NULL)
    {
        fprintf(stderr, "fatal error occur when mallc for partical match table.");
        exit(-1);
    }
    
    /***************calculate the partical match table*********************/
    memset(partMatTable, 0, sizeof(int) * lenPartStr);
    partMatTable[0] = 0;    // # of first character should be 0
    calculatePartMatTable(partMatTable, lenPartStr, partStr);
    /***************calculate the partical match table*********************/
    
    int matBase = 0, matIdx = 0;    // position variable for KMP algorithm
    while (matBase <= (lenMatchedStr - lenPartStr))
    {
        int isMatched = 1;
        for (; matIdx < lenPartStr; matIdx++)
        {
            if (matchedStr[matBase + matIdx] != partStr[matIdx])
            {
                isMatched = 0;
                
                if (matIdx == 0)    // match nothing or match the first character only
                {
                    matBase++;
                    matIdx = 0;
                }
                else
                {
                    matBase += (matIdx - partMatTable[matIdx - 1]);
                    matIdx = partMatTable[matIdx - 1];
                }
                
                break;
            }
        }
        
        if (isMatched == 1)
        {
            
            res->matchPos[res->matchCount++] = matBase;
            if (res->matchCount >= res->matchCapacity)
            {
                reAllKMPRes(res);
            }
            
            matBase += (matIdx - partMatTable[matIdx - 1]);
            matIdx = partMatTable[matIdx - 1];
            
        }
    }
        
    if (partMatTable != NULL)
    {
        free(partMatTable);
    }
}
/******************************KMP match algorithm***********************************/