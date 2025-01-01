#include "mochila.cpp"

struct Soldado {
  int vida;
  std::string nombre;
  Mochila *mochila;
};

struct ListaSoldado {
  Soldado *soldado;
  ListaSoldado *sig;
};

Soldado *crearSoldado(int vida, std::string nombre) {
  Soldado *soldado = new Soldado;
  soldado->vida = vida;
  soldado->nombre = nombre;
  soldado->mochila = NULL;
  return soldado;
}

void darMochila(Soldado **soldado, Mochila *mochila) {
  (*soldado)->mochila = mochila;
}

void agregarAListaSoldado(ListaSoldado **lista, Soldado *soldado) {
  ListaSoldado *nuevo = new ListaSoldado;
  nuevo->soldado = soldado;
  nuevo->sig = NULL;
  if (*lista == NULL) {
    *lista = nuevo;
  } else {
    ListaSoldado *aux = *lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};

void eliminarListaSoldado(ListaSoldado **lista) {
  ListaSoldado *aux = *lista;
  while (aux != NULL) {
    ListaSoldado *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *lista = NULL;
};
