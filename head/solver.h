#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>
#include "solver.h"

bool check(std::vector<int> v);

class Solver{
public:
    std::string ruta;
    int autos;
    int opciones;
    int clases;
    std::vector<int> maxopt;
    std::vector<int> blocksize;
    std::vector<std::vector<int>> autoclase;
    std::vector<std::vector<int>> claseop;
    std::vector<int> dominio;

    Solver();
    int Read(std::string problema);
    void Solve(std::string token);
    std::vector<int> BT(std::vector<int>& c,std::vector<int>& act,std::vector<int>& bestres,int best,int index,int start);
    int eval(std::vector<int> &v);
    };
#endif
