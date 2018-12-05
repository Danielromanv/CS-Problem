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
    int maxauto;
    int maxtam;
    int autoclase;

    Solver();
    int Read(std::string problema);

};
#endif
