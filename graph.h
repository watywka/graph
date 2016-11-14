#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class graph
{
    private:
        int* matrix;
        int n;
    public:
        graph();
        graph(int n, int* mat);
        ~graph();
        int get_n();
        void gen_dag(int n);
        void get_next(int k,set<int>* visited, set<int>* out);
        int path(int start, int cur,set<int>* visited, vector<int>* out);

};

void search(int n, int* a,vector<int>* out);

void gen(int n, int p, int* a);

void shuf(int n, int* a);

#endif
