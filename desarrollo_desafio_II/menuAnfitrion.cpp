#include <iostream>
#include <string>
using namespace std;

void menuAnfitrion()
{
    int fechaHoy;

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
            cout << "Opcion invalida. Ingrese un numero del 1 al 3 ";
        } else {
            if (opcion == "3") {
                cout << "Para salir por favor ingrese la fecha del dia de hoy: ";
                while (true) {
                    cout << "Para salir por favor ingrese la fecha del dia de hoy: ";
                    cin >> fechaHoy;
                    try {
                        Fecha fechaCorte = crearFecha(fechaHoy);
                        break;
                    } catch (const invalid_argument &excepcion) {
                        cerr << "Fecha invalida. Intente de nuevo por favor" << excepcion.what()
                             << " Intente de nuevo" << endl;
                    } catch (const runtime_error &excepcion) {
                        cerr << "Erro de ejcucion. Intente de nuevo por favor" << excepcion.what()
                             << " Intente de nuevo" << endl;
                    } catch (const exception &excepcion) {
                        cerr << "A ocurrido un error desconocido: " << excepcion.what()
                             << " Intente de nuevo" << endl;
                    }
                }
                cout << "Saliendo del menu de anfitriones" << endl;
                break;
            } else if (opcion == "1") {
                while (true) {
                    for (unsigned short i = 0;
                         i < arregloAnfitriones[indiceAnfitrion]->getAlojamientosCargados;
                         i++) {
                        arregloAnfitriones[indiceAnfitrion]->getAlojamiento(i)->mostrarAlojamiento();
                    }
                    cout << "Ingrese el codigo del alojamiento que desea ver las reservas: ";
                    string codigoAlojamiento;
                    cin >> codigoAlojamiento;
                    cout << "Sus reservas son:" << endl;
                    for (unsigned short i = 0;
                         i < arregloAnfitriones[indiceAnfitrion]->getAlojamientosCargados;
                         i++) {
                        if (arregloAnfitriones[indiceAnfitrion]->getAlojamiento(i)->getCodigo
                            == codigoAlojamiento) {
                            for (unsigned short j = 0; j < arregloAnfitriones[indiceAnfitrion]
                                                               ->getAlojamiento(i)
                                                               ->getReservasCargadas;
                                 j++) {
                                Reserva **reservasAlojamiento = arregloAnfitriones[indiceAnfitrion]
                                                                    ->getAlojamiento(i)
                                                                    ->getReservas();
                                reservasAlojamiento[j]->mostarReserva;
                            }
                        }
                    }
                    cout << "Escriba por favor el codigo de la reserva que desea anular: ";
                    string codigoReserva;
                    cin >> codigoReserva;
                    cout << "Reserva eliminada" << endl;
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
                cout << "Sus reservas son:" << endl;
                //mostar reservas
                cout << endl << endl;
            }
        }
    }
}
