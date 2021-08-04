#ifndef Grafo_H
#define Grafo_H
#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Grafo {
  int vertices;
  list<int>* adj;
  vector<vector<int>> componentesFc;

  void encontraComponente(int verticeAtual, int temposDescoberta[],
                          int tempoAncestralProximo[],
                          stack<int>* acentraisConectados, bool estaNaPilha[],
                          int* tempo);

 public:
  Grafo(int vertices);
  void addAresta(int verticeOrigem, int verticeDestino);
  void encontraComponentesFortementeConectados();
  bool temArestaDeEntrada(vector<int> componente);
  bool temArestaDeSaida(vector<int> componente);
  int getArestasMinimas();
};

#endif