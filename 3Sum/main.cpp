//
//  main.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//

//#include "Grid2D.cpp"
//#include "Grid2D.hpp"
//#include "3Sum.cpp"
#include "DFS_BFS.cpp"
#include <fstream>
//#include "Add2Int.cpp"

using namespace std;



class info{
    public:
    string beginpoi;
    string desti;
};


int main(int argc, const char * argv[]) {
    
    //3 Sum Question
//    Solution Solute = *new Solution();
//    vector<int> A = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
//    vector<vector<int>> SolutionSet = Solute.threeSum(A);
//

    
    //////////////////////////
    //  DFS & BFS Algorithm //
    //////////////////////////
    char buffer[100];
    string il;
    string cost;
    vector<string> place;
    SearchTree Dsearch = *new SearchTree();
    ifstream iinfo;
    info Info = *new info();
    
    iinfo.open("/Users/kouruiri/Documents/3Sum/3Sum/input1.txt");
    if (! iinfo.is_open())
    { cout << "Error opening file"; exit (1); }
    
    iinfo.getline(buffer, 50);

   
    
    //////////////////////////////////////////////////////////
    //    Read the Begin Point and the Desination  <Head>   //
    //////////////////////////////////////////////////////////
    
    while (!iinfo.eof()) {
        char a = iinfo.get();
        if (a == '\n') {
            break;
        }
        else{
            Info.beginpoi.push_back(a);
        }
    }
    while (!iinfo.eof()) {
        char a = iinfo.get();
        if (a == '\n') {
            break;
        }
        else{
            Info.desti.push_back(a);
        }
    }
    //////////////////////////////////////////////////////////
    //     Read the Begin Point and the Desination  <End>   //
    //////////////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////////////
    //      Read the intersection information  <Head>       //
    //////////////////////////////////////////////////////////
    int flag = 0;
    
    while (!iinfo.eof() )
    {
        
        char a = iinfo.get();
        if(a != ' ' && a != '\n' &&( a < 48 || a > 57)){
            il.push_back(a);
            
        }
        
        else if (48 < a && a< 57){
            cost.push_back(a);
            flag++;
        }

        else if (a == '\n') {
            if (place.size()) {
                Dsearch.graph.insert(pair<vector<string>,string>(place, cost) );
                Dsearch.tree.insert(pair<string, string>(place[0],place[1]));
                il.clear();
                place.clear();
                cost.clear();
                flag = 0;
            }
            
        }
        else if (a == ' ' && flag != 2){
            if (il.size() ) {
                place.push_back(il);
                il.clear();
                flag++;
            }
            
        }
        
    }
    
    if (place.size()) {
            Dsearch.graph.insert(pair<vector<string>,string>(place, cost) );
            Dsearch.tree.insert(pair<string, string>(place[0],place[1]));
            il.clear();
            place.clear();
            cost.clear();

    }
    //sort(Dsearch.graph.begin(), Dsearch.graph.end());
    //////////////////////////////////////////////////////////
    //      Read the intersection information  <End>        //
    //////////////////////////////////////////////////////////
    
    
    if (buffer[0] == 'D') {
        cout << "result for dfs:" << endl;
        cout << Info.beginpoi << endl;
        cout << Info.desti << endl;
        Dsearch.dfs(Info.beginpoi,Info.desti);
    }
    else if(buffer[0] == 'B'){
        cout << "result for dfs:" << endl;
        cout << Info.beginpoi << endl;
        cout << Info.desti << endl;
        Dsearch.bfs(Info.beginpoi,Info.desti);
    }
    else if (buffer[0] == 'U'){
        cout << "result for dfs:" << endl;
        cout << Info.beginpoi << endl;
        cout << Info.desti << endl;
        Dsearch.UniformSearch(Info.beginpoi,Info.desti);
    }
    else{
        cout << Info.beginpoi << endl;
        cout << Info.desti << endl;
    }

    
    return 0;
    
}
