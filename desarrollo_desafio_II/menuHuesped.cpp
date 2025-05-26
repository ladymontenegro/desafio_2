#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void menuHuesped(Huesped **&arregloHuespedes, Reserva **&arregloReservasGlobales, unsigned short indice){
    //debe recibir los arreglo y el indice del huesped
    string opcion = "";
    string codigoReserva = "";
    bool reservaEliminada = false;
    bool sistemaActivo = true;

    while(sistemaActivo){
        bool entrada_valida = false;

        cout << "--- MENU HUESPED ---" << endl;
        cout << "1. Agregar reserva" << endl;
        cout << "2. Eliminar reserva" << endl;
        cout << "3. Salir del sistema" << endl;

        while (!entrada_valida) {
            cout << "Ingrese una opcion: ";
            getline(cin, opcion); // Captura toda la línea

            // Validar la opción
            if (opcion == "1" || opcion == "2" || opcion == "3") {
                entrada_valida = true;
            } else {
                cout << "Error: Opcion invalida. Intente de nuevo.\n";
            }
        }

        if(opcion == "1"){
            cout << "Ejecutando Opcion 1" << endl;
        }

        else if(opcion == "2"){
            cout << "Ejecutando Opcion 2" << endl;
            arregloHuespedes[indice] -> mostrarReservas();

            while(!reservaEliminada){
                cout << "Ingrese el codigo de la reserva que desea eliminar: ";
                getline(cin, codigoReserva);
                reservaEliminada = eliminarReservaTodos(codigoReserva);

                if(!reservaEliminada){
                    cout << "Error: No fue posible eliminar la reserva. Asegurese que el codigo ingresado fue el correcto" << endl;
                } else {
                    cout << "Reserva aliminada exitosamente." << endl;
                }
            }
        }
        else if(opcion == "3"){
            cout << "Has salido del sistema";
            sistemaActivo = false;
        }
    }
}
