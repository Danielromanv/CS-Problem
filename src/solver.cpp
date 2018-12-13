#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

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
    for(int i=0;i<this->clases;i++){
        dominio.push_back(autoclase[i][1]);
    }
    std::cout<<dominio[0]<<dominio[1];
    sol = BT(dominio,v);
    for(unsigned int i=0;i<sol.size();i++)
        std::cout<<sol[i];
    std::cout<<std::endl;
    return 0;
}
std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act/*int best*/){
    std::stack <int> s;
    std::vector<int> v = act;
    std::cout<<s.size()<<std::endl;
    std::cout<< "largo inicial de la cosa" << v.size() <<std::endl;
    for(int i=0; i<this->clases;i++){
        if(c[i]>0){
            s.push(i);
            v.push_back(i);
            c[i] = c[i]-1;
            break;
            }
    }
    while(!s.empty()){
        std::cout<< "alksjas " << v.size() <<std::endl;
        for(int i=0; i<this->clases;i++){
            for (unsigned int j=0;j<v.size();j++)
                std::cout<<v[j]<<" ";
            std::cout<<std::endl;
            if(i!=0 && c[i-1]>0){
                i = i-1;
                s.push(i);
                std::cout<<"Insertando "<<i<< "en posición "<<std::endl;
                v.push_back(i);
                std::cout << "me voy a morir" << '\n';
                c[i] = c[i] - 1;
            }
            else if(c[i] > 0){
                std::cout<<c[i] << " es el c"<<"Insertando "<<i<< "en posición "<<std::endl;
                s.push(i);
                v.push_back(i);
                std::cout << "me voy a morir" << '\n';
                c[i] = c[i] - 1;
            }
            std::cout<<"stack tiene en top: "<<s.top()<<std::endl;
            std::cout<< "este es el tamaño del vector "<<v.size()<<std::endl;
            std::cout<<"no quiere entrarr!!! \n\n\n";
            for(unsigned int i=0;i<v.size();i++)
                std::cout << "el vector: "<< v[i]<<std::endl;
            if((int)v.size() == this->autos){
                std::cout << v[0]<<" "<< v[1]<<" "<< v[2]<<" "<<std::endl;
                std::cout<<"llené el vector sol="<< eval(v)<<std::endl;}
        }
    }
    return v;

}

int Solver::eval(std::vector<int> &v)
{


    int eval = 0;
    int bloque;
    int iter;
    for(int i = 1; i < opciones+2; i++){
        bloque = maxopt[i];
        for(int j = 0; j < autos; j++){
            iter = 0;
            for(int k = j; k < j + bloque && k < autos; k++){
                iter += autoclase[v[k]][i];
                if(iter > blocksize[i]){
                    eval++;
                }
            }
        }
    }
    return eval;
}
