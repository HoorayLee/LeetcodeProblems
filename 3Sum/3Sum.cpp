//
//  3Sum.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//

#include <stdio.h>
#include "Grid2D.cpp"
class Solution{
public:
    bool CheckSet(vector<vector<int>> &Example, vector<int>& nums){
        sort(nums.begin(), nums.end());
        sort(Example.begin(), Example.end());
        int flag = 0;
        vector<int> Nums;
        for(int i = 0; i< 3; i++){
            Nums.push_back(nums[i]);
        }
        
        if(Example.size() == 0){
            return true;
        }
        for(int i = 0; i < Example.size(); i++){
            for(int k = 0; k < 3; k++){
                if (Example[i][k] == nums[k]) {
                    flag++;
                }
            }
            if(flag == 3){
                return false;
            }
            
            flag = 0;
        }
        
        
        return true;
        
        
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> SolutionSet;
        vector<int> Solution;
        int i = 0;
        int k = 0;
        
        multimap<int, vector<int>> Newmap;
        for(i = 0; i < nums.size(); i++){
            for(k = i + 1; k < nums.size(); k++){
                
                Solution.push_back(nums[i]);
                Solution.push_back(nums[k]);
                Solution.push_back(i);
                Solution.push_back(k);
                Newmap.insert(pair<int, vector<int>>(-(nums[i] + nums[k]),Solution));
                Solution.clear();
            }
        }
        int tmp = 0;
        
        for(i = 0; i < nums.size(); i++){
            tmp = Newmap.count(nums[i]);
            multimap<int,vector<int>>::iterator m;
            if (tmp != 0) {
                m = Newmap.find(nums[i]);
                int a = 0;
                while (a < tmp) {
                    if (m ->second[2] != i && m->second[3] != i) {
                        m->second.resize(3);
                        m->second[2] = nums[i];
                        if(CheckSet(SolutionSet, m->second)){
                            SolutionSet.push_back(m->second);
                        }
                    }
                    m++;
                    a++;
                }
                Newmap.erase(nums[i]);
            }
        }
        
        return SolutionSet;
    }
};
