#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string obtenerDato(const string& linea, size_t& inicio) {
    size_t fin = linea.find(',', inicio);
    string atributo;

    if (fin != string::npos) { // si se encontro una coma
        atributo = linea.substr(inicio, fin - inicio);
        inicio = fin + 1; // actualiza el inicio para el proximo atributo, por eso se pasa por referencia
    } else { // pa que igual tome el ultimo atributo que no tiene coma
        atributo = linea.substr(inicio);
        inicio = linea.length(); // evita procesar mas atributos
    }
    return atributo;
}
