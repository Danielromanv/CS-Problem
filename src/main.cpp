#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "solver.h"


int main(int args, char **argv)
{
    if(args != 2)
    {
    std::cout << "Se ha ingresado una cantidad incorrecta de parámetros" << std::endl;
    return 1;
    }
    std::string input = argv[1];
    std::string s = input;
    std::string delimiter = "/";
    std::string token = s.substr(s.find(delimiter)+1,s.size());
    delimiter=".txt";
    token = token.substr(0,token.find(delimiter));
    token = token + ".out";
    Solver solved = Solver();
    solved.Read(input);
    solved.Solve(token);

    return 0;
}
