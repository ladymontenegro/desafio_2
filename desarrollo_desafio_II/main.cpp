#include <iostream>
#include "funcionesAuxiliares.h"
#include "variablesIteracionesMemoria.h"
using namespace std;

int main()
{
    string rutaAnfitriones = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/alojamientos_anfitriones.txt";
    string rutaHuespedes = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/huespedes.txt";
    string rutaReservas = "C:/Users/DELL/Documents/universidad/segundo_semestre/informatica_II/prueba_desafio_II/reservas_vigentes.txt";

    Anfitrion** arregloAnfitriones = {nullptr};
    Huesped** arregloHuespedes = {nullptr};
    Reserva** arregloReservasGlobales = {nullptr};

    unsigned short capacidadAnfitriones = 40;
    unsigned short capacidadHuespedes = 70;
    unsigned short capacidadReservasGlobales = 150;

    unsigned short anfitrionesCargados = cargarDatosAnfitriones(rutaAnfitriones, arregloAnfitriones, capacidadAnfitriones);
    unsigned short huespedesCargados = cargarDatosHuespedes(rutaHuespedes, arregloHuespedes, capacidadHuespedes);
    unsigned short reservasCargadas = cargarDatosReservas(rutaReservas, arregloReservasGlobales, arregloAnfitriones, arregloHuespedes, anfitrionesCargados, huespedesCargados, capacidadReservasGlobales);

    Globales::acumuladorMemoria = calcularMemoriaTotal(anfitrionesCargados, huespedesCargados, reservasCargadas, arregloAnfitriones, arregloHuespedes, arregloReservasGlobales, capacidadAnfitriones, capacidadHuespedes, capacidadReservasGlobales);
    float memoriaKB = (static_cast<float>(Globales::acumuladorMemoria)/1024);
    cout << "El espacio de memoria ocupado por los objetos y estructuras es: " << memoriaKB << "KB" << endl;

    unsigned short indiceUsuario = 0;
    while(true){
        Globales::contadorIteraciones++;
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

    Globales::acumuladorMemoria = calcularMemoriaTotal(anfitrionesCargados, huespedesCargados, reservasCargadas, arregloAnfitriones, arregloHuespedes, arregloReservasGlobales, capacidadAnfitriones, capacidadHuespedes, capacidadReservasGlobales);
    memoriaKB = (static_cast<float>(Globales::acumuladorMemoria)/1024);
    cout << "\nEl espacio de memoria ocupado por los objetos y estructuras antes de liberacion de memoria: " << memoriaKB << "KB" << endl;

    //liberar memoria
    if (arregloReservasGlobales != nullptr) {
        for (unsigned short i = 0; i < reservasCargadas; ++i) {
            Globales::contadorIteraciones++;
            if (arregloReservasGlobales[i] != nullptr) {
                delete arregloReservasGlobales[i];
            }
        }
        delete[] arregloReservasGlobales;
    }

    if (arregloHuespedes != nullptr) {
        for (unsigned short i = 0; i < huespedesCargados; ++i) {
            Globales::contadorIteraciones++;
            if (arregloHuespedes[i] != nullptr) {
                delete arregloHuespedes[i];
            }
        }
        delete[] arregloHuespedes;
    }

    if (arregloAnfitriones != nullptr) {
        for (unsigned short i = 0; i < anfitrionesCargados; ++i) {
            Globales::contadorIteraciones++;
            if (arregloAnfitriones[i] != nullptr) {
                delete arregloAnfitriones[i];
            }
        }
        delete[] arregloAnfitriones;
    }

    cout << "\n\n";
    cout << "TOTAL DE ITERACIONES DEL PROGRAMA: " << Globales::contadorIteraciones << endl;
    cout << "TOTAL APARICIONES METODO FIND (Con complejidad O(n)): " << Globales::contadorFind << endl;
    cout << "TOTAL APARICIONES METODO TO_STRING (Con complejidad O(1), Flotantes -> O(log n)): " << Globales::contadorTo_String << endl;
    cout << "TOTAL APARICIONES METODO SUBSTR (Con complejidad O(n)): " << Globales::contadorSubstr << endl;
    cout << "TOTAL APARICIONES METODO STOI (Con complejidad O(1)): " << Globales::contadorStoi << endl;
    cout << "TOTAL APARICIONES METODO STOF (Con complejidad O(n)): " << Globales::contadorStof << endl;
    cout << "TOTAL APARICIONES METODO LENGTH (Con complejidad O(1)): " << Globales::contadorLength << endl;
    cout << "TOTAL APARICIONES METODO EMPTY (Con complejidad O(1)): " << Globales::contadorEmpty << endl;

    return 0;
}
