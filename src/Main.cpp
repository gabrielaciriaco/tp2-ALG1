#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "Grafo.hpp"

using namespace std;

Grafo lerRotas(int numeroAeroportos, int numeroRotas) {
  int vertice1;
  int vertice2;
  Grafo grafo(numeroAeroportos);
  for (int i = 0; i < numeroRotas; i++) {
    cin >> vertice1 >> vertice2;
    grafo.addAresta(vertice1, vertice2);
  }
  return grafo;
}

int main() {
  int numeroAeroportos, numeroRotas;
  cin >> numeroAeroportos >> numeroRotas;

  Grafo grafo = lerRotas(numeroAeroportos, numeroRotas);

  grafo.encontraComponentesFortementeConectados();
  cout << grafo.getArestasMinimas() << endl;
  return 0;
}
