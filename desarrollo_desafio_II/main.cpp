#include <iostream>
#include "funcionesAuxiliares.h"
#include "variablesIteracionesMemoria.h"
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

    unsigned short anfitrionesCargados = cargarDatosAnfitriones(rutaAnfitriones, arregloAnfitriones);
    unsigned short huespedesCargados = cargarDatosHuespedes(rutaHuespedes, arregloHuespedes);
    unsigned short reservasCargadas = cargarDatosReservas(rutaReservas, arregloReservasGlobales, arregloAnfitriones, arregloHuespedes, anfitrionesCargados, huespedesCargados);

    cout << "Todo cargo " << reservasCargadas << endl;

    unsigned short indiceUsuario = 0;
    while(true){
        char esUsuario = tipoUsuario(arregloHuespedes, arregloAnfitriones, indiceUsuario, anfitrionesCargados, huespedesCargados);

        if(esUsuario == '1'){
            Anfitrion* anfitrionActual = arregloAnfitriones[indiceUsuario];
            menuAnfitrion(anfitrionActual, arregloAnfitriones,arregloReservasGlobales, reservasCargadas, anfitrionesCargados);
            break;
        } else if(esUsuario == '2'){
            Huesped* huespedActual = arregloHuespedes[indiceUsuario];
            menuHuesped(arregloAnfitriones, arregloReservasGlobales, huespedActual, reservasCargadas, anfitrionesCargados);
            break;
        } else {
            cout << "Usuario no encontrado. Intente de nuevo" << endl;
        }
    }

    return 0;
}
