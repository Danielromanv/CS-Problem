#include <iostream>
#include <fstream>
#include <string>

#include "solver.h"


int main(int args, char **argv)
{
    std::cout << "vas a morir moe" << std::endl;
    if(args != 2)
    {
    std::cout << "Se ha ingresado una cantidad incorrecta de parámetros" << std::endl;
    return 1;
    }
    std::cout << "Honorarios y ganancias mil" << std::endl;
    std::string input = argv[1];
    std::cout<<input<<std::endl;
    Solver solved = Solver();
    solved.Read(input);
    std::cout << "vas a morir moe" << std::endl;
    return 0;
}
