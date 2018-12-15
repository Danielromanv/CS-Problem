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

void Solver::Solve(std::string token){
    std::vector<int> sol, v;
    std::ofstream salida;
    v.resize(autos);
    sol = BT(this->dominio,v,sol, 2147483647,0,0);
    salida.open(token);
    std::cout << "Solución: " << '\n';
    for(unsigned int i=0;i<sol.size();i++){
        std::cout<<sol[i]<<" ";
        salida<<sol[i]<<" ";
        for(int j = 0;j<opciones;j++){
            std::cout << this->claseop[sol[i]][j] << ' ';
            salida<< this->claseop[sol[i]][j] << ' ';
        }
        salida<<'\n';
        std::cout << '\n';
    }
    salida<<"restricciones instatisfechas = " <<eval(sol)<<std::endl;
    std::cout<< "restricciones instatisfechas = " <<eval(sol)<<std::endl;
    salida.close();
}

//Funcion para evitar que se infrija las restricciones de cantidad de autos de cada clase en la secuencia

std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act,std::vector<int>& bestres,int best,int index,int start){
	std::sort(c.begin(), c.end());
    int e;
	do {
        if((e=eval(c)) < best){
            best = e;
            bestres = c;
        }
	}while(std::next_permutation(c.begin(), c.end()));
    return(bestres);
}

int Solver::eval(std::vector<int> &v){
    int restr = 0;
    unsigned int sizeIndividuo = v.size();
    for (unsigned int opcion = 0; opcion < blocksize.size(); opcion++){
      int block = blocksize[opcion];
      int maxCars = this->maxopt[opcion];
      for (unsigned int i = 0; i < sizeIndividuo; i++){
        int optionsInBlock = 0;
        for(unsigned int s = i; s < std::min(sizeIndividuo,i + block); s++){
          optionsInBlock += this->claseop[v[s]][opcion];
        }
        if(optionsInBlock > maxCars) restr++;
      }
    }
    return restr;
  }
