#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include <algorithm>
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
        this->claseop.push_back(v);
        for(j=0;j<(this->opciones)+2;j++)
        {
            archivo >> word;
            this->autoclase[i].push_back(word);
            if(j>1)
                this->claseop[i].push_back(word);
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
bool Solver::checkseq(std::vector<int> v, int n)
{   int cont = 0;
    int max = autoclase[n][1];
    for (unsigned int i = 0; i < v.size(); i++) {
        if(v[i] == n)
            cont++;
    }
    if (cont==max)
        return false;
    else
        return true;
}
std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act,std::vector<int>& bestres,int best,int index,int start){
    // std::cout << "actual:" << '\n';
    // for (unsigned int i = 0; i < act.size(); i++) {
    //     std::cout<< act[i]<<" ";
    // }
    // std::cout<<std::endl;
    for (unsigned int i = 0; i < act.size(); i++) {
        std::cout << " "<< act[i];
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
        if(checkseq(act,c[j]))
            act[index] = c[j];
        else
            break;
        act = BT(c,act,bestres,best,index+1,j+1);
    }
    return act;
}
int Solver::eval(std::vector<int> &v){
    int restr = 0;
    unsigned int sizeIndividuo = v.size();
    for (unsigned int opcion = 0; opcion < blocksize.size(); opcion++){                           //Recorre opciones
      int block = blocksize[opcion];
      int maxCars = this->maxopt[opcion];
      for (unsigned int i = 0; i < sizeIndividuo; i++){                            //recorre individuo
        int optionsInBlock = 0;
        for(unsigned int s = i; s < std::min(sizeIndividuo,i + block); s++){            //recorre bloque dentro del individuo
          optionsInBlock += this->claseop[v[s]][opcion];
        }
        if(optionsInBlock > maxCars) restr++;
      }
    }
    return restr;
  }
