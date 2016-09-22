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
    unsigned long n;
    int hops = 0;
    multimap<string, string> tree;
    map<vector<string>, string> graph;
    map<string, int> visited;
    map<string, int> seen;
    map<string, string> Distance;

    bool checkArrive(string NextPoi, string destination, vector<string> *BestRoute,map<string,string> LastRoute, vector<string> OrigStart){
        if (NextPoi == destination) {
            BestRoute->clear();
            BestRoute->push_back(NextPoi);
            while (LastRoute[NextPoi] != OrigStart[0]) {
                BestRoute->push_back(LastRoute[NextPoi]);
                NextPoi = LastRoute[NextPoi];
            }
            BestRoute->push_back(OrigStart[0]);
            return true;
        }
        return false;
    }
    
    static bool mysort(vector<string> & m1, vector<string> & m2) {
        string2int toint = *new string2int();
        int a,b;
        a = toint.Toint(m1[0]);
        b = toint.Toint(m2[0]);
        if (a == b){
            a = toint.Toint(m1[1]);
            b = toint.Toint(m2[1]);
            return m1[1] < m2[1];
        }
        return a < b;
        
    }
    struct Node{
        Node *parent;
        int hops;
        int poi;
        string f,g,h;
        string name;
    };
    
    Node node[10000];
    
    
    int dfs(string v, string desti,int times)
    {
        ofstream ofile;
        string filepath = "/Users/kouruiri/Documents/3Sum/3Sum/Output/output";
        filepath.append(to_string(times));
        filepath.append(".txt");
        if(hops == 0){
            ofile.open(filepath);
        }
        else{
            ofile.open(filepath,ios::app);
        }
        
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        node[hops].name = v;
        if(node[hops].parent){
            node[hops].hops = node[hops].parent->hops + 1;
        }
        else{
            node[hops].hops = 0;
        }
        int i = 0;
        string NextPoi;
        multimap<string,string>::iterator it;
        vector<string> sorted;
        it = tree.find(v);
        visited[v] = 1;
        seen[v] = 1;
       
        n = tree.count(v);
        if (n == 0){
            ofile.clear();
        }
        for (i = 0; i < n; i++) {
            seen[it->second] += 1;
            if(seen[it->second] > 1){
                
            }
            else{
                sorted.push_back(it->second);
            }
            
            if (it->second ==  desti && seen[it->second] == 1) {
                int k = 1;
                int q[100];
                string sub[100];
                sub[0] = it -> second;
                q[0] = node[hops].hops + 1;
                while (node[hops].parent) {
                    sub[k] = node[hops].name;
                    q[k] = node[hops].hops;
                    node[hops] = *node[hops].parent;
                    k++;
                }
                k--;
                ofile << node[0].name << " " << node[0].hops <<endl;
                while (k >= 0) {
                    ofile << sub[k] << " " << q[k]<<endl;
                    k--;

                }
                
                return 0;
            }
            it++;
        }
        i = 0;
   //     sort(sorted.begin(),sorted.end());
        if (n > 0) {
            int a = hops;
            
            while(i < sorted.size()) {
                hops++;
                node[hops].parent = &node[a];
                NextPoi = sorted[i];
                if (!visited.count(NextPoi)){
                    int k = dfs(NextPoi,desti,times);
                    if(k == 0){
                        return 0;
                    }
                    }
                i++;
            }
        }

            return 1;
        
        
    }

    int bfs(string v, string desti,int times)
    {
        visited.clear();
        hops = 0;
        int k = 1;
        ofstream ofile;
        string filepath = "/Users/kouruiri/Documents/3Sum/3Sum/Output/output";
        filepath.append(to_string(times));
        filepath.append(".txt");
        ofile.open(filepath);
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        int i = 0;
        Node newhead;
        multimap<string,string>::iterator it;
        it = tree.find(v);
        vector<Node> sorted;
        visited[v] = 1;
        node[0].name = v.c_str();
        node[0].hops = hops;
        node[0].poi = 0;
        hops++;
        sorted.push_back(node[0]);
        while (!sorted.empty())
        {

            newhead = sorted[0];
            sorted.erase(sorted.begin());
            it = tree.find(newhead.name);
            n = tree.count(newhead.name);
            for (i = 0; i < n; i++) {
                node[k].poi = k;
                node[k].name = it->second;
                node[k].hops = node[newhead.poi].hops + 1;
                node[k].parent = &node[newhead.poi];
                string Nextpoi = it->second;
                if(it->second == desti){
                    int m = 0;
                    int q[100];
                    string sub[100];
                    while (node[k].parent) {
                        sub[m] = node[k].name;
                        q[m] = node[k].hops;
                        node[k] = *node[k].parent;
                        m++;
                    }
                    m--;
                    ofile << node[0].name << " " << node[0].hops <<endl;
                    while (m >= 0) {
                        ofile << sub[m] << " " << q[m]<<endl;
                        m--;
                        
                    }
                    return 1;
                }
                if (!visited.count(it->second))
                {
                    sorted.push_back(node[k]);
                    visited[it->second] = true;
                }
                k++;
                it++;
            }
//            sort(sorted.begin(),sorted.end(),[](const Node &m1,const Node &m2){return m1.name[0] < m2.name[0];});

        }
        
        ofile.close();
        
        return 1;
    }

    
    void UniformSearch(string start, string destination,int times){
        ofstream ofile;
        visited.clear();
        hops = 0;
        
        int i = 0;
        int step = 0;
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
        OrigStart.push_back(start);
        BestRoute.push_back(destination);
        string filepath = "/Users/kouruiri/Documents/3Sum/3Sum/Output/output";
        filepath.append(to_string(times));
        filepath.append(".txt");
        
        while (!queue.empty() || flag == 0)
        {
            int change = 0;
            flag ++;
            it1 = tree.find(start);
            n = tree.count(start);
            
            if (n < 3) {
                flag = 0;
            }
            step++;
            for (i = 0; i < n ; i++){
                NextPoi = it1 -> second;
                
                if (CurrStart.size() == 0) {
                    CurrStart.push_back(start);
                }
                
                if (!visited.count(NextPoi))
                {
                    
        
                    OrigStart.push_back(NextPoi);
                    CurrStart.push_back(NextPoi);
                   
                    LastRoute[NextPoi] = start;
                    visited[NextPoi] = true;
                    
                    if (checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart)&&graph.count(OrigStart) ){
                        
                        ofile.open(filepath,ios::trunc);
                        ofile << BestRoute[BestRoute.size() - 1] << " " <<"0" << endl;
                        OrigStart.pop_back();
                        for (int k = 2; k < BestRoute.size() + 1; k++) {
                            OrigStart.push_back(BestRoute[BestRoute.size() - k]) ;
                            ofile << BestRoute[BestRoute.size() - k] << " " <<graph.find(OrigStart)->second << endl;
                            OrigStart.pop_back();
                        }
                        ofile.close();
                    }

                }

                else if (visited.count(NextPoi) && NextPoi != OrigStart[0]){
                    OrigStart.push_back(NextPoi);
                    CurrStart.push_back(NextPoi);
                    
                        if(toint.Toint(graph.find(OrigStart)->second)  > (hops + toint.Toint(graph.find(CurrStart)->second) )){
                            change = 1;
                            
                            graph[OrigStart] = to_string(hops + toint.Toint(graph[CurrStart]));
                            LastRoute[NextPoi] = start;
                            if (checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart)){
                                ofile.open(filepath,ios::trunc);
                                ofile << BestRoute[BestRoute.size() - 1] << " " <<"0" << endl;
                                OrigStart.pop_back();
                                for (int k = 2; k < BestRoute.size() + 1; k++) {
                                    OrigStart.push_back(BestRoute[BestRoute.size() - k]) ;
                                    ofile << BestRoute[BestRoute.size() - k] << " " <<graph.find(OrigStart)->second << endl;
                                    OrigStart.pop_back();
                                }
                                ofile.close();
                            }

                        }
                }

                if (graph.count(OrigStart) == 0 && OrigStart.size() == 2 && OrigStart[0] != OrigStart[1])  {
                    graph[OrigStart] = to_string(hops + toint.Toint(graph[CurrStart]));
                    change = 1;
                    LastRoute[NextPoi] = start;
                    if (checkArrive(NextPoi, destination, &BestRoute, LastRoute, OrigStart)){
                        ofile.open(filepath,ios::trunc);
                        ofile << BestRoute[BestRoute.size() - 1] << " " <<"0" << endl;
                        OrigStart.pop_back();
                        for (int k = 2; k < BestRoute.size() + 1; k++) {
                            OrigStart.push_back(BestRoute[BestRoute.size() - k]) ;
                            ofile << BestRoute[BestRoute.size() - k] << " " <<graph.find(OrigStart)->second << endl;
                            OrigStart.pop_back();
                        }
                    ofile.close();

                    }
                    
                }
                if(OrigStart.size() > 1 ){
                    if (visited[OrigStart[1]] == 1 || change == 1) {
                        it = graph.find(OrigStart);
                        test.push_back(it->second);
                        test.push_back(to_string(step));
                        test.push_back(it->first[1]);
                        queue.push_back(test);
                        test.clear();
                        visited[OrigStart[1]]++;
                        change = 0;
                    }
                    
                }
                
                
                if (OrigStart.size() == 2) {
                    OrigStart.pop_back();
                }
                    CurrStart.clear();
                

                route.clear();
                it1++;
            }
            sort(queue.begin(), queue.end(),this->mysort);
            
            
            if(queue.size() == 0){
                break;
            }
            else{
                //OrigStart.push_back(OrigStart[0]);
                start = queue[0][2];
                OrigStart.push_back(start);
                hops = toint.Toint(graph.find(OrigStart)->second);
                OrigStart.pop_back();
                queue.erase(queue.begin());
            }
        
        }
       
    }
    
    
    void Asearch(string start, string destination,int times){
        visited.clear();
        ofstream ofile;
        string filepath = "/Users/kouruiri/Documents/3Sum/3Sum/Output/output";
        filepath.append(to_string(times));
        filepath.append(".txt");
        ofile.open(filepath);
        if (! ofile.is_open())
        { cout << "Error opening file"; exit (1); }
        
        
        string2int toint = *new string2int();
        vector<string> Currstart;
        unsigned long n = 0, i;
        Node startnode, nextp[50000],tmp;
        memset(nextp, 0,sizeof(Node)*50000);
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
                break;
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
            sort(queue.begin(), queue.end(), mysort );
            
        }
        Currstart.clear();
        tmp = nextp[toint.Toint(queue[0][2])];
        queue.clear();

        while (tmp.parent != NULL) {
            if (tree.count(tmp.parent->name) != 0){
                Currstart.push_back(tmp.name);
                Currstart.push_back(tmp.f);
                
                tmp = *tmp.parent;
                queue.push_back(Currstart);
                Currstart.clear();

            }
            else{
                break;
            }
        }
        Currstart.push_back(tmp.name);
        Currstart.push_back(tmp.f);
        queue.push_back(Currstart);
        while (queue.size()) {
            int dis = toint.Toint(queue[queue.size() - 1][1])-toint.Toint(Distance[queue[queue.size() - 1][0]]);
            ofile << queue[queue.size() - 1][0] << " " << dis << endl;
            queue.pop_back();
        }
        
    }

};
