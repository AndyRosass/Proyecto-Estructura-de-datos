#include "combate.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void mostrarMenu() {
  std::cout << "=============================\n";
  std::cout << "       JUEGO DE LA CURA      \n";
  std::cout << "=============================\n";
  std::cout << "1. Jugar\n";
  std::cout << "2. Salir\n";
  std::cout << "=============================\n";
  std::cout << "Seleccione una opción: ";
}

void iniciarJuego() {
  // Cargar datos
  ListaSoldado *soldados = cargarSoldados();
  ListaZombie *zombies = cargarZombies();
  std::vector<nodo *> grafo = cargarGrafo();

  if (grafo.empty()) {
    std::cout
        << "Error al cargar los datos del mapa. Asegúrese de que el archivo "
           "existe y es correcto.\n";
    return;
  }
  if (soldados == NULL) {
    std::cout << "Error al cargar los datos. Asegúrese de que el archivo de "
                 "soldados existe y es correcto.\n";
    return;
  }
  if (zombies == NULL) {
    std::cout << "Error al cargar los datos. Asegúrese de que el archivo de "
                 "zombies existe y es correcto.\n";
    return;
  }

  if (soldados == NULL || zombies == NULL || grafo.empty()) {
    std::cout << "Error al cargar los datos. Asegúrese de que los archivos "
                 "existen y son correctos.\n";
    return;
  }

  // Asignar mochilas a los soldados
  Mochila *objetos = cargarObjetos();
  ListaSoldado *aux = soldados;
  while (aux != NULL) {
    aux->soldado->mochila = elegirObjetos(objetos);
    aux = aux->sig;
  }

  // Seleccionar nodo de inicio y nodo de destino
  nodo *nodoInicio = grafo[0];
  nodo *nodoDestino = grafo[rand() % grafo.size()];

  std::cout << "El juego ha comenzado. Debes llevar la cura desde el nodo "
            << nodoInicio->value << " hasta el nodo " << nodoDestino->value
            << ".\n";

  // Bucle principal del juego
  nodo *nodoActual = nodoInicio;
  while (nodoActual != nodoDestino) {
    std::cout << "Estás en el nodo " << nodoActual->value << ".\n";
    mostrarDatosZombie(zombies);
    mostrarDatosSoldados(soldados);

    // Combate en el nodo actual
    combate(&soldados, &zombies);

    if (soldados == NULL) {
      std::cout << "Todos los soldados han muerto. Has perdido.\n";
      return;
    }

    // Seleccionar siguiente nodo
    std::cout << "Seleccione el siguiente nodo para moverse: ";
    int siguienteNodo;
    std::cin >> siguienteNodo;
    limpiarBuffer();

    bool nodoValido = false;
    for (arista edge : nodoActual->edges) {
      if (edge.destination == siguienteNodo) {
        nodoActual = grafo[siguienteNodo - 1];
        nodoValido = true;
        break;
      }
    }

    if (!nodoValido) {
      std::cout << "Nodo no válido. Intente nuevamente.\n";
    }
  }

  std::cout << "¡Felicidades! Has entregado la cura en el nodo "
            << nodoDestino->value << ".\n";
}

int main() {
  srand(time(0));
  int opcion;

  while (true) {
    mostrarMenu();
    std::cin >> opcion;
    limpiarBuffer();

    if (opcion == 1) {
      iniciarJuego();
    } else if (opcion == 2) {
      std::cout << "Gracias por jugar. ¡Hasta la próxima!\n";
      break;
    } else {
      std::cout << "Opción no válida. Intente nuevamente.\n";
    }
  }

  return 0;
}
