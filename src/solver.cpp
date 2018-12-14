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
        this->dominio.push_back(autoclase[i][1]);
    }
    return 0;
}

int Solver::Solve()
{
    std::vector<int> sol, v;
    sol = BT(this->dominio,v, 2147483647,0);
    for(unsigned int i=0;i<sol.size();i++)
        std::cout<<sol[i];
    std::cout<< "esta es la sol "<<std::endl;
    return 0;
}

std::vector<int> Solver::BT(std::vector<int>& c,std::vector<int>& act,int best,int inicio){
    std::cout<<"best = "<<best<<std::endl;
    std::cout<<"inicio = "<<inicio<<std::endl;
    int e;
    bool flag = check(c);
    std::cout << flag << '\n';
    std::cout << "c inicial = ";
    for (unsigned int j = 0 ; j<c.size();j++)
        std::cout << c[j];
    std::vector<int> v = act;
    if(inicio==autos){
        std::cout << "miiiiau" << '\n';
        e = eval(v);
        return(v);}
        std::cout << "/* message */" << '\n';
    while(flag){
            for(int i=inicio;i<clases;){
                std::cout << "i= "<< i << '\n';
                std::cout << "c = ";
                for (unsigned int j = 0 ; j<c.size();j++)
                    std::cout << c[j];
                std::cout << '\n';
                std::cout << "v = ";
                for (unsigned int j = 0 ; j<v.size();j++)
                    std::cout << v[j];
                std::cout << '\n';
                std::cout <<"best = "<<best<< std::endl;
                std::cout << "c actual "<< c[i] << "\n\n";
                if (c[i] > 0){
                    v.push_back(i);
                    c[i] = c[i] - 1;
                    }
                else if(c[i] == 0){
                    i++;
                    }

                }
            if(!check(c)){
                std::cout << "\nme qué sin valores\n" << '\n';
                for (unsigned int j = 0 ; j<c.size();j++)
                    std::cout << c[j];
                for (unsigned int j = 0 ; j<v.size();j++)
                    std::cout << v[j];
                flag = check(c);
            }
    }
    e = eval(v);
    std::cout << "llamo a la recursión" << '\n';
    return BT(c,v,e,inicio+1);
}

int Solver::eval(std::vector<int> &v)
{   for (unsigned int i=0;i<v.size();i++)
        std::cout<< v[i]<< " ";
    std::cout<<std::endl;
    int eval = 0;
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
    std::cout<<"valor = "<<eval<<std::endl;
    return eval;
}
