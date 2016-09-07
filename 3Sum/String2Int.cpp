//
//  String2Int.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/9/1.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//
#include "Grid2D.hpp"
#include <math.h>
using namespace std;

class string2int{
public:
    int Toint(string a){
        int num = 0;
        int k = a.length();
        int i = 0;
        while (a[i] != '\0') {
            num += (a[i] - 48) * pow(10,a.length() - i - 1);
            i++;
        }
        
        return num;
    }
};