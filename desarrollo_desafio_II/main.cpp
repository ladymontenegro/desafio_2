#include <iostream>
#include "funcionesAuxiliares.h"
using namespace std;

int main()
{
    cout << "Rutas" << endl;

    string rutaAnfitriones = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/alojamientos_anfitriones.txt";
    string rutaHuespedes = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/huespedes.txt";
    string rutaReservas = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/reservas_vigentes.txt";

    cout << "Punteros" << endl;

    Anfitrion** arregloAnfitriones = {nullptr};
    Huesped** arregloHuespedes = {nullptr};
    Reserva** arregloReservasGlobales = {nullptr};

    cout << "Carga" << endl;

    short anfitrionesCargados = cargarDatosAnfitriones(rutaAnfitriones, arregloAnfitriones);
    short huespedesCargados = cargarDatosHuespedes(rutaHuespedes, arregloHuespedes);
    short reservasCargadas = cargarDatosReservas(rutaReservas, arregloReservasGlobales, arregloAnfitriones, arregloHuespedes, anfitrionesCargados, huespedesCargados);

    cout << "Todo cargo " << reservasCargadas << endl;

    unsigned short indiceUsuario = 0;
    while(true){
        char esAnfitrion = tipoUsuario(arregloHuespedes, arregloAnfitriones, indiceUsuario, anfitrionesCargados, huespedesCargados);

        if(esAnfitrion == '1'){
            menuAnfitrion(arregloAnfitriones, indiceUsuario);
            break;
        } else if(esAnfitrion == '2'){
            menuHuesped(arregloHuespedes, arregloReservasGlobales, indiceUsuario, reservasCargadas);
            break;
        } else {
            cout << "Usuario no encontrado. Intente de nuevo" << endl;
        }
    }

    return 0;
}
