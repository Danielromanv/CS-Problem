#include <iostream>
#include <fstream>
#include <string>

#include "solver.h"

using namespace std;

int main(int args, char **argv)
{
  string input = argv[1];
  std::cout<<input<<std::endl;
  if(args != 1)
  {
    std::cout << "Se ha ingresado una cantidad incorrecta de parámetros" << std::endl;
    return 1;
  }
  Solver solved = Solver();
  solved.Read(input);
  return 0;
}
