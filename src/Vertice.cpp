#include "Vertice.hpp"

Vertice::Vertice(int id){
    this->id = id;
}
void Vertice::insereEntrada(Vertice* vertice){
    this->entradas.push_back(vertice);
}
void Vertice::insereSaida(Vertice* vertice){
    this->saidas.push_back(vertice);
}

int Vertice::getId(){
    return this->id;
}

vector<Vertice*> Vertice::getEntradas(){
    return this->entradas;
}

vector<Vertice*> Vertice::getSaidas(){
    return this->saidas;
}

vector<Vertice*> Vertice::getAdjacencias(){
    vector<Vertice*> adjacencias = this->entradas;
    adjacencias.insert(adjacencias.end(), this->saidas.begin(), this->saidas.end());
    return adjacencias;
}