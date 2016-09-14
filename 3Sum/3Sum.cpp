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
        int i = 0;
        if(Example.size() == 0){
            return true;
        }
        
        while( i < Example.size()&& Example[i][0] < nums[0])
        {
            i++;
        }
        
        for(; i < Example.size(); i++){
            if(Example[i][0] > nums[0]){
                break;
            }
            else if (Example[i][0] == nums[0] &&Example[i][1] == nums[1]) {
                return false;
            }
            
        }
        
        
        
        return true;
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> SolutionSet;
        vector<int> Solution;
        int sum;
        int m = 0;
        int flag1 = 0;
        int flag = 0;
        int i = 0;
        int k = nums.size() - 1;
        
        map<int, int> Newmap;
        if(nums.size() < 3){
            return SolutionSet;
        }
        sort(nums.begin(), nums.end());
        for (i = 0; i < nums.size(); i++) {
            Newmap[nums[i]] += 1;
        }
        i = 0;
        while (nums[i] <= 0) {
            while(k > i + 1){
                sum = nums[i] + nums[k];
                if (-sum == nums[i] && -sum == nums[k]) {
                    if (Newmap[-sum] > 2) {
                        flag = 0;
                    }
                    else{
                        flag++;
                    }
                }
                else if(-sum == nums[i] || -sum == nums[k]){
                    if (Newmap[-sum] > 1) {
                        flag = 0;
                    }
                    else{
                        flag++;
                    }
                    
                }
                if (Newmap.count(-sum) && flag == 0) {
                    Solution.push_back(nums[i]);
                    Solution.push_back(nums[k]);
                    if(-sum < nums[i]){
                        Solution.insert(Solution.begin(),-sum);
                    }
                    else if(-sum > nums[k]){
                        Solution.insert(Solution.end(),-sum);
                    }
                    else{
                        Solution.insert(Solution.begin() + 1, -sum);
                    }
                    if (SolutionSet.size() == 0) {
                        SolutionSet.push_back(Solution);
                    }
                    else{
//                        while( m < SolutionSet.size() && SolutionSet[i][0] < Solution[0])
//                        {
//                            m++;
//                        }
//                        
                        for(m = 0; m < SolutionSet.size(); m++){
                            if (SolutionSet[m][1] == Solution[1] && SolutionSet[m][0] == Solution[0]) {
                                flag1 = 1;
                            }
                        }
                        
                        if(flag1 == 0){
                            SolutionSet.push_back(Solution);
                        }
                        flag1 = 0;
                        m = 0;
                    }
                    
                    Solution.clear();
                }
                k--;
                flag = 0;
            }
            k = nums.size() - 1;
            i++;
        }
        

        //        for(i = 0; i < nums.size(); i++){
//            for(k = i + 1; k < nums.size(); k++){
//
//                Solution.push_back(nums[i]);
//                Solution.push_back(nums[k]);
//                Solution.push_back(i);
//                Solution.push_back(k);
//                Newmap.insert(pair<int, vector<int>>(-(nums[i] + nums[k]),Solution));
//                Solution.clear();
//            }
//        }
//        int tmp = 0;
//        
//        for(i = 0; i < nums.size(); i++){
//            tmp = Newmap.count(nums[i]);
//            multimap<int,vector<int>>::iterator m;
//            if (tmp != 0) {
//                m = Newmap.find(nums[i]);
//                int a = 0;
//                while (a < tmp) {
//                    if (m ->second[2] != i && m->second[3] != i) {
//                        m->second.resize(3);
//                        m->second[2] = nums[i];
//                        if(CheckSet(SolutionSet, m->second)){
//                            SolutionSet.push_back(m->second);
//                        }
//                    }
//                    m++;
//                    a++;
//                }
//                Newmap.erase(nums[i]);
//            }
//        }
        
        return SolutionSet;
    }
};
