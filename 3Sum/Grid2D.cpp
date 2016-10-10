//
//  Grid2D.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//

#include "Grid2D.hpp"
using namespace std;
class Grid2D{
public:
    int numIslands(vector<vector<char>>& grid) {
        int i = 0;
        int length = grid[0].size();
        int height = 0;
        while(grid[height][i] != '1'){
            i++;
            if (i > length) {
                i = 0;
                height++;
            }
        }
        
        return 0;
        
    }
};