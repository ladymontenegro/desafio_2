#include <iostream>
#include <string>
#include <fstream>

#include "funcionesAuxiliares.h"

using namespace std;

void guardarReservasEnArchivo(Anfitrion** anfitriones, unsigned short anfitrionesCargados) {
    ofstream archivo("reservas_vigentes.txt");

    //recorrer todos los anfitriones
    for (unsigned short i = 0; i < anfitrionesCargados; i++) {
        Anfitrion* anfitrion = anfitriones[i];
        Alojamiento** alojamientos = anfitrion -> getAlojamientos();

        unsigned short numAlojamientos = anfitrion -> getAlojamientosCargados();

        //recorrer cada alojamiento del anfitrion
        for (unsigned short j = 0; j < numAlojamientos; j++) {
            Alojamiento* alojamiento = alojamientos[j];
            ordenarReservasDeAlojamiento(alojamiento);

            //escribir bloque en el archivo, entonces inicia con el codigo del alojamiento
            archivo << alojamiento -> getCodigo() << endl;

            Reserva** reservas = alojamiento -> getReservas();
            unsigned short reservasCargadas = alojamiento -> getReservasCargadas();

            //escribir cada reserva ordenada
            for (unsigned short k = 0; k < reservasCargadas; k++) {
                archivo << reservas[k] -> reservaString() << endl;
            }
        }
    }
    archivo.close();
}

void moverReservasHistoricas(Fecha fechaActual, Reserva** reservasGlobales, unsigned short &totalReservasGlobales, Anfitrion** anfitriones, unsigned short anfitrionesCargados, Huesped** huespedes, unsigned short totalHuespedes) {

    //se hallan que reservas deben de ser cargadas al historico y se guardan en un arreglo temporal
    unsigned short contadorHistoricas = 0;
    Reserva** historicas = new Reserva*[totalReservasGlobales];

    for (unsigned short i = 0; i < totalReservasGlobales; i++) {
        if (reservasGlobales[i] -> getFechaFin() < fechaActual) {
            historicas[contadorHistoricas] = reservasGlobales[i];
            contadorHistoricas++;
        }
    }

    //ordenar por fechas las reservas
    mergeSort(historicas, 0, contadorHistoricas - 1);

    //escribir en el archivo con modo append pa que se agreguen al final
    ofstream archivo("historicas.txt", ios::app);
    for (unsigned short i = 0; i < contadorHistoricas; i++) {
        archivo << historicas[i] -> getAlojamiento() -> getCodigo() << "," << historicas[i] -> reservaString() << endl;
    }
    archivo.close();

    //eliminar las reservas movidas al historico en los arreglos de cada clase que lo tiene
    for (unsigned short i = 0; i < contadorHistoricas; i++) {
        bool reservaEliminada = eliminarReservaTodos((historicas[i] -> getCodigoReserva()), reservasGlobales, totalReservasGlobales);
    }

    //libero la memoria del arrerglo temporal
    delete[] historicas;
}
