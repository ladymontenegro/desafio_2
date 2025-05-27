#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void guardarReservasEnArchivo(Anfitrion** anfitriones, int totalAnfitriones) {
    ofstream archivo("reservas_activas.txt");

    // Recorrer todos los anfitriones
    for (int i = 0; i < totalAnfitriones; i++) {
        Anfitrion* anfitrion = anfitriones[i];
        Alojamiento** alojamientos = anfitrion  ->  getAlojamientos();

        int numAlojamientos = anfitrion -> getCantidadAlojamientos();

        //recorrer cada alojamiento del anfitrion
        for (int j = 0; j < numAlojamientos; j++) {
            Alojamiento* alojamiento = alojamientos[j];
            ordenarReservasDeAlojamiento(alojamiento);

            //escribir bloque en el archivo
            archivo << alojamiento -> getCodigo() << endl;

            Reserva** reservas = alojamiento -> getReservas();
            int numReservas = alojamiento -> getCantidadReservas();

            //escribir cada reserva ordenada
            for (int k = 0; k < numReservas; k++) {
                string lineaReserva = "";
                archivo << lineaReserva << endl;
            }
        }
    }

    archivo.close();
}

void ordenarReservasDeAlojamiento(Alojamiento* alojamiento) {
    int numReservas = alojamiento -> getCantidadReservas();
    Reserva** reservas = alojamiento -> getReservas();

    // Algoritmo de ordenamiento bubble Sort
    for (int i = 0; i < numReservas - 1; i++) {
        for (int j = 0; j < numReservas - i - 1; j++) {
            if (reservas[j]  ->  getFechaEntrada() > reservas[j + 1]  ->  getFechaEntrada()) {
                // Intercambiar punteros
                Reserva* temp = reservas[j];
                reservas[j] = reservas[j + 1];
                reservas[j + 1] = temp;
            }
        }
    }
}
