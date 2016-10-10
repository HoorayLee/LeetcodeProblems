//
//  main.cpp
//  missingrange
//
//  Created by 洪锐 李 on 10/9/16.
//  Copyright © 2016 洪锐 李. All rights reserved.
//
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        string tmp;
        vector<string> final;
        vector<int> range;
        vector<vector<int>> result;
        int i;
        if(lower < nums[0]){
            range.push_back(lower);
            if(lower + 2 < nums[0]){
                range.push_back(nums[0] - 1);
            }
        }
        result.push_back(range);
        range.clear();
        for (i = 0; i < nums.size() - 1; i++){
            if(nums[i] + 1 < nums[i + 1]){
                range.push_back(nums[i] + 1);
                if(nums[i] + 2 < nums[i + 1] ){
                    range.push_back(nums[i + 1] - 1);
                }
            }
            result.push_back(range);
            range.clear();
        }
        
        for(i = 0; i < result.size(); i++){
            if(result[i].size() == 1){
                final.push_back(to_string(result[i][0]));
            }
            else{
                tmp = to_string(result[i][0]) + "->" + to_string(result[i][1]);
                final.push_back(tmp);
            }
        }
        
        return final;
    }
};
int main(int argc, const char * argv[]) {
    Solution solut = *new Solution();
    vector<int> nums = {0,1,3,50,75};
    int lower = 0;
    int high = 99;
    vector <string> shit = solut.findMissingRanges(nums,lower,high);
    cout << shit[0];
    return 0;
}
