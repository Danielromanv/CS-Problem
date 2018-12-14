#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include "solver.h"

bool check(std::vector<int> v){
    int a=0;
    for(unsigned int i=0; i<v.size();i++)
        a = a + v[i];
    if(a == 0)
        return false;
    else if(a >= 0)
        return true;
    return false;
}

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
    for(int i=0;i<this->clases;i++){
        for (int j=0;j<autoclase[i][1];j++)
            this->dominio.push_back(autoclase[i][0]);
    }
    return 0;
}

int Solver::Solve()
{
    std::vector<int> sol, v;
    for(int i = 0; i<autos;i++)
        v.push_back(0);
    sol = BT(this->dominio,v,sol, 2147483647,0,0);
    for(unsigned int i=0;i<sol.size();i++)
        std::cout<<sol[i];
    std::cout<< "esta es la sol "<<std::endl;
    std::cout<< eval(sol)<<std::endl;
    return 0;
}

std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act,std::vector<int>& bestres,int best,int index,int start){
    for (unsigned int i = 0; i < act.size(); i++) {
        std::cout <<  act[i];
    }
    std::cout << '\n';
    if(int e = eval(act) <= best){
        bestres = act;
        best = e;
    }
    if(index == this->autos){
        return bestres;
    }
    for (int j = start;j<this->autos;j++){
        act[index] = c[j];
        act = BT(c,act,bestres,best,index+1,j+1);
    }
    return act;
}

int Solver::eval(std::vector<int> &v)
{   int eval = 0;
    int bloque;
    int iter;

    for(int i = 0; i < opciones; i++){
        bloque = this->blocksize[i];
        for(unsigned int j = 0; j < v.size(); j++){
            iter = 0;
            for(unsigned int k = j; k < j + bloque && k < (unsigned int)autos && k<=v.size(); k++){
                iter += autoclase[v[k]][i];
                if(iter > maxopt[i]){
                    eval++;
                }
            }
        }
    }
    return eval;
}
