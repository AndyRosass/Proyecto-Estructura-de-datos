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
    if (oleada->zombie->vida <= 0) {
      oleada = oleada->sig;
      continue;
    }

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

        std::cout << "\n"
                  << num << "\n"
                  << nombre << "\n"
                  << balas << "\n"
                  << dmg << std::endl;

        std::cout << "Selecciona el arma que quieres usar: ";
        std::cin >> opcion;
        limpiarBuffer();

        if (!esNumero(opcion)) {
          std::cout << "Por favor ingrese un numero valido\n";
          continue;
        }
        if (stoi(opcion) < 1 || stoi(opcion) > listaObjetoslen(armasDispo)) {
          std::cout << "Por favor ingrese un numero dentro del rango\n";
          continue;
        }
        Mochila *seleccionada_moch = armasDispo;
        for (int i = 1; i < stoi(opcion); i++) {
          seleccionada_moch = seleccionada_moch->sig;
        }
        seleccionada = armasDispo->objeto;
        if (seleccionada->valor > getPoderCombinadoZmb(*oleada) &&
            verificarArmas((*actual)->mochila, seleccionada->valor)) {

          std::cout << "El arma seleccionada es muy fuerte para el zombie\n"
                    << getPoderCombinadoZmb(*oleada) << "\n";

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

void usarObjeto(Soldado **actual) {
  if ((*actual)->mochila == NULL) {
    std::cout << "La mochila está vacía o no existe.\n";
    return;
  }

  Mochila *aux = (*actual)->mochila;
  Mochila *objetosDispo = NULL;

  while (aux != NULL) {
    if (aux->objeto->categoria != "Ataque") {
      agregarAMochila(&objetosDispo, aux->objeto);
    }
    aux = aux->sig;
  }

  if (objetosDispo == NULL) {
    std::cout << "No hay objetos disponibles para usar.\n";
    return;
  }

  aux = objetosDispo;
  std::string num = "Numero : | ";
  std::string nombre = "Nombre : | ";
  std::string categoria = "Categoria : | ";
  int cont = 1;

  while (aux != NULL) {
    if (aux->objeto->categoria == "Ataque") {
      aux = aux->sig;
      continue;
    }

    num += std::to_string(cont) + " | ";
    nombre += aux->objeto->nombre + " | ";
    categoria += aux->objeto->categoria + " | ";
    cont++;
    aux = aux->sig;
  }

  std::cout << num << "\n" << nombre << "\n" << categoria << std::endl;

  std::string opcion;
  while (true) {
    std::cout << "Elige un objeto para usar: ";
    std::cin >> opcion;
    limpiarBuffer();

    if (!esNumero(opcion)) {
      std::cout << "Por favor ingrese un numero valido\n";
      continue;
    }

    if (stoi(opcion) < 1 || stoi(opcion) > cont - 1) {
      std::cout << "Por favor ingrese un numero valido\n";
      continue;
    }

    aux = objetosDispo;
    for (int i = 1; i < stoi(opcion); i++) {
      aux = aux->sig;
    }

    Objeto *objetoElegido = aux->objeto;
    if (objetoElegido->categoria == "Supervivencia") {
      (*actual)->vida += objetoElegido->valor;
      if ((*actual)->vida > (*actual)->vida_maxima) {
        (*actual)->vida = (*actual)->vida_maxima;
      }
      std::cout << "El soldado ha sido curado. Vida actual: " << (*actual)->vida
                << "\n";
    } else {
      (*actual)->defensa = objetoElegido->valor;
      std::cout << "El soldado ha aumentado su defensa. Defensa actual: "
                << (*actual)->defensa << "\n";
    }
    break;
  }
}

void soldadoOpciones(Soldado **actual, ListaZombie **oleada) {
  if (todosZombiesMuertos(*oleada))
    return;
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
      // Aqui crea una funcion que tome como referencia la mochila del soldado y
      // le de la opcion de elegir un objeto siempre y cuando no sea un arma
      // (objeto->categoria != "Ataque") ademas de que si el objeto es de
      // curacion, se le aplique al soldado que lo use
      usarObjeto(actual);
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

  // Primeros 2 turnos de los humanos
  for (int i = 0; i < 2; ++i) {
    ListaSoldado *aux = *soldados;
    while (aux != NULL) {
      soldadoOpciones(&(aux->soldado), zombies);
      aux = aux->sig;
    }
    if (*zombies == NULL || todosZombiesMuertos(*zombies)) {
      std::cout << "Los soldados han ganado.\n";
      return;
    }
  }

  // Bucle principal de combate
  while (*soldados != NULL && *zombies != NULL) {
    // Turno de los humanos
    ListaSoldado *auxSoldado = *soldados;
    while (auxSoldado != NULL) {
      soldadoOpciones(&(auxSoldado->soldado), zombies);
      auxSoldado = auxSoldado->sig;
    }

    // Verificar si todos los zombies han muerto
    if (*zombies == NULL || todosZombiesMuertos(*zombies)) {
      std::cout << "Los soldados han ganado.\n";
      return;
    }

    // Turno de los zombies
    if (turno % 2 == 0) {
      ListaZombie *auxZombie = *zombies;
      while (auxZombie != NULL) {
        // Seleccionar un soldado al azar para atacar
        int numSoldados = listaSoldadolen(*soldados);
        int pos = rand() % numSoldados;
        ListaSoldado *soldadoAtacado = *soldados;
        for (int i = 0; i < pos; ++i) {
          soldadoAtacado = soldadoAtacado->sig;
        }
        soldadoAtacado->soldado->vida -= auxZombie->zombie->dmg;
        std::cout << auxZombie->zombie->nombre << " atacó a "
                  << soldadoAtacado->soldado->nombre << " causando "
                  << auxZombie->zombie->dmg << " de daño.\n";
        auxZombie = auxZombie->sig;
      }
    }

    // Eliminar soldados muertos
    ListaSoldado *prevSoldado = NULL;
    auxSoldado = *soldados;
    while (auxSoldado != NULL) {
      if (auxSoldado->soldado->vida <= 0) {
        if (prevSoldado == NULL) {
          *soldados = auxSoldado->sig;
        } else {
          prevSoldado->sig = auxSoldado->sig;
        }
        ListaSoldado *temp = auxSoldado;
        auxSoldado = auxSoldado->sig;
        delete temp->soldado;
        delete temp;
      } else {
        prevSoldado = auxSoldado;
        auxSoldado = auxSoldado->sig;
      }
    }

    // Verificar si todos los soldados han muerto
    if (*soldados == NULL) {
      std::cout << "Los zombies han ganado.\n";
      return;
    }

    // Eliminar zombies muertos
    ListaZombie *prevZombie = NULL;
    ListaZombie *auxZombie = *zombies;
    while (auxZombie != NULL) {
      if (auxZombie->zombie->vida <= 0) {
        if (prevZombie == NULL) {
          *zombies = auxZombie->sig;
        } else {
          prevZombie->sig = auxZombie->sig;
        }
        ListaZombie *temp = auxZombie;
        auxZombie = auxZombie->sig;
        delete temp->zombie;
        delete temp;
      } else {
        prevZombie = auxZombie;
        auxZombie = auxZombie->sig;
      }
    }

    turno++;
  }

  if (*soldados == NULL) {
    std::cout << "Los zombies han ganado.\n";
  } else {
    std::cout << "Los soldados han ganado.\n";
  }
}

int main() {
  ListaSoldado *soldados = cargarSoldados();
  ListaZombie *zombies = cargarZombies();

  ListaSoldado *aux = soldados;

  while (aux != NULL) {
    aux->soldado->mochila = cargarObjetos();
    aux = aux->sig;
  }
  combate(&soldados, &zombies);
  eliminarListaSoldado(&soldados);
  eliminarListaZombie(&zombies);
}
