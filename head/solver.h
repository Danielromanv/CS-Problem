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
    std::vector<int> maxauto;
    std::vector<int> maxtam;
    std::vector<std::vector<int> > autoclase;

    Solver();
    int Read(std::string problema);

};
#endif
