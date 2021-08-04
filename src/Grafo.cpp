#include "Grafo.hpp"

bool includes(list<int> listaPesquisa, int item) {
  return find(listaPesquisa.begin(), listaPesquisa.end(), item) !=
         listaPesquisa.end();
}

bool includes(vector<int> listaPesquisa, int item) {
  return find(listaPesquisa.begin(), listaPesquisa.end(), item) !=
         listaPesquisa.end();
}

Grafo::Grafo(int vertices) {
  this->vertices = vertices;
  adj = new list<int>[vertices];
}

void Grafo::addAresta(int verticeOrigem, int verticeDestino) {
  adj[verticeOrigem - 1].push_back(verticeDestino - 1);
}
void Grafo::encontraComponente(int verticeAtual, int temposDescoberta[],
                               int tempoAncestralProximo[],
                               stack<int>* acentraisConectados,
                               bool estaNaPilha[], int* tempo) {
  temposDescoberta[verticeAtual] = tempoAncestralProximo[verticeAtual] =
      ++*tempo;
  acentraisConectados->push(verticeAtual);
  estaNaPilha[verticeAtual] = true;

  list<int>::iterator i;
  for (i = adj[verticeAtual].begin(); i != adj[verticeAtual].end(); ++i) {
    int v = *i;

    if (temposDescoberta[v] == -1) {
      encontraComponente(v, temposDescoberta, tempoAncestralProximo,
                         acentraisConectados, estaNaPilha, tempo);
      tempoAncestralProximo[verticeAtual] =
          min(tempoAncestralProximo[verticeAtual], tempoAncestralProximo[v]);
    } else if (estaNaPilha[v] == true) {
      tempoAncestralProximo[verticeAtual] =
          min(tempoAncestralProximo[verticeAtual], temposDescoberta[v]);
    }
  }

  int aux = 0;

  if (tempoAncestralProximo[verticeAtual] == temposDescoberta[verticeAtual]) {
    vector<int> componenteAtual;
    while (acentraisConectados->top() != verticeAtual) {
      aux = (int)acentraisConectados->top();
      componenteAtual.push_back(aux);
      estaNaPilha[aux] = false;
      acentraisConectados->pop();
    }
    aux = (int)acentraisConectados->top();
    componenteAtual.push_back(aux);
    componentesFc.push_back(componenteAtual);
    estaNaPilha[aux] = false;
    acentraisConectados->pop();
  }
  return;
}

void Grafo::encontraComponentesFortementeConectados() {
  int* temposDescoberta = new int[vertices];
  int* tempoAncestralProximo = new int[vertices];
  bool* estaNaPilha = new bool[vertices];
  stack<int>* acentraisConectados = new stack<int>();

  for (int i = 0; i < vertices; i++) {
    temposDescoberta[i] = -1;
    tempoAncestralProximo[i] = -1;
    estaNaPilha[i] = false;
  }

  for (int i = 0; i < vertices; i++) {
    int tempo = 0;
    if (temposDescoberta[i] == -1) {
      encontraComponente(i, temposDescoberta, tempoAncestralProximo,
                         acentraisConectados, estaNaPilha, &tempo);
    }
  }
}
bool Grafo::temArestaDeEntrada(vector<int> componente) {
  for (int vertice : componente) {
    for (int i = 0; i < vertices; i++) {
      if (includes(adj[i], vertice) && !includes(componente, i)) {
        return true;
      }
    }
  }
  return false;
}

bool Grafo::temArestaDeSaida(vector<int> componente) {
  for (int vertice : componente) {
    for (int verticeSaida : adj[vertice]) {
      if (!includes(componente, verticeSaida)) {
        return true;
      }
    }
  }
  return false;
}

int Grafo::getArestasMinimas() {
  int verticesSemEntrada = 0;
  int verticesSemSaida = 0;

  for (int i = 0; i < componentesFc.size(); i++) {
    vector<int> componente = componentesFc.at(i);
    bool componentHasInbound = temArestaDeEntrada(componente);
    bool componentHasOutbound = temArestaDeSaida(componente);

    if (!componentHasInbound) {
      verticesSemEntrada++;
    }
    if (!componentHasOutbound) {
      verticesSemSaida++;
    }
  }

  return verticesSemEntrada > verticesSemSaida ? verticesSemEntrada
                                               : verticesSemSaida;
}