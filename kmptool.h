//
//  kmptool.h
//  KMPTool
//
//  Created by zlh on 11/19/15.
//  Copyright © 2015 zlh. All rights reserved.
//

#ifndef kmptool_h
#define kmptool_h

typedef struct
{
    
    int matchCount;    // the match position count
    
    int *matchPos;    // the match positions in matched string
    
    int matchCapacity;    // maintained by the code
    
}KMPRes;

void malKMPRes(KMPRes * res);    // apply memory for KMPRes

// matchedStr is the string will be matched, partStr is the pattern string
void kmpMatch(KMPRes * res, const char * matchedStr, const char * partStr);

void delKMPRes(KMPRes * res);    // delete memory of KMPRes

#endif /* kmptool_h */
