#include <iostream>
#include <stdexcept>
#include <string>

#include "variablesIteracionesMemoria.h"
#include "funcionesAuxiliares.h"

using namespace std;

void menuHuesped(Anfitrion **&arregloAnfitriones, Reserva **&arregloReservasGlobales, Huesped* huespedActual, unsigned short &reservasCargadas, unsigned short anfitrionesCargados){
    //debe recibir los arreglo y el indice del huesped
    string opcion = "";
    bool sistemaActivo = true;

    while(sistemaActivo){
        Globales::contadorIteraciones++;
        bool entrada_valida = false;

        cout << "\n--- MENU HUESPED ---" << endl;
        cout << "1. Agregar reserva" << endl;
        cout << "2. Eliminar reserva" << endl;
        cout << "3. Salir del sistema" << endl;

        while (!entrada_valida) {
            Globales::contadorIteraciones++;
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
            string codigoAlojamiento = "";
            string municipio = "";
            short indiceAnfitrion = 0;
            short indiceAlojamiento = 0;
            unsigned short estadiaNoches = 0;
            bool codigoValido = false;
            bool fechaValida = false;
            bool estadiaValida = false;
            bool reservaCreada = false;

            while(!fechaValida){
                Globales::contadorIteraciones++;
                string _fechaEntrada = "";
                cout << "Ingrese la fecha en la cual se desea hospedar (DD-MM-AAAA): ";
                getline(cin, _fechaEntrada);
                try {
                    fechaEntrada = crearFecha(_fechaEntrada);
                    fechaValida = true;
                } catch (const invalid_argument &e){
                    cout << "Error: " << e.what() << " Por favor, intente de nuevo." << endl;
                } catch (const out_of_range &e){
                    cout << "Error: " << e.what() << " Verifique los valores (dia, mes, anio)." << endl;
                }
                catch (const runtime_error &e) {
                    cout << "Se ha producido un error inesperado al procesar la fecha. Por favor, contacte a soporte tecnico." << endl;
                } catch (const exception &e){
                    cout << "Ha ocurrido un error desconocido al ingresar la fecha. Por favor, intente de nuevo." << endl;
                }
            }

            while (!estadiaValida) {
                Globales::contadorIteraciones++;
                string estadiaNochesStr = "";
                cout << "Ingrese la cantidad de noches que desea alojarse: ";
                getline(cin, estadiaNochesStr);

                bool esNumeroCompleto = validarNumero(estadiaNochesStr);

                if (!esNumeroCompleto) {
                    cout << "Entrada invalida. Por favor, ingrese solo numeros positivos." << endl;
                    continue; //pa volver a pedir entrada
                }
                try {
                    estadiaNoches = static_cast<unsigned short>(stoi(estadiaNochesStr));
                    Globales::contadorStoi++;
                    if (estadiaNoches > 0 && estadiaNoches < 365) {
                        estadiaValida = true;
                    } else {
                        cout << "La cantidad de noches debe ser un numero positivo y no mayor a 365" << endl;
                    }
                } catch (const out_of_range& excepcion) {
                    cerr << "El numero ingresado es demasiado grande o pequenio. Por favor, intente con otro." << endl;
                } catch (const invalid_argument& excepcion) {
                    cerr << "Error interno al convertir el numero. Por favor, intente de nuevo." << endl;
                }
            }

            cout << "Ingrese el municipio donde desea alojarse: ";
            getline(cin, municipio);

            cout << "\nFiltros de Busqueda"
                    "\n1. Precio maximo por alojamiento"
                    "\n2. Puntuacion minima de Anfitrion"
                    "\n3. Ambos"
                    "\n4. No aplicar filtros de busqueda" << endl;

            string opcionBusqueda = "";
            bool opcion_valida = false;

            while(!opcion_valida) {
                Globales::contadorIteraciones++;
                cout << "Ingrese una opcion: ";
                getline(cin,opcionBusqueda);

                if (opcionBusqueda == "1" || opcionBusqueda == "2" || opcionBusqueda == "3" || opcionBusqueda == "4") {
                    opcion_valida = true;
                } else {
                    cout << "Error: Opcion invalida. Intente de nuevo.\n";
                }
            }

            bool alojamientoEncontrado = false;

            if(opcionBusqueda == "1"){
                string costoMaximoStr = "";
                unsigned int costoMaximo= 0;

                while(true){
                    cout << "Ingrese el precio maximo por alojamiento: ";
                    getline(cin, costoMaximoStr);
                    bool esNumeroCompleto = validarNumero(costoMaximoStr);

                    if (!esNumeroCompleto) {
                        cout << "Entrada invalida. Por favor, ingrese solo numeros positivos." << endl;
                        continue; //pa volver a pedir entrada
                    }
                    try {
                        costoMaximo = static_cast<unsigned int>(stoi(costoMaximoStr));
                        Globales::contadorStoi++;
                        if (costoMaximo > 0) {
                            cout << "EL costo maximo debe ser un numero positivo" << endl;
                        }
                        alojamientoEncontrado = filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, costoMaximo, 0, true, false);

                        if(alojamientoEncontrado){
                            break;
                        }
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido. Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico (fuera de rango). Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor. Por favor, intente de nuevo" << endl;
                    }
                }

                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        reservaCreada = crearReservaTodos(arregloReservasGlobales, reservasCargadas, arregloAnfitriones, fechaEntrada, huespedActual, estadiaNoches, indiceAlojamiento, indiceAnfitrion);
                        break;
                    }
                }

                if(reservaCreada){
                    cout << "Rserva creada exitosamente." << endl;
                } else {
                    cout << "La reserva no pudo ser creada. Por favor acceda de nuevo al sistema.";
                }
            }

            else if(opcionBusqueda == "2"){
                string puntuaMinimaStr = "";
                unsigned int puntuaMinima= 0;
                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese la puntuacion minima del Anfitrion: ";
                    getline(cin, puntuaMinimaStr);
                    try {
                        puntuaMinima = stof(puntuaMinimaStr);
                        Globales::contadorStof++;
                        alojamientoEncontrado = filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, 0, puntuaMinima, false, true);
                        if(alojamientoEncontrado){
                            break;
                        }
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        reservaCreada = crearReservaTodos(arregloReservasGlobales, reservasCargadas, arregloAnfitriones, fechaEntrada, huespedActual, estadiaNoches, indiceAlojamiento, indiceAnfitrion);
                        break;
                    }
                }

                if(reservaCreada){
                    cout << "Rserva creada exitosamente." << endl;
                } else {
                    cout << "La reserva no pudo ser creada. Por favor acceda de nuevo al sistema.";
                }
            }

            else if(opcionBusqueda == "3"){
                string costoMaximoStr = "";
                unsigned int costoMaximo= 0;
                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese el precio maximo por alojamiento: ";
                    getline(cin, costoMaximoStr);
                    try {
                        costoMaximo = static_cast<unsigned int>(stoi(costoMaximoStr));
                        Globales::contadorStoi++;
                        break;
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                string puntuaMinimaStr = "";
                unsigned int puntuaMinima= 0;
                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese la puntuacion minima del Anfitrion: ";
                    getline(cin, puntuaMinimaStr);
                    try {
                        puntuaMinima = stof(puntuaMinimaStr);
                        Globales::contadorStof++;
                        break;
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                alojamientoEncontrado = filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, costoMaximo, puntuaMinima, true, true);

                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        reservaCreada = crearReservaTodos(arregloReservasGlobales, reservasCargadas, arregloAnfitriones, fechaEntrada, huespedActual, estadiaNoches, indiceAlojamiento, indiceAnfitrion);
                        break;
                    }
                }

                if(reservaCreada){
                    cout << "Rserva creada exitosamente." << endl;
                } else {
                    cout << "La reserva no pudo ser creada. Por favor acceda de nuevo al sistema.";
                }
            }

            else {
                alojamientoEncontrado = filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, 0, 0, false, false);

                while(true){
                    Globales::contadorIteraciones++;
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        reservaCreada = crearReservaTodos(arregloReservasGlobales, reservasCargadas, arregloAnfitriones, fechaEntrada, huespedActual, estadiaNoches, indiceAlojamiento, indiceAnfitrion);
                        break;
                    }
                }

                if(reservaCreada){
                    cout << "Rserva creada exitosamente." << endl;
                } else {
                    cout << "La reserva no pudo ser creada. Por favor acceda de nuevo al sistema.";
                }
            }

            guardarReservasEnArchivo(arregloAnfitriones, anfitrionesCargados);
        }

        else if(opcion == "2"){
            string codigoReserva = "";
            bool reservaEliminada = false;

            //visualizar las reservas asociadas al huesped
            huespedActual -> mostrarReservas();

            while(!reservaEliminada){
                Globales::contadorIteraciones++;
                cout << "\nIngrese el codigo de la reserva que desea eliminar: ";
                getline(cin, codigoReserva);
                reservaEliminada = eliminarReservaTodos(codigoReserva, arregloReservasGlobales, reservasCargadas);

                if(!reservaEliminada){
                    cout << "Error: No fue posible eliminar la reserva. Asegurese que el codigo ingresado fue el correcto" << endl;
                } else {
                    cout << "Reserva aliminada exitosamente." << endl;
                }
            }
            guardarReservasEnArchivo(arregloAnfitriones, anfitrionesCargados);
        }
        else if(opcion == "3"){
            cout << "Has salido del sistema";
            sistemaActivo = false;
        }
    }
}
