#include <algorithm>
#include <iostream>
bool esNumero(std::string opcion) {
  return (
      std::all_of(opcion.begin(), opcion.end(),
                  ::isdigit)); // Verifica si todos los caracteres son digitos
}

void limpiarBuffer() {
  std::cin.ignore();
  std::cin.clear();
}
