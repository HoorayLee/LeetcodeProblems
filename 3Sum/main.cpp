//
//  main.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//

//#include "Grid2D.cpp"
//#include "Grid2D.hpp"
#include "3Sum.cpp"
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
//    vector<int> A = {14,-11,-2,-3,4,-3,-3,-8,-15,11,11,-6,-14,-13,5,-10,-13,0,-12,-8,14,-12,-10,2,-4,9,13,10,2,7,-2,-7,4,11,5,-7,-15,10,-7,-14,6,11,-5,7,6,8,5,8,-7,8,-15,14,11,13,1,-15,7,0,10,-14,14,-15,-14,3,4,6,4,4,-7,12,5,14,0,8,7,13,1,-11,-2,9,12,-1,8,0,-11,-5,0,11,2,-13,4,1,-12,5,-10,-1,-12,9,-12,-11,-2,9,-12,5,-6,2,4,10,6,-13,4,3,-7,-11,11,-3,-9,-4,-15,8,-9,-4,-13,-14,8,14};
//    vector<vector<int>> SolutionSet = Solute.threeSum(A);


    
    //////////////////////////
    //  DFS & BFS Algorithm //
    //////////////////////////
    char buffer[5];
    string il;
    string cost;
    vector<string> place;
    string Numroute;
    int Numberoute;
    int i = 0;
    SearchTree Dsearch = *new SearchTree();
    ifstream iinfo;
    ofstream ofile;
    info Info = *new info();
    string2int toint = *new string2int();
    
    iinfo.open("/Users/kouruiri/Documents/3Sum/3Sum/input.txt");
    if (! iinfo.is_open())
    { cout << "Error opening file"; exit (1); }
    
    iinfo.getline(buffer, 10);

   
    
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
    while (!iinfo.eof()) {
        char a = iinfo.get();
        if (a == '\n') {
            break;
        }
        else{
            
            Numroute.push_back(a);
        }
        
    }
    Numberoute = toint.Toint(Numroute);
    
    //////////////////////////////////////////////////////////
    //     Read the Begin Point and the Desination  <End>   //
    //////////////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////////////
    //      Read the intersection information  <Head>       //
    //////////////////////////////////////////////////////////
    int flag = 0;
    
    while (!iinfo.eof() && i != Numberoute)
    {
        
        char a = iinfo.get();
        if(a != ' ' && a != '\n' && flag < 2){
            il.push_back(a);
            
        }
        
        else if (47 < a && a< 58 && flag == 2){
            cost.push_back(a);
        }

        else if (a == '\n') {
            if (place.size() == 2) {
                Dsearch.tree.insert(pair<string, string>(place[0],place[1]));
                Dsearch.tree.insert(pair<string, string>(place[1],place[0]));
                Dsearch.graph[place] = cost;

                place.push_back(place[0]);
                place.erase(place.begin());
                if (!Dsearch.graph.count(place)) {
                    Dsearch.graph[place] =  cost;
                    
                }

                il.clear();
                place.clear();
                cost.clear();
                flag = 0;
                i++;
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
    //////////////////////////////////////////////////////////
    //      Read the intersection information  <End>        //
    //////////////////////////////////////////////////////////
    flag = 0;
    Numroute.clear();
    while (!iinfo.eof()) {
        char a = iinfo.get();
        if (a == '\n') {
            break;
        }
        else{
            
            Numroute.push_back(a);
        }
        
    }
    Numberoute = toint.Toint(Numroute);
    
    while (!iinfo.eof() && i != Numberoute){
        
        char a = iinfo.get();
        if(a != ' ' && a != '\n' && flag < 1){
            il.push_back(a);
            
        }
        
        else if (47 < a && a< 58 && flag == 1){
            cost.push_back(a);
        }
        
        else if (a == '\n') {
                Dsearch.Distance[il] = cost;
                il.clear();
                place.clear();
                cost.clear();
                flag = 0;
            
        }
        else if (a == ' '){
            
                flag++;
            
        }
        
    }

    if (il.size()) {
        Dsearch.Distance[il] = cost;
        il.clear();
        place.clear();
        cost.clear();
        
    }
    iinfo.close();
    if (Info.beginpoi == Info.desti) {
        ofile.open("/Users/kouruiri/Documents/3Sum/3Sum/output.txt");
        ofile << Info.desti << " 0" << endl;
        ofile.close();
        exit(0);
    }

    
    if (buffer[0] == 'D') {
        cout << "result for dfs:" << endl;
        cout << "From" << Info.beginpoi << endl;
        cout << "To" << Info.desti << endl;
        Dsearch.dfs(Info.beginpoi,Info.desti);
    }
    else if(buffer[0] == 'B'){
        cout << "result for bfs:" << endl;
        cout << "From" << Info.beginpoi << endl;
        cout << "To" << Info.desti << endl;
        Dsearch.bfs(Info.beginpoi,Info.desti);
    }
    else if (buffer[0] == 'U'){
        cout << "result for Uniform Search:" << endl;
        cout << "From" << Info.beginpoi << endl;
        cout << "To" << Info.desti << endl;
        Dsearch.UniformSearch(Info.beginpoi,Info.desti);
    }
    else if (buffer[0] == 'A'){
        cout << "result for A* Search:" << endl;
        cout << "From" << Info.beginpoi << endl;
        cout << "To" << Info.desti << endl;
        Dsearch.Asearch(Info.beginpoi, Info.desti);
    }

    
    return 0;
    
}
