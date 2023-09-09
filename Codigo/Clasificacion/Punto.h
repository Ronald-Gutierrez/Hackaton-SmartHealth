#include <iostream>
#include <vector>
class Punto{
    private:
    std::vector<float> X;//En cada posicion guardaremos los datos array de n dimensiones
    public:
    float getX(int);
    void setX(float,int);
    Punto(std::vector<float>);
    ~Punto();
    friend std::ostream& operator<<(std::ostream& os,  Punto dt);
    friend Punto operator+(const Punto &p1,const Punto &p2);
    friend Punto operator/(Punto p1,float divisor);
    friend bool operator==(const Punto &p1,const Punto &p2);
};

Punto::Punto(std::vector<float> X){
    this->X=X;
}

Punto::~Punto()
{
}
float Punto::getX(int posicion){
    return X[posicion];
}
void Punto::setX(float dato,int posicion){
    this->X[posicion]=dato;
}
std::ostream& operator<<(std::ostream& os, Punto dt){
    for(int i=0;i<dt.X.size();i++){
        os << dt.getX(i) << '\t';
    }
    std::cout<<std::endl;
    return os;
}
Punto operator+(const Punto &p1,const Punto &p2){
    std::vector<float> suma(p1.X.size());
    for(int i=0;i<p1.X.size();i++){
        suma[i]=suma[i]+p1.X[i]+p2.X[i];
    }
    return Punto(suma);
}
Punto operator/(Punto p1,float divisor){
    
    for(int i=0;i<p1.X.size();i++){
        p1.X[i]=p1.X[i]/divisor;
    }
    return p1;
}
bool operator==(const Punto &p1,const Punto &p2){
    for(int i=0;i<p1.X.size();i++){
        if(p1.X[i]!=p2.X[i])
            return false;
    }
    return true;
}