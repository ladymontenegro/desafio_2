#ifndef HEADER_FUNCIONES_H
#define HEADER_FUNCIONES_H

#include <iostream>
#include <string>

using namespace std;

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio, const char delimitador);
bool esDocumento(const string& linea, size_t& inicio);
short buscarHuespedPorDocumento(Huesped**& arregloHuespedes, const string &documento, unsigned short cantidadHuespedes);
bool buscarAlojamientoPorCodigo(Anfitrion**& arregloAnfitriones, const string &codigo, short cantidadAnfitriones, short &indiceAnfitrion, short &indiceAlojamiento);
Fecha crearFecha(const string &fechaStr);

template<typename T>
void redimensionarArreglo(unsigned short& capacidad, unsigned short elementosCargados, T**& arreglo);

//FUNCIONES DE CARGA DE DATOS
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion**& arregloAnfitriones);
int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes);
int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes);


//Implementacion de la plantilla
template<typename T>
void redimensionarArreglo(unsigned short& capacidad, unsigned short elementosCargados, T**& arreglo) {
    unsigned short nuevaCapacidad = capacidad * 2;
    T** nuevoArreglo = new T*[nuevaCapacidad];

    for (unsigned short i = 0; i < elementosCargados; i++) {
        nuevoArreglo[i] = arreglo[i];
    }

    for (unsigned short i = elementosCargados; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] arreglo;
    arreglo = nuevoArreglo;
    capacidad = nuevaCapacidad;
}
#endif // HEADER_FUNCIONES_H
