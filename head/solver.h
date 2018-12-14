#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <limits>
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
    std::vector<int> dominio;

    Solver();
    int Read(std::string problema);
    int Solve();
    std::vector<int> BT(std::vector<int>& c,std::vector<int>& act,int best,int inicio);
    int eval(std::vector<int> &v);

};
#endif
