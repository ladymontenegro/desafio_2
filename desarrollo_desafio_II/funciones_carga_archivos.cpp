#include <iostream>
#include <string>
#include <fstream>

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

void ordenarReservasDeAlojamiento(Alojamiento* alojamiento) {
    unsigned short reservasCargadas = alojamiento -> getReservasCargadas();
    Reserva** reservas = alojamiento -> getReservas();

    //se ordenan las reservas
    mergeSort(reservas, 0, reservasCargadas - 1);
}

void moverReservasHistoricas(Fecha fechaActual, Reserva** reservasGlobales, unsigned short &totalReservasGlobales,
    Anfitrion** anfitriones, unsigned short anfitrionesCargados, Huesped** huespedes, unsigned short totalHuespedes) {

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
        bool reservaEliminada = eliminarReservaTodos(historicas[i] -> getCodigo, reservasGlobales, totalReservasGlobales);
    }

    //libero la memoria del arrerglo temporal
    delete[] historicas;
}

void mergeSort(Reserva** reservas, unsigned short izquierda, unsigned short derecha) {
    if (izquierda < derecha) {
        unsigned short medio = izquierda + (derecha - izquierda) / 2;

        //ordenar primera y segunda mitad
        mergeSort(reservas, izquierda, medio);
        mergeSort(reservas, medio + 1, derecha);

        //mezclar las mitades ordenadas
        mezclar(reservas, izquierda, medio, derecha);
    }
}

void mezclar(Reserva** reservas, unsigned short izquierda, unsigned short medio, unsigned short derecha) {
    //tamanio de los subarreglos temporal
    unsigned short n1 = medio - izquierda + 1;
    unsigned short n2 = derecha - medio;

    //crear arreglos temporales dinámicos
    Reserva** izquierdaArr = new Reserva*[n1];
    Reserva** derechaArr = new Reserva*[n2];

    //copir datos a los arreglos temporales, son punteros, asi que aja
    for (unsigned short i = 0; i < n1; i++) {
        izquierdaArr[i] = reservas[izquierda + i];
    }
    for (unsigned short j = 0; j < n2; j++) {
        derechaArr[j] = reservas[medio + 1 + j];
    }

    //indices para recorrer los subarreglos
    unsigned short i = 0, j = 0, k = izquierda;

    //mezclar los subarreglos en el arreglo principal
    while (i < n1 && j < n2) {
        if (izquierdaArr[i] -> getFechaInicio() <= derechaArr[j] -> getFechaInicio()) {
            reservas[k] = izquierdaArr[i];
            i++;
        } else {
            reservas[k] = derechaArr[j];
            j++;
        }
        k++;
    }
    //copiar elementos restantes de izquierdaArr (si los hay)
    while (i < n1) {
        reservas[k] = izquierdaArr[i];
        i++;
        k++;
    }
    //copiar elementos restantes de derechaArr (si los hay)
    while (j < n2) {
        reservas[k] = derechaArr[j];
        j++;
        k++;
    }
    //liberar memoria de los arreglos temporales
    delete[] izquierdaArr;
    delete[] derechaArr;
}
