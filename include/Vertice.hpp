#ifndef Vertice_H
#define Vertice_H

#include <iostream>
#include <vector>

using namespace std;

class Vertice {
private:
 int id;
 vector<Vertice*> entradas;
 vector<Vertice*> saidas;
 
public:
  Vertice() {};
  Vertice(int id);
  void insereEntrada(Vertice* vertice);
  void insereSaida(Vertice* vertice);
  int getId();
  vector<Vertice*> getEntradas();
  vector<Vertice*> getSaidas();
  vector<Vertice*> getAdjacencias();
};

#endif