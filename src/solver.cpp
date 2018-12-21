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
    // for (unsigned int i=0; i<this->maxopt.size();i++)
    //     std::cout<< this->maxopt[i] <<' ';
    // std::cout<<std::endl;
    // for (unsigned int i=0; i<this->maxopt.size();i++)
    //     std::cout<< this->blocksize[i] <<' ';
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
    // std::cout<<std::endl;
    // for (int i=0; i<this->clases;i++)
    // {
    //     for(j=0;j<(this->opciones)+2;j++)
    //         std::cout<<this->autoclase[i][j]<< " ";
    //     std::cout<<std::endl;
    // }

    for(int i=0;i<this->clases;i++){
        for (int j=0;j<autoclase[i][1];j++)
            this->dominio.push_back(autoclase[i][0]);
    }
    return 0;
}

void Solver::Solve(std::string token){
    std::vector<int> sol, k;
    std::ofstream salida;
    //for(unsigned int i=0; i<this->dominio.size();i++)
    //    std::cout << this->dominio[i] << ' ';
    //std::cout << '\n';
    int pos = 2147483647;
    int limit;
    k = BT(this->dominio,sol, pos,0,(int)this->dominio.size(), limit);
    //for (size_t n = 0; n < k.size(); n++) {
    //    std::cout << k[n] << '\n';
    //}
    //std::cout << '\n';
    salida.open(token);
    //std::cout << "Solución: " << '\n';
    for(unsigned int i=0;i<sol.size();i++){
        //std::cout<<sol[i]<<" ";
        salida<<sol[i]<<" ";
        for(int j = 0;j<opciones;j++){
            //std::cout << this->claseop[sol[i]][j] << ' ';
            salida<< this->claseop[sol[i]][j] << ' ';
        }
        salida<<'\n';
        //std::cout << '\n';
    }
    salida<<"restricciones instatisfechas = " <<eval(sol)<<std::endl;
    //std::cout<< "restricciones instatisfechas = " <<eval(sol)<<std::endl;
    salida.close();
}

//Funcion para evitar que se infrija las restricciones de cantidad de autos de cada clase en la secuencia
/*std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& bestres,int best,int index,int end){
	std::sort(c.begin(), c.end());
    int e;

	do {
        for (unsigned int j = 0; j < c.size(); j++) {
            std::cout << c[j] << ' ';
        }
        std::cout << '\n';
	    if((e=eval(c)) < best){
            best = e;
            bestres = c;
        }
	}while(std::next_permutation(c.begin(), c.end()));
    return(bestres);
}*/

void swap(int a,std::vector<int> &arr,int b)
{
	int temp = arr[b];
	arr[b] = arr[a];
	arr[a] = temp;
}

std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& bestres,int &best,int index,int end, int &limit){
    int t;
    if (index == end){

        /*std::cout << "End" << '\n';
        for (int x = 0; x < this->autos; x++) {
            std::cout << c[x] << ' ';
        }*/
    }
    else{
        for (int i = index; i < end; i++) {
            limit = limit+1;
            t = eval(c);
            if (t<best) {
                /*std::cout << "entró con: ";
                std::cout << c.size() << '\n';
                std::cout << t << '\n';
                std::cout << '\n';*/
                bestres = c;
                best = t;
            }
            //else if(t > best){
            //    continue;
            //}
            if(c[i] == c[index])
                continue;
            // std::cout << " t= "<< t<<" best= "<<best << "\n\n\n\n";
            // for (int m = 0; m < 10; m++) {
            //     std::cout << c[m] << ' ';
            // }
            //std::cout << '\n';
            //std::cout << " t= "<< t<<" best= "<<best << "\n\n\n\n";
            /*std::cout << "t es: "<<t << '\n';
            std::cout << "best es: "<<best << '\n';*/
            //std::cout << "iteración "<< i << '\n';
            swap(index,c,i);
            BT(c,bestres,best,index+1,end,limit);
            swap(i,c,index);
        }

    }
    return bestres;
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
