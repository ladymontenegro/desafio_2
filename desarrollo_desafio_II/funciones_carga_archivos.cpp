#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//FUNCIONES AUXILIARES
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

bool esDocumento(const string& lineaArchivo, size_t& inicio){
    bool documento = false;
    size_t fin = lineaArchivo.find(',', inicio);
    string identificador = lineaArchivo.substr(inicio, fin - inicio);

    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool puedeAgregar(short cantidadActual, short limite) { //funcion de monitoreo de tamanio
    return cantidadActual < limite;
}
