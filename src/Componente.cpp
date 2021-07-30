#include "Componente.hpp"

Componente::Componente(){
  this->numeroSaidas=0;
  this->numeroEntradas=0;
}

void Componente::insereVertice(Vertice* vertice){
  bool naoTemEntradas = vertice->getEntradas().empty();
  bool naoTemSaidas = vertice->getSaidas().empty();
  if(naoTemEntradas){
    this->numeroEntradas++;
  }
  if(naoTemSaidas){
    this->numeroSaidas++;
  }
  this->vertices.push_back(vertice);
}

int Componente::getArestasFaltantes(){
    if(this->numeroEntradas>this->numeroSaidas){
       return this->numeroEntradas;
    }
    return this->numeroSaidas;
}