#include "alojamiento.h"
#include "anfitrion.h"
#include "fecha.h"
#include "reserva.h"
#include <iostream>
#include <string>
#include "funcionesAuxiliares.h"
using namespace std;

void menuAnfitrion(Anfitrion **arregloAnfitriones,
                   unsigned short indiceAnfitrion,
                   Reserva **arregloReservasGlobales,
                   unsigned short &totalReservasGlobales)
{
    while (true) {
        cout << "---MENU ANFITRIONES---" << endl;
        cout << "1. Anular una reservacion" << endl;
        cout << "2. Consultar reservaciones" << endl;
        cout << "3. Salir" << endl;
        cout << "Escoja una opcion: ";
        string opcion;
        cin >> opcion;
        cout << endl;
        if (opcion != "1" && opcion != "2" && opcion != "3") {
            cout << "Opcion invalida. Ingrese un numero del 1 al 3 " << endl;
        } else {
            if (opcion == "3") {
                string fechaCorte = "";
                while (true) {
                    cout << "Para salir por favor ingrese la fecha del dia de hoy (DD-MM-AAAA): ";
                    cin.ignore(1000, '\n');
                    getline(cin, fechaCorte);
                    try {
                        Fecha fechaCorte = crearFecha(fechaCorte);
                        break;
                    } catch (const invalid_argument &excepcion) {
                        cerr << "Fecha invalida. Intente de nuevo por favor" << excepcion.what() << endl;
                    } catch (const runtime_error &excepcion) {
                        cerr << "Error de ejcucion. Intente de nuevo por favor" << excepcion.what() << endl;
                    } catch (const exception &excepcion) {
                        cerr << "Ha ocurrido un error desconocido: " << excepcion.what() << endl;
                    }
                }
                moverReservasHistoricas(fechaCorte, arregloReservasGlobales, totalReservasGlobales);
                cout << "Saliendo del menu de anfitriones" << endl;
                break;
            } else if (opcion == "1") {
                while (true) {
                    opcion1(arregloAnfitriones, indiceAnfitrion);
                    cout << "Desea anular otra reserva? (y/n): ";
                    string continuarAnulando;
                    while (true) {
                        cin >> continuarAnulando;
                        if (continuarAnulando != "y" && continuarAnulando != "n") {
                            cout << "Opcion invalida. Ingrese 'y'(si) o 'n'(no): ";
                        } else {
                            break;
                        }
                    }
                    if (continuarAnulando == "n") {
                        cout << endl << endl;
                        break;
                    }
                }
            } else if (opcion == "2") {
                cout << "Sus alojamientos son:" << endl;
                opcion2(arregloAnfitriones, indiceAnfitrion);
                cout << endl << endl;
            }
        }
    }
}

void opcion1(Anfitrion **arregloAnfitriones, unsigned short indiceAnfitrion)
{
    Anfitrion *anfitrionActual = arregloAnfitriones[indiceAnfitrion];

    // Mostrar todos los alojamientos del anfitrion
    cout << "\n--- Alojamientos del anfitrion ---" << endl;
    if (anfitrionActual->getAlojamientosCargados() == 0) {
        cout << "El anfitrion no tiene alojamientos registrados." << endl;
        return;
    }
    for (unsigned short i = 0; i < anfitrionActual->getAlojamientosCargados(); ++i) {
        anfitrionActual->getAlojamiento(i)->mostrarAlojamiento();
    }

    // Pedir codigo de alojamiento y buscarlo
    cout << "\nIngrese el codigo del alojamiento que desea gestionar: ";
    string codigoAlojamientoSeleccionado;
    cin >> codigoAlojamientoSeleccionado;

    Alojamiento *alojamientoEncontrado = nullptr;
    for (unsigned short i = 0; i < anfitrionActual->getAlojamientosCargados(); ++i) {
        Alojamiento *currentAlojamiento = anfitrionActual->getAlojamiento(i);
        if (currentAlojamiento != nullptr
            && currentAlojamiento->getCodigo() == codigoAlojamientoSeleccionado) {
            alojamientoEncontrado = currentAlojamiento;
            break; // Alojamiento encontrado, salir del bucle
        }
    }

    if (alojamientoEncontrado == nullptr) {
        cout << "Alojamiento con codigo '" << codigoAlojamientoSeleccionado << "' no encontrado."
             << endl;
        return; // Salir de la funcion si el alojamiento no existe
    }

    if (alojamientoEncontrado->getReservasCargadas() == 0) {
        cout << "No hay reservas para este alojamiento." << endl;
        return;
    }

    // Mostrar reservas del alojamiento encontrado
    cout << "\n--- Sus reservas para el alojamiento '" << alojamientoEncontrado->getCodigo()
         << "' ---" << endl;
    for (unsigned short j = 0; j < alojamientoEncontrado->getReservasCargadas(); ++j) {
        Reserva **reservasAlojamiento = alojamientoEncontrado->getReservas();
        if (reservasAlojamiento != nullptr && reservasAlojamiento[j] != nullptr) {
            reservasAlojamiento[j]->mostrarReserva();
        }
    }

    // Pedir codigo de reserva a anular y buscarla/eliminarla
    cout << "\nEscriba por favor el codigo de la reserva que desea anular: ";
    string codigoReservaAnular;
    cin >> codigoReservaAnular;

    // Aqui se llama al metodo eliminarReserva en el alojamiento especifico
    bool eliminada = alojamientoEncontrado->eliminarReserva(codigoReservaAnular);

    if (eliminada) {
        cout << "Reserva eliminada exitosamente." << endl;
    } else {
        cout << "No se encontro la reserva con el codigo '" << codigoReservaAnular
             << "' en este alojamiento." << endl;
    }
    cout << endl;
}

void opcion2(Anfitrion **arregloAnfitriones, unsigned short indiceAnfitrion)
{
    Anfitrion *anfitrionActual = arregloAnfitriones[indiceAnfitrion];

    cout << "\n--- Consulta de Reservas por Alojamiento ---" << endl;
    if (anfitrionActual->getAlojamientosCargados() == 0) {
        cout << "El anfitrion no tiene alojamientos registrados para consultar." << endl;
        return;
    }

    // Iterar sobre cada alojamiento del anfitrion
    for (unsigned short i = 0; i < anfitrionActual->getAlojamientosCargados(); ++i) {
        Alojamiento *currentAlojamiento = anfitrionActual->getAlojamiento(i);

        if (currentAlojamiento != nullptr) {
            // Mostrar codigo y nombre del alojamiento
            cout << "\n---------------------------------------------------" << endl;
            cout << "Alojamiento: " << currentAlojamiento->getNombre()
                 << " (Codigo: " << currentAlojamiento->getCodigo() << ")" << endl;
            cout << "---------------------------------------------------" << endl;

            // Mostrar las reservas de este alojamiento
            if (currentAlojamiento->getReservasCargadas() == 0) {
                cout << "  No hay reservas registradas para este alojamiento." << endl;
            } else {
                Reserva **reservasDelAlojamiento = currentAlojamiento->getReservas();
                for (unsigned short j = 0; j < currentAlojamiento->getReservasCargadas(); ++j) {
                    if (reservasDelAlojamiento != nullptr && reservasDelAlojamiento[j] != nullptr) {
                        reservasDelAlojamiento[j]->mostrarReserva();
                    }
                }
            }
        }
    }
    cout << "\n--- Fin de la consulta de reservas ---" << endl;
    cout << endl;
}
