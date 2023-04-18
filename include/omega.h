#ifndef OMEGA_H
#define OMEGA_H

#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

#define MAX_IN 1024
#define MAX_ST 14
#define MAX_EX 4

struct PE{

    int n,m;
    int *input;
    int *output;
    int node;

    PE(int n, int m){
        this->n = n;
        this->m = m;
        input = new int[n];
        output = new int[m];
        node = -1;
    }

    void set_pe(int *input, int *output){
        for(int i=0; i<n; i++)
            this->input[i]=input[i];
        
        for(int i=0; i<m; i++)
            this->output[i]=output[i];
    }
};

class Omega{

private:
    int circuit[MAX_IN][MAX_ST];    // estado do circuito 
    int free[MAX_IN][MAX_ST];       // switches livres
    int n, st, ex, radix, L, mask;  // parametros da rede

    vector<vector<int>> inword;
    vector<int> outword;

public:

    Omega(int n=256, int st=4, int ex=1, int radix=4, int mask=255);
    bool route(int input, int output);
    void unroute(int word);
    void dealloc(PE elem);
    void set_omega(int stage, int extra, int in);
    void print_network();
    void clear();
};

#endif