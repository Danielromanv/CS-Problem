#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "solver.h"

Solver::Solver()
{
}

int Solver::Read(std::string problema)
{
  this->ruta = problema;
  std::ifstream archivo;
  archivo.open(problema);
  if(!archivo.good()){
    std::cout << "No se pudo leer el archivo" << std::endl;
    return 1;
  }


return 0;
}
