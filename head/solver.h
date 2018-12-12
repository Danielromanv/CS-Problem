#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "solver.h"

class Solver{
public:
    std::string ruta;
    int autos;
    int opciones;
    int clases;
    std::vector<int> maxopt;
    std::vector<int> blocksize;
    std::vector<std::vector<int>> autoclase;

    Solver();
    int Read(std::string problema);
    int Solve();
    std::vector<int> BT(std::vector<int>& c,std::vector<int>& act, int inicio /*int best*/);


};
#endif
