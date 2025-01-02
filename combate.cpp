#include "cargar_datos.cpp"
// #include "entidades/soldado.cpp"
// #include "entidades/zombie.cpp"
#include <cassert>
// Como me imagino el combate.
// Primer turno:
// SIEMPRE empiezan atacando los humanos
// y no termina el turno de los humanos hasta que
// todos los miembros del equipo realicen una accion
// Las acciones que se podrian hacer son
// Atacar: Atacas si tienes un arma cumpliendo
// con los requesitos (
//		* Los humanos nunca atacaran con un arma cuya fuerza sea mayor
// que la del conjunto de los zombies , a menos que sea su última arma.
// )
// Usar Objeto:
// Ya sea defensa o curarse (Por ahora que la curacion sea individual, si da
// chance que se pueda curar un miembro del equipo) Pasar el turno: Por si un
// miembro se queda sin arma sin objeto para que no valga vrg
//
// Zombies: Una vez finalizados 2 turnos de los humanos, los zombies atacan
// requesitos: (
// Atacar luego de 2 turnos de humanos
// Atacan primero al azar y luego al mas debil (Podria ser que en el 3er turno
// zombie vayan a por el debil) Los zombies atacan en oleadas de hasta 5 por vez
// (?)
// )
// El encuentro termina SI ALGUN BANDO MUERE POR COMPLETO
//

void mostrarDatosZombie(ListaZombie *oleada) {
  assert(oleada != NULL);
  std::string posicion = "Posicion: | ";
  std::string tipo = "Tipo: | ";
  std::string vida = "Vida: | ";
  int cont = 1;
  while (oleada != NULL) {
    posicion += std::to_string(cont) + " | ";
    tipo += oleada->zombie->nombre + " | ";
    vida += std::to_string(oleada->zombie->vida) + " | ";
    cont++;
    oleada = oleada->sig;
  }
  std::cout << posicion << "\n" << tipo << "\n" << vida << std::endl;
}

void mostrarDatosSoldados(ListaSoldado *equipo) {
  assert(equipo != NULL);
  std::string posicion = "Posicion: | ";
  std::string tipo = "Nombre: | ";
  std::string vida = "Vida: | ";
  int cont = 1;
  while (equipo != NULL) {
    posicion += std::to_string(cont) + " | ";
    tipo += equipo->soldado->nombre + " | ";
    vida += std::to_string(equipo->soldado->vida) + " | ";
    cont++;
    equipo = equipo->sig;
  }
  std::cout << posicion << "\n" << tipo << "\n" << vida << std::endl;
}

void atacarSoldado(Soldado **actual, ListaZombie **oleada) {
  Zombie *zombie;
  std::string opcion;
  bool salir = false;
  Objeto *seleccionada;

  while (!salir) {
    mostrarDatosZombie(*oleada);
    std::cout << "Elige a que zombie deseas atacar (1/"
              << listaZombielen(*oleada) << ") : ";
    std::cin >> opcion;
    limpiarBuffer();
    zombie = getZombie(oleada, stoi(opcion) - 1);

    seleccionada = NULL;

    Mochila *aux = (*actual)->mochila;

    std::string num = "Numero : | ";
    std::string nombre = "Nombre : | ";
    std::string balas = "Balas : | ";
    std::string dmg = "Ataque : | ";
    int cont = 1;
    int id;

    if (ultimaArma((*actual)->mochila)) {
      std::cout << "Solo tienes un arma!";
      while (aux != NULL && aux->objeto->categoria != "Ataque") {
        aux = aux->sig;
      }
      seleccionada = aux->objeto;
    } else {
      Mochila *armasDispo = NULL;
      while (aux != NULL) {
        if (aux->objeto->categoria == "Ataque")
          agregarAMochila(&armasDispo, aux->objeto);
        aux = aux->sig;
      }
      aux = armasDispo;
      while (aux != NULL) {
        num += std::to_string(cont) + " | ";
        nombre += aux->objeto->nombre + " | ";
        balas += std::to_string(aux->objeto->usos) + " | ";
        dmg += std::to_string(aux->objeto->valor) + " | ";

        cont++;
        aux = aux->sig;
      }
      std::cout << num << "\n"
                << nombre << "\n"
                << balas << "\n"
                << dmg << std::endl;
      while (true) {
        std::cout << "Selecciona el arma que quieres usar: ";
        std::cin >> opcion;
        limpiarBuffer();
        if (!esNumero(opcion)) {
          std::cout << "Por favor ingrese un numero valido\n";
          continue;
        }
        if (stoi(opcion) < 1 || stoi(opcion) > listaObjetoslen(armasDispo)) {
          std::cout << "Por favor ingrese un numero valido\n";
          continue;
        }
        for (int i = 1; i < stoi(opcion); i++) {
          armasDispo = armasDispo->sig;
        }
        seleccionada = armasDispo->objeto;
        if (seleccionada->valor > getPoderCombinadoZmb(*oleada)) {
          std::cout << "El arma seleccionada es muy fuerte para el zombie\n";
          continue;
        } else if (seleccionada->usos < 0) {
          std::cout << "El arma seleccionada no tiene balas\n";
          continue;
        }
        break;
      }
    }
    salir = true;
  }
  zombie->vida -= seleccionada->valor;
  seleccionada->usos--;
}

void soldadoOpciones(Soldado **actual, ListaZombie **oleada) {

  std::string opcion;
  bool salir = false;

  while (!salir) {

    std::cout << "1. ATACAR | 2. USAR OBJETO | 3. PASAR TURNO\n";
    std::cin >> opcion;
    limpiarBuffer();

    if (!esNumero(opcion)) {
      std::cout << "Por favor ingrese un numero valido\n";
      continue;
    }

    switch (stoi(opcion)) {

    case 1:
      atacarSoldado(actual, oleada);
      salir = true;
      break;

    case 2:
      continue;
      salir = true;
      break;

    case 3:
      salir = true;
      break;

    default:
      std::cout << "Por favor ingrese un numero valido\n";
      break;
    }
  }
}

void combate(ListaSoldado **soldados, ListaZombie **zombies) {
  int turno = 1;
  // 2 turnos seguidos de ataques Humanos
}

int main() {
  ListaSoldado *l = cargarSoldados();
  ListaZombie *z = cargarZombies();
  Mochila *listaObjetos = cargarObjetos();

  l->soldado->mochila = listaObjetos;
  atacarSoldado(&l->soldado, &z);

  eliminarListaZombie(&z);
  eliminarListaSoldado(&l);

  return 0;
}
