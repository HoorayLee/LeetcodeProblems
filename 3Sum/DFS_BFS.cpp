//
//  DFS_BFS.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include "Grid2D.hpp"
#include <queue>
#include "String2Int.cpp"
using namespace std;

class SearchTree{
public:
    int n;
    int hops = 0;
    multimap<string, string> tree;
    multimap<vector<string>, string> graph;
    map<string, int> visited;

    void dfs(string v, string desti)
    {
        int i = 0;
        string NextPoi;
        multimap<string,string>::iterator it;
        vector<string> sorted;
        it = tree.find(v);
        NextPoi = it -> second;
        visited[v] = 1;
        printf("%s\t\t%d\n", v.c_str(), hops);
        hops++;

        n = tree.count(NextPoi);
        for (i = 0; i < n; i++) {
            sorted.push_back(it->second);
            it++;
        }
        i = 0;
        if (NextPoi ==  desti) {
            printf("%s\t%d",NextPoi.c_str(),hops);
            exit(0);
        }
        sort(sorted.begin(),sorted.end());
        if (n > 0) {
            for (; i < n; i++) {
                NextPoi = sorted[i];
                if (!visited.count(NextPoi)){
                        dfs(NextPoi,desti);
                    }
                it++;
            }
        }
        
    }

    void bfs(string v, string desti)
    {
        int i = 0;
        string NextPoi;
        multimap<string,string>::iterator it;
        it = tree.find(v);
        vector<string> sorted;
        visited[v] = 1;
        int flag = 0;
        printf("%s\t\t%d\n", v.c_str(), hops);
        hops++;
        queue<string> t;
        t.push(v);
        while (!t.empty())
        {
            sorted.clear();
            v = t.front();
            t.pop();
            it = tree.find(v);
            n = tree.count(v);
            for (i = 0; i < n; i++) {
                sorted.push_back(it->second);
                it++;
            }
            i = 0;
            it = tree.find(v);
            sort(sorted.begin(),sorted.end());
            

            for (i = 0; i < n ; i++){
                 NextPoi = sorted[i];
                if(NextPoi == desti){
                    printf("%s\t\t%d\n", NextPoi.c_str(), hops);
                    exit(0);
                }

                if (!visited.count(NextPoi))
                {
                    printf("%s\t\t%d\n", NextPoi.c_str(), hops);
                    t.push(NextPoi);
                    visited[NextPoi] = true;
                    flag++;
                }
                it++;
            }
            if (flag) {
                hops++;
                flag = 0;
            }
            

        }
    }
    
    void UniformSearch(string start, string destination){
        int i = 0;
        int i1 = 0;
        int flag = 0;
        
        vector<string> OrigStart;
        vector<string> CurrStart;
        vector<string> BestRoute;
        
        string NextPoi;
        
        map<string,string> LastRoute;
        multimap<vector<string>, string>::iterator it;
        multimap<string, string>::iterator it1;
        
        vector<vector<string>> queue;
        vector<string> test;
        vector<string> route;
        
        
        it1 = tree.find(start);
        string2int toint = *new string2int();
        
        visited[start] = 1;
        printf("%s\t%d\n", start.c_str(), hops);
        OrigStart.push_back(start);
        BestRoute.push_back(destination);
        
        while (!queue.empty() || flag == 0)
        {
            flag ++;
            it1 = tree.find(start);
            n = tree.count(start);
            for (i = 0; i < n ; i++){
                NextPoi = it1 -> second;
                
                if (CurrStart.size() == 0) {
                    CurrStart.push_back(start);
                }
                
                if (!visited.count(NextPoi))
                {
                    
                    route.push_back(it1->first);
                    route.push_back(it1->second);
                    it = graph.find(route);
                    test.push_back(it->second);
                    test.push_back(it->first[1]);
                    
                    queue.push_back(test);
                    OrigStart.push_back(NextPoi);
                    test.clear();
                    LastRoute[NextPoi] = start;
                    visited[NextPoi] = true;
                }

                else if (visited.count(NextPoi) && NextPoi != OrigStart[0]){
                    OrigStart.push_back(NextPoi);
                    CurrStart.push_back(NextPoi);
                    if (graph.count(CurrStart)) {
                        if(toint.Toint(graph.find(OrigStart)->second)  > (hops + toint.Toint(graph.find(CurrStart)->second) )){
                            graph.find(OrigStart)->second = to_string(hops + toint.Toint(graph.find(CurrStart)->second) );
                            for ( ;i1 < queue.size(); i1++) {
                                if (queue[i1][1] == CurrStart[1]) {
                                    queue[i1][0] = graph.find(OrigStart)->second;
                                }
                            }
                            i1 = 0;
                            LastRoute[NextPoi] = start;
                            printf("%s to %s has been updated to \t%d\n", OrigStart[0].c_str(), NextPoi.c_str(), hops + toint.Toint(graph.find(CurrStart)->second));
                        }
                    }
                }

                if (graph.count(OrigStart) == 0 && OrigStart.size() == 2 && OrigStart[0] != OrigStart[1])  {
                    graph.insert(pair<vector<string>, string>(OrigStart,to_string(hops + toint.Toint(it -> second)) ));
                    LastRoute[NextPoi] = start;
                    printf("%s to %s has been updated to \t%d\n", OrigStart[0].c_str(), NextPoi.c_str(), hops + toint.Toint(it -> second));
                    }
                    
                if (OrigStart.size() == 2) {
                    OrigStart.pop_back();
                }
                    CurrStart.clear();
                

                route.clear();
                it++;
                it1++;
            }
            sort(queue.begin(), queue.end());
            start = queue[0][1];
            if (start == destination) {
                cout << "Destination has arrived" << endl;
                while (LastRoute[start] != OrigStart[0]) {
                    BestRoute.push_back(LastRoute[start]);
                    start = LastRoute[start];
                }
                BestRoute.push_back(OrigStart[0]);
                
                break;
            }
            
            CurrStart.push_back(OrigStart[0]);
            CurrStart.push_back(start);
            hops = toint.Toint(graph.find(CurrStart)->second);
            CurrStart.clear();
            queue.erase(queue.begin());
        }
        cout << BestRoute[BestRoute.size() - 1] << "\t\t" <<"0" << endl;
        for (i = 2; i < BestRoute.size() + 1; i++) {
             OrigStart.push_back(BestRoute[BestRoute.size() - i]) ;
             cout << BestRoute[BestRoute.size() - i] << "\t\t" <<graph.find(OrigStart)->second << endl;
             OrigStart.pop_back();
        }
       
    }

};
