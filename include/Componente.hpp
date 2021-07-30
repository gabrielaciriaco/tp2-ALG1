#ifndef Componente_H
#define Componente_H

#include <iostream>
#include <vector>
#include "Vertice.hpp"

using namespace std;

class Componente {
private:
 vector<Vertice*> vertices;
 int numeroSaidas;
 int numeroEntradas;
 
public:
  Componente();
  void insereVertice(Vertice* vertice);
  int getArestasFaltantes();
};

#endif