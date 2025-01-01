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
