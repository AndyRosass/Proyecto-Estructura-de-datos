#include <iostream>
#include <string>
#include <limits>

// Macros para crear zombies
#define NEW_ZB_AGIL crearZombie(70, 5, "Agil y veloz")
#define NEW_ZB_FUER crearZombie(120, 15, "Fuerte")
#define NEW_ZB_INTE crearZombie(50, 1, "Inteligente")
#define NEW_ZB_HONG crearZombie(100, 3, "Infectado por Hongos")
#define NEW_ZB_BIOL crearZombie(100, 5, "Bioluminiscente")
// Macros para crear armas de fuego
#define NEW_ARMA_PIST crearArma(1, 3, 24, 1, "Pistola")
#define NEW_ARMA_ESCO crearArma(2, 5, 10, 2, "Escopeta")
#define NEW_ARMA_FUSI crearArma(1, 4, 20, 1, "Fusil")
#define NEW_ARMA_FRAN crearArma(2, 10, 7, 2, "Francotirador")
#define NEW_ARMA_BALE crearArma(1, 2, 30, 1, "Ballesta")
#define NEW_ARMA_TIRA crearArma(1, 2, 20, 1, "Tirachinas")
// Macros para crear armas blancas
#define NEW_ARMA_CUCH crearArma(2, 6, 0, 2, "Cuchillo")
#define NEW_ARMA_KATA crearArma(2, 8, 0, 2, "Katana")
#define NEW_ARMA_BATE crearArma(3, 4, 0, 3, "Bate de Beisbol de madera")
#define NEW_ARMA_TUBE crearArma(1, 3, 0, 1, "Tuberias")
#define NEW_ARMA_MART crearArma(3, 8, 0, 3, "Martillo")
// Macros para crear lanzables
#define NEW_ARMA_GRAN crearArma(0, 100, 3, 0, "Granada")
#define NEW_ARMA_MONO crearArma(1, 40, 5, 1, "Molotov")
// Macros para Soldados
#define NEW_SOLD_COMA crearSoldado(200, "Comandante")
#define NEW_SOLD_TANK crearSoldado(150, "Tanque")
#define NEW_SOLD_VETE crearSoldado(100, "Veterano")
#define NEW_SOLD_NOVA crearSoldado(75, "Novato")
#define NEW_SOLD_APOY crearSoldado(50, "Apoyo")
// Macros para Curaciones
#define NEW_CURA_BOTI crearCuracion(100, "Botiquin")
#define NEW_CURA_VEND crearCuracion(20, "Vendaje")
#define NEW_CURA_PAST crearCuracion(10, "Pastillas")
#define NEW_CURA_INYE crearCuracion(15, "Inyeccion")

using namespace std;

struct Curacion {
  int cantidad_curacion;
  string nombre_curacion;
} curacion1, curacion2, curacion3, curacion4;

struct Zombie {
  int fortaleza_zombie;
  int damage_zombie;
  string nombre_zombie;
} zombie1, zombie2, zombie3, zombie4, zombie5;
struct ListaZombie {
  Zombie *zombie;
  ListaZombie *sig;
};

struct armas {
  int desgaste;
  int damage;
  int municion;
  int duraciondelarma;
  string todaslasarmas;
} armasdefuego, armasblancas, armascontundentes, armasarrojadizas,
    armasdeproyectiles;

struct listaCura {
  Curacion *curacion;
  listaCura *sig;
};
struct listaArmas {
  armas *arma;
  listaArmas *sig;
};

struct Inventario {
  listaCura *curas;
  listaArmas *armas;
};
struct Soldado {
  int vida_soldado;
  string nombre_soldado;
  Inventario *mochila;

} soldado1, soldado2, soldado3, soldado4, soldado5;
struct EquipoSoldado { // Igual que lista soldado
  Soldado *soldado;
  EquipoSoldado *sig;
};

// Funciones de curaciones

Curacion *crearCuracion(int cantidad, string nombre) {
  Curacion *curacion = new Curacion;
  curacion->cantidad_curacion = cantidad;
  curacion->nombre_curacion = nombre;
  return curacion;
};

void elimCuracion(Curacion *curacion) { delete curacion; };

void modificarCuracion(Curacion *curacion, int cantidad, string nombre) {
  curacion->cantidad_curacion = cantidad;
  curacion->nombre_curacion = nombre;
};
void mostrarCuracion(Curacion *curacion) {
  cout << "Nombre: " << curacion->nombre_curacion << "\n";
  cout << "Cantidad de curacion: " << curacion->cantidad_curacion << "\n";
};
void agregarAListaCura(listaCura **lista, Curacion *curacion) {
  listaCura *nuevo = new listaCura;
  nuevo->curacion = curacion;
  nuevo->sig = NULL;
  if (*lista == NULL) {
    *lista = nuevo;
  } else {
    listaCura *aux = *lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};

void eliminarListaCuracion(listaCura **lista) {
  listaCura *aux = *lista;
  while (aux != NULL) {
    listaCura *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *lista = NULL;
};
void mostrarListaCuracion(listaCura *lista) {
  listaCura *aux = lista;
  while (aux != NULL) {
    mostrarCuracion(aux->curacion);
    aux = aux->sig;
  }
  cout << "=========\n";
};

// Fin funciones de curaciones

// Funciones de zombies
Zombie *crearZombie(int def, int dmg, string nombre) {
  Zombie *zombie = new Zombie;
  zombie->fortaleza_zombie = def;
  zombie->damage_zombie = dmg;
  zombie->nombre_zombie = nombre;
  return zombie;
}

void elimZombie(Zombie *zombie) { delete zombie; }

void modificarZombie(Zombie *zombie, int def, int dmg, string nombre) {
  zombie->fortaleza_zombie = def;
  zombie->damage_zombie = dmg;
  zombie->nombre_zombie = nombre;
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
    cout << "Nombre: " << aux->zombie->nombre_zombie << "\n";
    cout << "Fortaleza: " << aux->zombie->fortaleza_zombie << "\n";
    cout << "Damage: " << aux->zombie->damage_zombie << "\n";
    cout << "=========\n";
    aux = aux->sig;
  }
};
// Fin de funciones de zombies

// Funciones de armas
armas *crearArma(int desgaste, int damage, int municion, int duracion,
                 string nombre) {
  armas *arma = new armas;
  arma->desgaste = desgaste;
  arma->damage = damage;
  arma->municion = municion;
  arma->duraciondelarma = duracion;
  arma->todaslasarmas = nombre;
  return arma;
};

void modificarArma(armas *arma, int desgaste, int damage, int municion,
                   int duracion, string nombre) {
  arma->desgaste = desgaste;
  arma->damage = damage;
  arma->municion = municion;
  arma->duraciondelarma = duracion;
  arma->todaslasarmas = nombre;
};

void eliminarArma(armas *arma) { delete arma; }
void mostrarArma(armas *arma) {
  cout << "Nombre: " << arma->todaslasarmas << "\n";
  cout << "Desgaste: " << arma->desgaste << "\n";
  cout << "Damage: " << arma->damage << "\n";
  cout << "Municion: " << arma->municion << "\n";
  cout << "Duracion del arma: " << arma->duraciondelarma << "\n";
  cout << "=========\n";
};
void agregarAListaArma(listaArmas **lista, armas *arma) {
  listaArmas *nuevo = new listaArmas;
  nuevo->arma = arma;
  nuevo->sig = NULL;
  if (*lista == NULL) {
    *lista = nuevo;
  } else {
    listaArmas *aux = *lista;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};
void eliminarListaArma(listaArmas **lista) {
  listaArmas *aux = *lista;
  while (aux != NULL) {
    listaArmas *borrar = aux;
    aux = aux->sig;
    delete borrar;
  }
  *lista = NULL;
};
void mostrarListaArmas(listaArmas *lista) {
  listaArmas *aux = lista;
  while (aux != NULL) {
    mostrarArma(aux->arma);
    aux = aux->sig;
  }
};
// Fin de funciones de armas
// Funciones de inventario
Inventario *crearInventario() {
  Inventario *inventario = new Inventario;
  inventario->curas = NULL;
  inventario->armas = NULL;
  return inventario;
}
bool tieneEspacio(Inventario *inventario) {
  listaCura *aux = inventario->curas;
  listaArmas *aux2 = inventario->armas;
  int contador = 0;
  while (aux != NULL) {
    contador++;
    if (contador == 3) {
      return false;
    }
    aux = aux->sig;
  }
  while (aux2 != NULL) {
    contador++;
    if (contador == 3) {
      return false;
    }
    aux2 = aux2->sig;
  }
  return true;
}
void eliminarInvetario(Inventario *inventario) {
  eliminarListaCuracion(&inventario->curas);
  eliminarListaArma(&inventario->armas);
  delete inventario;
}
// Fin de funciones de inventario

// Funciones de soldados
Soldado *crearSoldado(int vida, string nombre) {
  Soldado *soldado = new Soldado;
  soldado->vida_soldado = vida;
  soldado->nombre_soldado = nombre;
  soldado->mochila = new Inventario;
  return soldado;
};
Soldado *crearSoldado(int vida, string nombre, Inventario *mochila) {
  Soldado *soldado = new Soldado;
  soldado->vida_soldado = vida;
  soldado->nombre_soldado = nombre;
  soldado->mochila = mochila;
  return soldado;
};
void mostrarSoldado(Soldado *sold) {
  cout << "Nombre: " << sold->nombre_soldado << "\n";
  cout << "Vida: " << sold->vida_soldado << "\n";
  cout << "Inventario: \n";
  mostrarListaCuracion(sold->mochila->curas);
  mostrarListaArmas(sold->mochila->armas);
  cout << "=========\n";
}
void elimSoldado(Soldado *soldado) { delete soldado; };
void modificarSoldado(Soldado *soldado, int vida, string nombre) {
  soldado->vida_soldado = vida;
  soldado->nombre_soldado = nombre;
};

void modificarSoldado(Soldado *soldado, int vida) {
  soldado->vida_soldado = vida;
};
void agregarAEquipoSoldado(EquipoSoldado **equipo, Soldado *soldado) {
  EquipoSoldado *nuevo = new EquipoSoldado;
  nuevo->soldado = soldado;
  nuevo->sig = NULL;
  if (*equipo == NULL) {
    *equipo = nuevo;
  } else {
    EquipoSoldado *aux = *equipo;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
};
void eliminarEquipoSoldado(EquipoSoldado **equipo) {
  EquipoSoldado *aux = *equipo;
  while (aux != NULL) {
    EquipoSoldado *borrar = aux;
    aux = aux->sig;
    eliminarInvetario(borrar->soldado->mochila);
    delete borrar;
  }
  *equipo = NULL;
};
void mostrarEquipoSoldado(EquipoSoldado *equipo) {
  EquipoSoldado *aux = equipo;
  while (aux != NULL) {
    mostrarSoldado(aux->soldado);
    aux = aux->sig;
  }
};

// Fin funciones de soldados

void opc_equivocada() {
    cin.clear(); // Limpia el error de la opcion del usuario
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la opcion equicocada del usuario
}
 // fin funcion de opcion erronea 

int main() {
    int opciones;
    EquipoSoldado *equipo = NULL;
    ListaZombie *ListaZombie = NULL;

    do {
        cout << "======= Menu =======\n";
        cout << "1) Comenzar Juego\n";
        cout << "2) Ajustes\n";
        cout << "3) Salir\n";
        cout << "===================\n";
        cout << "Seleccione una opción: ";
        cin >> opciones;

        while (cin.fail() || opciones < 1 || opciones > 3) {
            opc_equivocada();
            cout << "Error, no es una opción válida. Intente nuevamente.\n";
            cout << "Seleccione una opción: ";
            cin >> opciones;
        }

        switch(opciones) {
            case 1:
                cout << "El juego comienza\n";
                cout << "Londres, 2024. Lo que comenzó como una serie de extraños síntomas en pequeñas comunidades a lo largo y ancho del país, pronto se reveló como una pesadilla global. Investigaciones preliminares apuntan a un incidente aéreo en el Canal de la Mancha, donde un cargamento altamente confidencial de patógenos modificados a partir del COVID-19 se habría dispersado en la atmósfera. La comunidad internacional se encuentra al borde del pánico, mientras expertos en salud pública y gobiernos intentan contener lo que parece ser una guerra biológica desatada accidentalmente.\n";
                cout << "La Dra. Emily Carter se encontraba en su laboratorio cuando recibió la llamada. Un nuevo virus, mucho más agresivo que cualquier otro conocido, estaba diezmando poblaciones enteras. Como viróloga experta, sabía que solo había una explicación: una fuga en uno de los laboratorios secretos que habían estado desarrollando armas biológicas. Sin embargo, cuando comenzó a investigar, se encontró con una conspiración mucho más profunda de lo que jamás había imaginado. Las grandes potencias habían estado jugando con fuego, y ahora el mundo entero estaba pagando las consecuencias.\n";
                cout << "Al principio, solo habíamos visto los zombies clásicos: lentos, torpes y fáciles de esquivar. Pero a medida que la infección se propagaba, comenzaron a surgir nuevas variantes. Los rápidos nos perseguían por las calles, los tanques derribaban las barricadas, y los inteligentes nos tendían emboscadas. Era como si el virus estuviera evolucionando, adaptándose a nuestras estrategias. Y lo peor de todo, habíamos empezado a ver zombies que brillaban en la oscuridad, como si fueran linternas vivientes. Pero ahora existían de distintos tipos.\n";
               
                int opcion1;
                cout << "Para continuar con el juego, por favor presiona 1: ";
                cin >> opcion1;

                while (cin.fail() || opcion1 != 1) {
                    opc_equivocada();
                    cout << "Error, no es una opción válida. Para poder empezar a jugar por favor presiona 1: ";
                    cin >> opcion1;
                }

                int opc_usuario1;
                do {
                    cout << "======= Juego =======\n";
                    cout << "1) Agregar Soldado\n";
                    cout << "2) Agregar Zombie\n";
                    cout << "3) Regresar al menú principal\n";
                    cout << "===================\n";
                    cout << "Seleccione una opción: ";
                    cin >> opc_usuario1;

                    while (cin.fail() || opc_usuario1 < 1 || opc_usuario1 > 3) {
                        opc_equivocada();
                        cout << "Error, no es una opción válida. Por favor selecciona una opción válida: ";
                        cin >> opc_usuario1;
                    }

                    switch(opc_usuario1) {
                        case 1:
                            cout << "¿Qué tipo de soldado desea agregar?\n4) Comandante\n5) Tanque\n6) Veterano\n7) Novato\n8) Apoyo\nSeleccione: ";
                            cin >> opciones;
                            while (cin.fail() || opciones < 4 || opciones > 8) {
                                opc_equivocada();
                                cout << "Error, no es una opción válida. Para agregar un soldado a tu escuadrón, por favor selecciona una opción correcta: ";
                                cin >> opciones;
                            }
                            switch (opciones) {
                                case 4:
                                    agregarAEquipoSoldado(&equipo, NEW_SOLD_COMA);
                                    break;
                                case 5:
                                    agregarAEquipoSoldado(&equipo, NEW_SOLD_TANK);
                                    break;
                                case 6:
                                    agregarAEquipoSoldado(&equipo, NEW_SOLD_VETE);
                                    break;
                                case 7:
                                    agregarAEquipoSoldado(&equipo, NEW_SOLD_NOVA);
                                    break;
                                case 8:
                                    agregarAEquipoSoldado(&equipo, NEW_SOLD_APOY);
                                    break;
                            }
                            mostrarEquipoSoldado(equipo);
                            break;
                        case 2:
                            cout << "¿Qué tipo de zombie desea agregar?\n4) Ágil y veloz\n5) Fuerte\n6) Inteligente\n7) Infectado por Hongos\n8) Bioluminiscente\nSeleccione: ";
                            cin >> opciones;
                            while (cin.fail() || opciones < 1 || opciones > 5) {
                                opc_equivocada();
                                cout << "Error, no es una opción válida. Si deseas agregar un zombie, por favor selecciona la opción correcta: ";
                                cin >> opciones;
                            }
                            switch (opciones) {
                                case 4:
                                    agregarAListaZombie(&ListaZombie, NEW_ZB_AGIL);
                                    break;
                                case 5:
                                    agregarAListaZombie(&ListaZombie, NEW_ZB_FUER);
                                    break;
                                case 6:
                                    agregarAListaZombie(&ListaZombie, NEW_ZB_INTE);
                                    break;
                                case 7:
                                    agregarAListaZombie(&ListaZombie, NEW_ZB_HONG);
                                    break;
                                case 8:
                                    agregarAListaZombie(&ListaZombie, NEW_ZB_BIOL);
                                    break;
                            }
                            mostrarListaZombie(ListaZombie);
                            break;
                        case 3:
                            cout << "Regresando al menú principal...\n";
                            break;
                    }
                    cout << "\n";
                } while(opc_usuario1 != 3);
                break;
            case 2:
                int opc_usuario2;
                do {
                    cout << "Entraste en los ajustes\n";
                    cout << "Por ahora estás en un modo demo del juego, así que no hay mucho que ver por aquí\n";
                    cout << "Presione 0 para regresar al menú principal: ";
                    cin >> opc_usuario2;
                    while (cin.fail() || opc_usuario2 != 0) {
                        opc_equivocada();
                        cout << "Error, no es una opción válida. Por favor presione 0: ";
                        cin >> opc_usuario2;
                    }
                } while(opc_usuario2 != 0);
                break;
            case 3:
                cout << "Espero le haya gustado el juego, ¡Hasta pronto!\n";
                break;
        }
        cout << "\n";
    } while(opciones != 3);

    eliminarEquipoSoldado(&equipo);
    eliminarListaZombie(&ListaZombie);

    return 0;
}
