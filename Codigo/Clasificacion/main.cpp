#include <iostream>
#include "DBSCAN.h"
#include <fstream>
#include <string>
using namespace std;

int main(){

    ifstream archivo;
    vector<Punto> datos;
    //Archivo prueba(100 datos), data(puntos de ejemplo visto en clase)
    archivo.open("prueba.txt");// prueba o data
    int i=0;
    int dimension=2;//grasa, calorias
    while(!archivo.eof()){
        std::string puntoX;
        float x;
        std::vector<float> X;
        //cout<<"Punto"<<i<<" "<<endl;
        //std::cout<<"Hola"<<std::endl;
        for(int j=0;j<dimension-1;j++){//Recoleccion de los datos del punto
            getline(archivo,puntoX,' ');
            x=stof(puntoX);
            X.push_back(x);
        }
        getline(archivo,puntoX,'\n');
        x=stof(puntoX);
        X.push_back(x);
        
        Punto puntito(X);
        //cout<<"jajajaja"<<puntito<<endl;
        datos.push_back(puntito);
        i++;
    }
    archivo.close();
    vector<Punto> X=datos;
    float eps=0.75;
    int minpts=2;

    DBSCAN dbscan(X,eps,minpts,"resultados.txt",dimension);
    dbscan.realizarBusqueda();

    return 0;
}