//
//  DFS_BFS.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/8/30.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//
#include <iostream>
#include <fstream>
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
    map<vector<string>, string> graph;
    map<string, int> visited;
    map<string, string> Distance;
    
    
    void dfs(string v, string desti)
    {
        ofstream ofile;
        ofile.open("/Users/kouruiri/Documents/3Sum/3Sum/output.txt");
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        
        int i = 0;
        string NextPoi;
        multimap<string,string>::iterator it;
        vector<string> sorted;
        it = tree.find(v);
        NextPoi = it -> second;
        visited[v] = 1;
        ofile<<v.c_str() << " " << hops <<endl;
        hops++;

        n = tree.count(NextPoi);
        for (i = 0; i < n; i++) {
            sorted.push_back(it->second);
            it++;
        }
        i = 0;
        if (NextPoi ==  desti) {
            ofile << NextPoi.c_str() << " " << hops << endl;
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
        ofstream ofile;
        ofile.open("/Users/kouruiri/Documents/3Sum/3Sum/output.txt");
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        
        int i = 0;
        string NextPoi;
        multimap<string,string>::iterator it;
        it = tree.find(v);
        vector<string> sorted;
        visited[v] = 1;
        int flag = 0;
        ofile<<v.c_str() << " " << hops <<endl;
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
                    ofile << NextPoi.c_str() << " " << hops << endl;
                    exit(0);
                }

                if (!visited.count(NextPoi))
                {
                    ofile << NextPoi.c_str() << " " << hops << endl;
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
    
    void checkArrive(string NextPoi, string destination, vector<string> *BestRoute,map<string,string> LastRoute, vector<string> OrigStart){
        if (NextPoi == destination) {
            BestRoute->clear();
            BestRoute->push_back(NextPoi);
            cout << "Destination has arrived" << endl;
            while (LastRoute[NextPoi] != OrigStart[0]) {
                BestRoute->push_back(LastRoute[NextPoi]);
                NextPoi = LastRoute[NextPoi];
            }
            BestRoute->push_back(OrigStart[0]);
        }
    }
    
    void UniformSearch(string start, string destination){
        ofstream ofile;
        ofile.open("/Users/kouruiri/Documents/3Sum/3Sum/output.txt");
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        
        int i = 0;
        int i1 = 0;
        int flag = 0;
        
        vector<string> OrigStart;
        vector<string> CurrStart;
        vector<string> BestRoute;
        
        string NextPoi;
        
        map<string,string> LastRoute;
        map<vector<string>, string>::iterator it;
        multimap<string, string>::iterator it1;
        
        vector<vector<string>> queue;
        vector<string> test;
        vector<string> route;
        
        
        it1 = tree.find(start);
        string2int toint = *new string2int();
        
        visited[start] = 1;
        //ofile << start.c_str() << " " << hops << endl;
        OrigStart.push_back(start);
        BestRoute.push_back(destination);
        
        while (!queue.empty() || flag == 0)
        {
            flag ++;
            it1 = tree.find(start);
            n = tree.count(start);
            
            if (n < 3) {
                flag = 0;
            }
            
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
                    checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart);
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
                            checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart);
                            

                        }
                    }
                }

                if (graph.count(OrigStart) == 0 && OrigStart.size() == 2 && OrigStart[0] != OrigStart[1])  {
                    graph.insert(pair<vector<string>, string>(OrigStart,to_string(hops + toint.Toint(it -> second)) ));
                    LastRoute[NextPoi] = start;
                    printf("%s to %s has been updated to \t%d\n", OrigStart[0].c_str(), NextPoi.c_str(), hops + toint.Toint(it -> second));
                    checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart);

                    }
                    
                if (OrigStart.size() == 2) {
                    OrigStart.pop_back();
                }
                    CurrStart.clear();
                

                route.clear();
                //it++;
                it1++;
            }
            sort(queue.begin(), queue.end());
            start = queue[0][1];
            
            CurrStart.push_back(OrigStart[0]);
            CurrStart.push_back(start);
            hops = toint.Toint(graph.find(CurrStart)->second);
            CurrStart.clear();
            if(queue.size() == 0){
                break;
            }
            else{
                queue.erase(queue.begin());
            }
        
        }
        ofile << BestRoute[BestRoute.size() - 1] << " " <<"0" << endl;
        for (i = 2; i < BestRoute.size() + 1; i++) {
             OrigStart.push_back(BestRoute[BestRoute.size() - i]) ;
             ofile << BestRoute[BestRoute.size() - i] << " " <<graph.find(OrigStart)->second << endl;
             OrigStart.pop_back();
        }
       
    }
    
    struct Node{
        Node *parent;
        string f,g,h;
        string name;
    };
    
    void Asearch(string start, string destination){
        ofstream ofile;
        ofile.open("/Users/kouruiri/Documents/3Sum/3Sum/output.txt");
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        
        string2int toint = *new string2int();
        vector<string> Currstart;
        int n = 0, i;
        Node startnode, nextp[1000] ,tmp;
        startnode.g = "0";
        startnode.h = Distance[start];
        startnode.name = start;
        startnode.f = to_string(toint.Toint(startnode.g) + toint.Toint(startnode.h));
        vector<vector<string>> queue;
        map<string,string>::iterator it;
        Currstart.push_back("0");
        Currstart.push_back(start);
        Currstart.push_back("0");
        queue.push_back(Currstart);
        Currstart.clear();
        int k = 0, m = 0;
        int flag = 0;
        
        while (!queue.empty()) {
            if (queue[0][1] == destination) {
                tmp = nextp[toint.Toint(queue[0][2])];
            }
            it = tree.find(queue[0][1]);
            n = tree.count(queue[0][1]);
            
            if (!visited[queue[0][1]]) {
                for (i = m; i < n + m; i++) {
                    Currstart.push_back(queue[0][1]);
                    Currstart.push_back(it -> second);
                    
                    if (flag == 0) {
                        nextp[i].parent = &startnode;
                        
                    }
                    else{
                        nextp[i].parent = &nextp[toint.Toint(queue[0][2])];
                    }
                    nextp[i].h = Distance[it->second];
                    nextp[i].g = to_string(toint.Toint(graph[Currstart]) + toint.Toint(nextp[i].parent->g));
                    nextp[i].f = to_string(toint.Toint(nextp[i].g) + toint.Toint(nextp[i].h));
                    nextp[i].name = it->second;
                    Currstart.clear();
                    
                    Currstart.push_back(nextp[i].f);
                    Currstart.push_back(nextp[i].name);
                    Currstart.push_back(to_string(k));
                    queue.push_back(Currstart);
                    Currstart.clear();
                    k++;
                    it++;
                }
                flag ++;
                visited[queue[0][1]] = 1;
                m = k;

            }
            queue.erase(queue.begin());
            sort(queue.begin(), queue.end());
            
        }
        Currstart.clear();

        queue.clear();

        while (tmp.parent) {
            Currstart.push_back(tmp.name);
            Currstart.push_back(tmp.f);
            tmp = *tmp.parent;
            queue.push_back(Currstart);
            Currstart.clear();
        }
        Currstart.push_back(tmp.name);
        Currstart.push_back(tmp.f);
        queue.push_back(Currstart);
        while (queue.size()) {
            int dis = toint.Toint(queue[queue.size() - 1][1])-toint.Toint(Distance[queue[queue.size() - 1][0]]);
            ofile << queue[queue.size() - 1][0] << " " << dis << endl;
            cout << queue[queue.size() - 1][0] << " " << dis << endl;
            queue.pop_back();
        }
        
    }

};
