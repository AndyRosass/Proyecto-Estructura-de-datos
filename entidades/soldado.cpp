#include "../utility.cpp"
#include "mochila.cpp"
#include <cassert>

struct Soldado {
  int vida;
  int vida_maxima;
  int defensa;
  std::string nombre;
  Mochila *mochila;
};

struct ListaSoldado {
  Soldado *soldado;
  ListaSoldado *sig;
};

Soldado *crearSoldado(int vida_maxima, int defensa, std::string nombre) {
  Soldado *soldado = new Soldado;
  soldado->vida_maxima = vida_maxima;
  soldado->vida = vida_maxima;
  soldado->defensa = defensa;
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
    if (aux->soldado->mochila != NULL)
      eliminarMochila(&aux->soldado->mochila);
    ListaSoldado *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *lista = NULL;
};

bool ultimaArma(Mochila *mochila) {
  assert(mochila != NULL);

  int cantArmas = 0;
  while (mochila != NULL && cantArmas < 2) {
    if (mochila->objeto == NULL) {
      mochila = mochila->sig;
      continue;
    }
    if (mochila->objeto->categoria == "Ataque")
      cantArmas++;
    mochila = mochila->sig;
  }
  return cantArmas == 1 ? true : false;
}

Mochila *elegirObjetos(Mochila *listaObjetos) {
  Mochila *mochila = NULL;
  std::string opcion;
  int cont = 1;
  while (cont != 4) {
    mostrarListaObjetos(listaObjetos);
    std::cout << "Elija el objeto que desea agregar a su mochila (" << cont
              << "/3): ";
    std::cin >> opcion;
    limpiarBuffer();

    std::cout << "\n";

    if (!esNumero(opcion)) {
      std::cout << "Por favor ingrese un numero valido\n";
      continue;
    }
    if (stoi(opcion) < 1 || stoi(opcion) > listaObjetoslen(listaObjetos)) {
      std::cout << "Por favor ingrese un numero valido\n";
      continue;
    }
    agregarAMochila(&mochila, getObjeto(listaObjetos, stoi(opcion)));
    cont++;
  }
  return mochila;
}
void eliminarSoldado(ListaSoldado **lista, int pos) {
  assert(*lista != NULL);
  ListaSoldado *aux = *lista;
  ListaSoldado *ant = NULL;
  int cont = 1;
  while (aux != NULL && cont < pos) {
    ant = aux;
    aux = aux->sig;
    cont++;
  }
  if (aux == NULL) {
    std::cout << "No existe el soldado en la posicion " << pos << "\n";
    return;
  }
  if (ant == NULL) {
    *lista = aux->sig;
  } else {
    ant->sig = aux->sig;
  }
  delete aux;
}

int listaSoldadolen(ListaSoldado *lista) {
  assert(lista != NULL);
  int cont = 0;
  while (lista != NULL) {
    cont++;
    lista = lista->sig;
  }
  return cont;
}
