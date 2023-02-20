#ifndef OMEGA_H
#define OMEGA_H

#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

#define MAX_IN 1024
#define MAX_ST 14
#define MAX_EX 4

class Omega{

private:
    char circuit[MAX_IN][MAX_ST];   // estado do circuito 
    int free[MAX_IN][MAX_ST];       // switches livres
    int n, st, ex, radix, L, mask;  // parametros da rede 

public:

    Omega(int n=256, int st=4, int ex=1, int radix=4, int mask=255);
    bool route(int input, int output);
    void setOmega(int stage, int extra, int in);
    void clear();
};

#endif