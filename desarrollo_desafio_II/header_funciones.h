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

//FUNCIONES DE CARGA DE DATOS
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion**& arregloAnfitriones);
int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes);
int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes);


#endif // HEADER_FUNCIONES_H
