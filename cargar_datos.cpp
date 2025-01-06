// Solo para cargar datos de los datosAccivos .zmb
#include "entidades/map.cpp"
#include "entidades/soldado.cpp" // Incluye el archivo de Mochila y este a su vez el de objeto
#include "entidades/zombie.cpp"
#include <fstream>
#include <sstream>
#include <string.h>

char ACC_CONF_PATH[] = "datos/Accesorio.zmb";
char MAP_CONF_PATH[] = "datos/Mapa.zmb";
char SOLD_CONF_PATH[] = "datos/Soldado.zmb";
char ZMB_CONF_PATH[] = "datos/Zombie.zmb";

bool existe(char path[]) {
  FILE *datosAcc = fopen(path, "r");
  if (datosAcc) {
    fclose(datosAcc);
    return true;
  }
  return false;
}

// Cargar zombie
ListaZombie *cargarZombies(void) {
  ListaZombie *lista = NULL;

  if (!existe(ZMB_CONF_PATH)) {
    std::cout << "No existe el archivo de zombie\n";

    return NULL;
  }

  std::string linea;
  std::ifstream datosZmb;
  int cont;

  datosZmb.open(ZMB_CONF_PATH);
  std::getline(datosZmb, linea);
  cont = stoi(linea);

  Zombie *zmb;

  std::string nombre;
  int dmg, def;
  for (int i = 0; i < cont; i++) {

    std::getline(datosZmb, linea); // quitar el --- de los cojones

    std::getline(datosZmb, linea);
    nombre = linea;
    nombre.pop_back(); // Mrc esta mierda me daba unos errores locos por el
                       // caracter de retorno ajjaja

    std::getline(datosZmb, linea);

    dmg = stoi(linea);

    std::getline(datosZmb, linea);
    def = stoi(linea);

    zmb = crearZombie(def, dmg, nombre);
    agregarAListaZombie(&lista, zmb);
  }

  datosZmb.close();
  return lista;
}
//

// Cargar Lista de Objetos
Mochila *cargarObjetos(void) {
  if (!existe(ACC_CONF_PATH)) {
    std::cout << "No existe el archivo de accesorios" << std::endl;
    return NULL;
  }
  std::string linea, nombre, categoria;
  int usos, valor, cant;
  Mochila *Mochila = NULL;
  Objeto *obj;
  std::ifstream datosAcc;
  datosAcc.open(ACC_CONF_PATH);

  getline(datosAcc, linea);

  cant = stoi(linea);
  for (int i = 0; i < cant; i++) {
    getline(datosAcc, linea);
    getline(datosAcc, linea);
    getline(datosAcc, linea);
    nombre = linea;
    nombre.pop_back();

    getline(datosAcc, linea);
    categoria = linea;
    categoria.pop_back();

    getline(datosAcc, linea);
    valor = stoi(linea);

    getline(datosAcc, linea);
    usos = stoi(linea);
    int id = i + 1;
    obj = crearObjeto(nombre, categoria, usos, valor, id);
    agregarAMochila(&Mochila, obj);
  }
  datosAcc.close();
  return Mochila;
}
//

// Cargar Soldados Disponibles
ListaSoldado *cargarSoldados(void) {
  if (!existe(SOLD_CONF_PATH)) {
    std::cout << "No existe el archivo de soldados\n";
    return NULL;
  }

  ListaSoldado *lista = NULL;

  Soldado *soldado;
  std::string linea, nombre;
  int salud, cant;

  std::ifstream datosSold;
  datosSold.open(SOLD_CONF_PATH);

  getline(datosSold, linea);

  cant = stoi(linea);

  for (int i = 0; i < cant; i++) {
    getline(datosSold, linea); // Quitar el ---

    getline(datosSold, linea);
    nombre = linea;
    nombre.pop_back();

    getline(datosSold, linea);
    salud = stoi(linea);

    soldado = crearSoldado(salud, 0, nombre);

    agregarAListaSoldado(&lista, soldado);
  }
  datosSold.close();

  return lista;
}
//
//
//
std::vector<nodo *> cargarGrafo() {
  std::ifstream file(MAP_CONF_PATH);
  std::string line;
  std::vector<nodo *> graph;
  std::map<int, nodo *> nodeMap;

  if (!file.is_open()) {
    std::cerr << "No se pudo abrir el archivo: " << MAP_CONF_PATH << std::endl;
    return graph;
  }

  int nodeCount;
  std::getline(file, line);
  nodeCount = std::stoi(line);

  while (std::getline(file, line)) {
    if (line == "---") {
      int nodeId;
      std::getline(file, line);
      nodeId = std::stoi(line);

      nodo *newNode = agregarnodo(nodeId);
      graph.push_back(newNode);
      nodeMap[nodeId] = newNode;

      std::getline(file, line); // Skip the '-'

      while (std::getline(file, line) && line != "--") {
        // Process zombie data if needed
      }

      std::getline(file, line); // Skip the '--'

      while (std::getline(file, line) && line != "---") {
        std::istringstream iss(line);
        std::string edge;
        while (std::getline(iss, edge, '|')) {
          int dest, weight;
          sscanf(edge.c_str(), "%d:%d", &dest, &weight);
          addaristas(newNode, nodeMap[dest], weight);
        }
      }
    }
  }

  file.close();
  return graph;
}
