#include <string>
struct Objeto {
  std::string nombre;
  std::string categoria;
  int usos;
  int valor; // Si es arma seria el danio si es de supervivencia la cantidad de
  int id;
};

Objeto *crearObjeto(std::string nombre, std::string categoria, int usos,
                    int valor, int id) {
  Objeto *objeto = new Objeto;
  objeto->nombre = nombre;
  objeto->categoria = categoria;
  objeto->usos = usos;
  objeto->valor = valor;
  objeto->id = id;
  return objeto;
}
