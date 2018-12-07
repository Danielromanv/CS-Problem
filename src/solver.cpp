#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "solver.h"

Solver::Solver()
{
    std::cout << "Ahora existo" << std::endl;
}


int Solver::Read(std::string problema)
{
    int word;
    std::vector<int> v;
    this->ruta = problema;
    std::ifstream archivo;
    archivo.open(problema);
    if(!archivo.good()){
    std::cout << "No se pudo leer el archivo" << std::endl;
    return 1;
    }
    std::cout << "En cada urna griega está" << '\n';
    archivo >> this-> autos;
    archivo >> this-> opciones;
    archivo >> this-> clases;
    for(int i=0;i<this->opciones;i++)
    {
        archivo >> word;
        this->maxauto.push_back(word);
    }
    for(int i=0;i<this->opciones;i++)
    {
        archivo >> word;
        this->maxtam.push_back(word);
    }
    for (unsigned int i=0; i<this->maxauto.size();i++)
        std::cout<< this->maxauto[i] <<' ';
    std::cout<<std::endl;
    for (unsigned int i=0; i<this->maxauto.size();i++)
        std::cout<< this->maxtam[i] <<' ';

    for (int i=0; i<this->clases;i++)
    {
        this->autoclase.push_back(v);
        for(int j=0;j<(this->opciones)+2;i++)
        {
            archivo >> word;
            this->autoclase[i].push_back(word);
        }
    }
    std::cout<< std::endl;
    std::cout << autos<<opciones<<clases<< '\n';
    return 0;
}
