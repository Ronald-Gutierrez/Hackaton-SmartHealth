#include "Punto.h"
#include <vector>
#include <cmath>
#include <fstream>
class DBSCAN{
    private:
    //std::vector<bool> visited;
    std::vector<Punto> X;
    std::vector<std::vector<int>> C;
    float eps;
    int minpts;
    int dimension;
    std::string nombreArchivo;
    std::ofstream archivo; 
    public:
    DBSCAN(std::vector<Punto>,float,int,std::string,int);
    ~DBSCAN();
    void realizarBusqueda();
    float distancia(Punto A,Punto B);
    std::vector<int> getNeighbors(int);
    bool esMiembroCluster(int);//
    void eliminarElemento(std::vector<int>&,int);
    bool esVisitado(std::vector<bool>&,int);//
    void imprimirArreglo();
};

DBSCAN::DBSCAN(std::vector<Punto> X,float eps, int minpts,std::string nombreArchivo,int dimension){
    //Marcamos todos los puntos como no visitados
    this->nombreArchivo=nombreArchivo;
    this->X=X;
    this->eps=eps;
    this->minpts=minpts;
    this->dimension=dimension;
}

DBSCAN::~DBSCAN(){

}
void DBSCAN::realizarBusqueda(){
    if(dimension<1){
        return;
    }
    archivo.open(nombreArchivo.c_str(), std::fstream::out);
    //archivo<<"Parametros:"<<std::endl;
    //archivo<<"epsilon = "<<eps<<std::endl;
    //archivo<<"minPts = "<<minpts<<std::endl;
    
    for(int i=0;i<X.size();i++){
        //archivo<<i+1<<". (";
        for(int j=0;j<dimension-1;j++){
            //archivo<<X[i].getX(j)<<", ";
        }
        //archivo<<X[i].getX(dimension-1)<<")"<<std::endl;
    }

    int idCluster=0;
    std::vector<bool> visited(X.size());
    std::vector<bool> noise(X.size());
    for(int i=0;i<visited.size();i++){
        if(visited[i]==true || noise[i]==true)
            continue;

        //archivo<<"Puntos no visitado: ";
        for(int p=0;p<visited.size();p++){
            if(visited[p]==false){
                //archivo<<p+1<<" ";
            }
        }
        //archivo<<"\nPunto visitado: "<<i+1<<std::endl;
        //archivo<<std::endl;
        visited[i]=true;
        int x=i;
        std::vector<int> N=getNeighbors(x);//En N se guardan las posiciones de los puntos
        
        //archivo<<"N : "<<std::endl;
        for(int p=0;p<N.size();p++){
            //archivo<<N[p]+1<<" ";
        }
        //archivo<<std::endl;
        if(N.size()<minpts){
            noise[i]=true;
        }

        else{
            std::vector<int> cluster;
            C.push_back(cluster);
            C[idCluster].push_back(x);// C <- {x}
            //cluster.push_back(x);
            for(int j=0;j<N.size();j++){//x'
                int xx=j;//x'
                if(visited[N[xx]])
                    continue;
                eliminarElemento(N,xx);//N<-n/X'
                
                    
                if(visited[N[xx]]==false){//x' es not visited
                    visited[N[xx]]=true;
                    std::vector<int> NN=getNeighbors(N[xx]);//N'
                    
                    //archivo<<"\nAnalizando: "<<N[xx]<<std::endl;
                    //archivo<<"N : "<<std::endl;
                    
                    //archivo<<std::endl;
                    if(NN.size()>=minpts){
                        for(int u=0;u<NN.size();u++){
                            if(visited[NN[u]]==false)
                                N.push_back(NN[u]);//N <- N u N'
                        }
                    }
                    for(int p=0;p<N.size();p++){
                        //archivo<<N[p]+1<<" ";
                    }
                    //archivo<<std::endl;
                    //archivo<<"N': "<<std::endl;
                    for(int p=0;p<NN.size();p++){
                        //archivo<<NN[p]+1<<" ";
                    }
                    //archivo<<std::endl;
                }
                if(esMiembroCluster(N[xx])==false){//x' no miebro de ningun cluster
                    C[idCluster].push_back(N[xx]);//C <- C u {x}
                }
            }
            /*
            archivo<<"N modificado : "<<std::endl;
            for(int p=0;p<N.size();p++){
                archivo<<N[p]+1<<" ";
            }
            archivo<<std::endl;
            */
            idCluster++;
        }
    }
    int caracterCluster=65;//A
    for(int p=0;p<C.size();p++){
        archivo<<"Grupo "<<(char)caracterCluster<<": ";
        for(int j=0;j<C[p].size();j++){
            archivo<<C[p][j]+1<<" ";
        }
        archivo<<std::endl;
        caracterCluster++;
    }
    archivo.close();
}
float DBSCAN::distancia(Punto A,Punto B){
    float resultado=0;
    for(int i=0;i<dimension;i++){
        resultado=resultado+pow(A.getX(i)-B.getX(i),2);
    }
    return sqrt(resultado);
}
std::vector<int> DBSCAN::getNeighbors(int x){
    std::vector<int> N;
    for(int i=0;i<X.size();i++){
        if(X[x]==X[i])
            continue;
        if(distancia(X[x],X[i])<=eps){
            //archivo<<"asd "<<distancia(X[x],X[i])<<" ";
            N.push_back(i);
        }
    }
    //archivo<<std::endl;
    return N;
}
void DBSCAN::eliminarElemento(std::vector<int>& N,int pos){
    // DELETE element "set"
    if(N.size()==0)
      return;
    auto elem_to_remove = N.begin() + pos;
    if (elem_to_remove != N.end()) {
        N.erase(elem_to_remove);
    }
}
bool DBSCAN::esVisitado(std::vector<bool>& visited, int xx){
    int i;
    int pos=0;
    for(i=0;i<X.size();i++){
        if(X[i]==X[xx]){
            pos=i;
            if(visited[i]==true){
                return true;
            }
        }
    }
    visited[pos];//marcamos x' como visited
    return false;
}
bool DBSCAN::esMiembroCluster(int xx){
    for(int i=0;i<C.size();i++){
        for(int j=0;j<C[i].size();j++){
            if(xx==C[i][j])
                return true;
        }
    }
    return false;
}