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
    int word, j=0;
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
    for(int i=0;i<this->opciones;i++){
        archivo >> word;
        this->maxopt.push_back(word);
    }
    for(int i=0;i<this->opciones;i++)
    {
        archivo >> word;
        this->blocksize.push_back(word);
    }
    for (unsigned int i=0; i<this->maxopt.size();i++)
        std::cout<< this->maxopt[i] <<' ';
    std::cout<<std::endl;
    for (unsigned int i=0; i<this->maxopt.size();i++)
        std::cout<< this->blocksize[i] <<' ';
    //Se guardan los autos de cada clase con sus opciones en una matriz
    for (int i=0; i<this->clases;i++)
    {
        this->autoclase.push_back(v);
        for(j=0;j<(this->opciones)+2;j++)
        {
            archivo >> word;
            this->autoclase[i].push_back(word);
        }
    }
    std::cout<<std::endl;
    for (int i=0; i<this->clases;i++)
    {
        for(j=0;j<(this->opciones)+2;j++)
            std::cout<<this->autoclase[i][j]<< " ";
        std::cout<<std::endl;
    }
    return 0;
}

int Solver::Solve()
{
    std::vector<int> sol, dominio, v;
    for(int i=0;i<this->clases;i++)
        dominio.push_back(autoclase[i][1]);
    std::cout<<dominio[0]<<dominio[1];
    sol = BT(dominio,v,0);
    for(unsigned int i=0;i<sol.size();i++)
        std::cout<<sol[i];
    std::cout<<std::endl;
    return 0;
}
std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act, int inicio /*int best*/){
    std::cout<<"soy la ejecución "<<inicio<<std::endl;
    std::vector<int> v = act;
    for(int i=0; i<this->clases;i++){
        std::cout<<i<<std::endl;
        if(c[i] > 0){
            v.insert(v.begin()+inicio,i);
            std::cout << "me voy a morir" << '\n';
            c[i] = c[i] - 1;
            v = BT(c,v,inicio+1/*best*/);
        }
        else if(i+1<clases && c[i+1] >0){
            v.insert(v.begin()+inicio,i+1);
            c[i+1] = c[i+1] - 1;
            v = BT(c,v,inicio+1);
        }
    }
    return v;
}
