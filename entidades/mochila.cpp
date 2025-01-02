#include "objetos.cpp"
#include <cassert>

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
  assert(*mochila != NULL);
  Mochila *aux = *mochila;
  while (aux != NULL) {
    Mochila *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *mochila = NULL;
};

void mostrarListaObjetos(Mochila *listaObjetos) {

  assert(listaObjetos != NULL);
  std::string id = "ID : | ";
  std::string nombre = "Nombre : | ";
  std::string categ = "Categoria : | ";
  std::string usos = "Usos : | ";
  std::string valor = "Valor : | ";
  while (listaObjetos != NULL) {
    id += std::to_string(listaObjetos->objeto->id) + " | ";
    nombre += listaObjetos->objeto->nombre + " | ";
    categ += listaObjetos->objeto->categoria + " | ";
    usos += std::to_string(listaObjetos->objeto->usos) + " | ";
    valor += std::to_string(listaObjetos->objeto->valor);
    if (listaObjetos->objeto->categoria == "Ataque") {
      valor += " Dmg | ";
    } else if (listaObjetos->objeto->categoria == "Supervivencia") {
      valor += " HP | ";
    } else {
      valor += " DEF | ";
    }
    listaObjetos = listaObjetos->sig;
  }
  std::cout << id << "\n"
            << nombre << "\n"
            << categ << "\n"
            << usos << "\n"
            << valor << std::endl;
}

int listaObjetoslen(Mochila *listaObjetos) {
  int cont = 0;
  if (listaObjetos == NULL)
    return cont;
  while (listaObjetos != NULL) {
    cont++;
    listaObjetos = listaObjetos->sig;
  }
  return cont;
}

Objeto *getObjeto(Mochila *listaObjetos, int id) {
  assert(listaObjetos != NULL);
  while (listaObjetos != NULL) {
    if (listaObjetos->objeto->id == id) {
      return listaObjetos->objeto;
    }
    listaObjetos = listaObjetos->sig;
  }
  return NULL;
}
