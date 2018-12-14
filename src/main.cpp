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
    std::string input = argv[1];
    std::cout<<input<<std::endl;
    Solver solved = Solver();
    solved.Read(input);
    solved.Solve();


    return 0;
}
