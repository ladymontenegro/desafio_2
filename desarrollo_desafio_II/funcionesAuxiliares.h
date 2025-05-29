#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include "alojamiento.h"
#include "anfitrion.h"
#include "fecha.h"
#include "huesped.h"
#include "reserva.h"

//FUNCIONES DE MENUS
void menuAnfitrion(Anfitrion *anfitrionActual, Anfitrion **arregloAnfitriones, Reserva **arregloReservasGlobales, unsigned short &totalReservasGlobales, unsigned short anfitrionesCargados);
void menuHuesped(Anfitrion **&arregloAnfitriones,Reserva **&arregloReservasGlobales, Huesped* huespedActual, unsigned short &reservasCargadas, unsigned short anfitrionesCargados);
void opcion1(Anfitrion *anfitrionActual, Anfitrion **arregloAnfitriones, Reserva **arregloReservasGlobales, unsigned short &totalReservasGlobales, unsigned short anfitrionesCargados);
void opcion2(Anfitrion *anfitrionActual);

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio, char delimitador, bool esCampoObligatorio = true);
Fecha crearFecha(const string &fechaStr);
bool eliminarReservaTodos(const string &codigoReserva, Reserva **&arregloReservasGlobal, unsigned short &reservasCargadas);
bool crearReservaTodos(Reserva** arregloReservasGlobales, unsigned short &reservasCargadas, Anfitrion** arregloAnfitriones,
                       Fecha fechaEntrada, Huesped* huespedActual, unsigned short estadiaNoches, unsigned short indiceAlojamiento, unsigned short indiceAnfitrion);
size_t calcularMemoriaTotal(unsigned short anfitrionesCargados, unsigned short huespedesCargados, unsigned short reservasCargadas,
                            Anfitrion** arregloAnfitriones, Huesped** arregloHuespedes, Reserva** arregloReservasGlobales,
                            unsigned short capacidadAnfitriones, unsigned short capacidadHuespedes, unsigned short capacidadReservasGlobales);
template<typename T>
void redimensionarArreglo(unsigned short& capacidad, unsigned short elementosCargados, T**& arreglo);

//FUNCIONES DE VALIDACION
bool esDocumento(const string& linea, size_t& inicio);
bool es_digito_manual(char c);
bool validarNumero(string &cadena);
char tipoUsuario(Huesped **&arregloHuespedes, Anfitrion **& arregloAnfitriones, unsigned short &indice, unsigned short anfitrionesCargados, unsigned short huespedesCargados);

//FUNCIONES DE BUSQUEDA
short buscarHuespedPorDocumento(Huesped**& arregloHuespedes, const string &documento, unsigned short cantidadHuespedes, bool &encontrado);
bool buscarAlojamientoPorCodigo(Anfitrion**& arregloAnfitriones, const string &codigo, unsigned short cantidadAnfitriones, short &indiceAnfitrion, short &indiceAlojamiento);
bool filtroReservas(Anfitrion **&arregloAnfitriones, const unsigned short &anfitrionesCargados, const string &municipio, const Fecha &fecha, const unsigned short &cantidadDeNoches,
                    const unsigned int &costoMaximo = 0, const float &puntajeMinimo = 0, bool buscarPorCosto = false, bool buscarPorPuntaje = false);

//FUNCIONES DE ORDENAMIENTO DE DATOS
void mergeSort(Reserva** reservas, unsigned short izquierda, unsigned short derecha);
void mezclar(Reserva** reservas, unsigned short izquierda, unsigned short medio, unsigned short derecha);
void ordenarReservasDeAlojamiento(Alojamiento* alojamiento);

//FUNCIONES DE CARGA DE DATOS
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion**& arregloAnfitriones, unsigned short capacidadAnfitriones);
int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes, unsigned short capacidadHuespedes);
int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes, unsigned short capacidadReservasGlobales);

//FUNCIONES DE CARGA DE ARCHIVOS
void guardarReservasEnArchivo(Anfitrion** arregloAnfitriones, unsigned short anfitrionesCargados);
void moverReservasHistoricas(Fecha fechaActual, Reserva** reservasGlobales, unsigned short &reservasCargadas);

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

#endif // FUNCIONESAUXILIARES_H
