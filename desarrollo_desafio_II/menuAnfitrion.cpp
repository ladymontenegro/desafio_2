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
                cin >> fechaHoy;
                // validar fecha
                cout << "Saliendo del menu de anfitriones" << endl;
                break;
            } else if (opcion == "1") {
                while (true) {
                    cout << "Sus reservas son:" << endl;
                    //mostar reservas
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
