#include <cassert>
#include <iostream>

struct Zombie {
  int vida;
  int dmg;
  std::string nombre;
};

struct ListaZombie {
  Zombie *zombie;
  ListaZombie *sig;
};

Zombie *crearZombie(int def, int dmg, std::string nombre) {
  Zombie *zombie = new Zombie;
  zombie->vida = def;
  zombie->dmg = dmg;
  zombie->nombre = nombre;
  return zombie;
}

void elimZombie(Zombie *zombie) { delete zombie; }

void modificarZombie(Zombie *zombie, int def, int dmg, std::string nombre) {
  zombie->vida = def;
  zombie->dmg = dmg;
  zombie->nombre = nombre;
};
void agregarAListaZombie(ListaZombie **lista, Zombie *zombie) {
  ListaZombie *nuevo = new ListaZombie;
  nuevo->zombie = zombie;
  nuevo->sig = NULL;
  if (*lista == NULL) {
    *lista = nuevo;
  } else {
    ListaZombie *aux = *lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};
void eliminarListaZombie(ListaZombie **lista) {
  ListaZombie *aux = *lista;
  while (aux != NULL) {
    ListaZombie *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *lista = NULL;
};

void mostrarListaZombie(ListaZombie *lista) {
  ListaZombie *aux = lista;
  while (aux != NULL) {
    std::cout << "Nombre: " << aux->zombie->nombre << "\n";
    std::cout << "Fortaleza: " << aux->zombie->vida << "\n";
    std::cout << "Damage: " << aux->zombie->dmg << "\n";
    std::cout << "=========\n";
    aux = aux->sig;
  }
};

int getPoderCombinadoZmb(ListaZombie *oleada) {
  assert(oleada != NULL);
  int poderComb = 0;
  while (oleada != NULL) {
    poderComb += oleada->zombie->dmg;
    oleada = oleada->sig;
  }
  return poderComb;
}

void eliminarZombie(ListaZombie **lista, int pos) {
  assert(*lista != NULL);
  ListaZombie *aux = *lista;
  ListaZombie *ant = NULL;
  int cont = 1;
  while (aux != NULL && cont < pos) {
    ant = aux;
    aux = aux->sig;
    cont++;
  }
  if (aux == NULL) {
    return;
  }
  if (ant == NULL) {
    *lista = aux->sig;
  } else {
    ant->sig = aux->sig;
  }
  elimZombie(aux->zombie);
  delete aux;
};

Zombie *getZombie(ListaZombie **oleada, int pos) {
  int cont = 0;
  ListaZombie *aux = *oleada;
  while (aux != NULL && cont != pos) {
    cont++;
    aux = aux->sig;
  }
  if (aux == NULL) {
    return NULL;
  }
  std::cout << "Zombie Seleccionado: " << aux->zombie->nombre << std::endl;

  return aux->zombie;
}

int listaZombielen(ListaZombie *lista) {
  assert(lista != NULL);
  int cont = 0;
  while (lista != NULL) {
    cont++;
    lista = lista->sig;
  }
  return cont;
}
