//
//  main.cpp
//  KMPTool
//
//  Created by zlh on 11/19/15.
//  Copyright © 2015 zlh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "kmptool.h"

using std::cout;
using std::endl;

int main(int argc, const char * argv[])
{

    KMPRes res;    // declare a match result valuable
    malKMPRes(&res);    // initlize this result
    
    char str[100] = "BBC ABAAABABCDABD ABABACADAABCDABDE  AABACDAABAD";
    char m[10] = "ABA";
    kmpMatch(&res, str, m);

    cout << str << endl;
    for (int i = 0; i < res.matchCount; i++)    // res.matchCount maintain # of matched position
    {
        for (int j = 0; j < res.matchPos[i]; j++)    // res.matchPos maintain matched position
        {
            cout << " ";
        }
        cout << m << endl;
    }
    
    delKMPRes(&res);    // recycle the memory for res.matchPos
    return 0;
}
