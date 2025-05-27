#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void menuHuesped(Huesped **&arregloHuespedes, Reserva **&arregloReservasGlobales, unsigned short indice){
    //debe recibir los arreglo y el indice del huesped
    string opcion = "";
    bool sistemaActivo = true;

    while(sistemaActivo){
        bool entrada_valida = false;

        cout << "--- MENU HUESPED ---" << endl;
        cout << "1. Agregar reserva" << endl;
        cout << "2. Eliminar reserva" << endl;
        cout << "3. Salir del sistema" << endl;

        while (!entrada_valida) {
            cout << "Ingrese una opcion: ";
            getline(cin, opcion);

            if (opcion == "1" || opcion == "2" || opcion == "3") {
                entrada_valida = true;
            } else {
                cout << "Error: Opcion invalida. Por favor, intente de nuevo.\n";
            }
        }

        if(opcion == "1"){
            Fecha fechaEntrada;
            string municipio = "";
            unsigned short estadiaNoches = 0;
            bool fechaValida = false;
            bool estadiaValida = false;

            while(!fechaValida){
                string _fechaEntrada = "";
                cout << "Ingrese la fecha en la cual se desea hospedar (DD-MM-AAAA): ";
                getline(cin, _fechaEntrada);
                try {
                    fechaEntrada = crearFecha(_fechaEntrada);
                    fechaValida = true;
                } catch (const invalid_argument &e){
                    cerr << "Error: " << e.what() << ". Por favor, intente de nuevo" << endl;
                } catch (const runtime_error &e) {
                    cerr << "Error: " << e.what() << "Contacte a soporte tecnico" << endl;
                } catch (const exception &e){
                    cerr << "Ha ocurrido un error desconocido: " << e.what() << ". Por favor, intente de nuevo" << ednl;
                }
            }

            while (!estadiaValida) {
                string estadiaNochesStr = "";
                cout << "Ingrese la cantidad de noches que desea alojarse: ";
                getline(cin, estadiaNochesStr);

                if (estadiaNochesStr.empty()) {
                    cout << "La entrada no puede estar vacia. Por favor, ingrese un numero." << endl;
                    continue;
                }
                bool esNumero = true;
                for (char c : estadiaNochesStr) {
                    if (!isdigit(c)) {
                        esNumero = false;
                        break;
                    }
                }
                if (!esNumero) {
                    cout << "Entrada invalida. Por favor, ingrese solo numeros." << endl;
                    continue;
                }
                try {
                    estadiaNoches = static_cast<unsigned short>(stoi(estadiaNochesStr));
                    if (estadiaNoches > 0) {
                        estadiaValida = true;
                    } else {
                        cout << "La cantidad de noches debe ser un numero positivo." << endl;
                    }
                } catch (const out_of_range& excepcion) {
                    cerr << "El numero ingresado es demasiado grande o pequeño. Por favor, intente con otro." << endl;
                } catch (const invalid_argument& excepcion) {
                    cerr << "Error interno al convertir el numero. Por favor, intente de nuevo." << endl;
                }
            }

            cout << "Ingrese el municipio donde desea alojarse: ";
            getline(cin, municipio);

            cout << "Filtros de Busqueda"
                    "\n1. Precio alojamiento"
                    "\n2. Puntuacion de Anfitrion"
                    "\n3. Ambos"
                    "\n4. No aplicar filtros de busqueda" << endl;

            string opcionBusqueda = "";
            bool opcion_valida = false;

            while(!opcion_valida) {
                cout << "Ingrese una opcion: ";
                getline(cin,opcionBusqueda);

                if (opcionBusqueda == "1" || opcionBusqueda == "2" || opcionBusqueda == "3" || opcionBusqueda == "4") {
                    opcion_valida = true;
                } else {
                    cout << "Error: Opcion invalida. Intente de nuevo.\n";
                }
            }

            if(opcionBusqueda == "1"){
                cout << ;
            }

            else if(opcionBusqueda == "2"){
                cout << ;
            }

            else if(opcionBusqueda == "3"){
                cout << ;
            }

            else if(opcionBusqueda == "4"){
                cout << ;
            }
        }

        else if(opcion == "2"){
            string codigoReserva = "";
            bool reservaEliminada = false;

            //visualizar las reservas asociadas al huesped
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

Fecha crearFecha(const string &fechaStr){
    if(fechaStr.empty()){
        throw invalid_argument("Error: La fecha no puede estar vacia");
    }
    size_t inicio = 0;
    const char delimitador = '-';

    unsigned char dia = '';
    unsigned char mes = '';
    unsigned short anio = 0;
    try {
        dia = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        mes = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        anio = static_cast<unsigned short>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
    } catch (const invalid_argument& excepcion) {
        throw invalid_argument("Error en formato numerico: " + string(excepcion.what()));
    } catch (const out_of_range& excepcion) {
        throw out_of_range("Error en el valor numerico de la fecha (fuera de rango): " + string(excepcion.what()));
    } catch (const exception& excepcion) {
        throw runtime_error("Error inesperado al procesar la fecha: " + string(excepcion.what()));
    }

    Fecha fechaCreada(dia, mes, anio);
    return fechaCreada;
}
