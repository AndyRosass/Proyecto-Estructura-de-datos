#include "objetos.cpp"

struct Mochila {
  Objeto *objeto;
  Mochila *sig;
};

void agregarAMochila(Mochila **mochila, Objeto *objeto) {
  Mochila *nuevo = new Mochila;
  nuevo->objeto = objeto;
  nuevo->sig = NULL;
  if (*mochila == NULL) {
    *mochila = nuevo;
  } else {
    Mochila *aux = *mochila;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};

void eliminarMochila(Mochila **mochila) {
  Mochila *aux = *mochila;
  while (aux != NULL) {
    Mochila *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *mochila = NULL;
};
