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
            Fecha fechaPago;
            string codigoAlojamiento = "";
            string municipio = "";
            string codigoReserva;
            string metodoPago = "";
            string inquietudes = "";
            string respuesta = "";
            short indiceAnfitrion = 0;
            short indiceAlojamiento = 0;
            unsigned int montoPago = 0;
            unsigned short estadiaNoches = 0;
            bool codigoValido = false;
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
                    cerr << "Ha ocurrido un error desconocido: " << e.what() << ". Por favor, intente de nuevo" << endl;
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
                    "\n1. Precio maximo por alojamiento"
                    "\n2. Puntuacion minima de Anfitrion"
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
                string costoMaximoStr = "";
                unsigned int costoMaximo= 0;
                while(true){
                    cout << "Ingrese el precio maximo por alojamiento: ";
                    getline(cin, costoMaximoStr);
                    try {
                        costoMaximo = static_cast<unsigned int>(stoi(costoMaximoStr));
                        filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, costoMaximo, 0, true, false);
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                while(true){
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        codigoReserva = to_string((stoi(arregloReservasGlobales[reservasCargadas-1] ->getCodigoReserva())) + 1);
                        cout << "Ingrese el metodo de pago: ";
                        getline(cin, metodoPago);
                        montoPago = (arregloAnfitriones[indiceAnfitrion] -> getAlojamiento(indiceAlojamiento) ->getPrecioNoche()) * estadiaNoches;

                        while(true){
                            cout << "Desea dejar alguna inquietud en su reserva? (S/N): ";
                            getline(cin, respuesta);
                            if(respuesta == "S"){
                                getline(cin, inquietudes);
                                break;
                            } else if(respuesta == "N"){
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo" << endl;
                            }
                        }

                        Reserva* nuevaReserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago.sumarDias(1), estadiaNoches, montoPago, huespedActual, arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento));
                        arregloReservasGlobales[reservasCargadas] = nuevaReserva;
                        huespedActual ->agregarReserva(nuevaReserva);
                        arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento) ->agregarReserva(nuevaReserva);

                        cout << "COMPROBANTE DE CONFIRMACION DE RESERVA";
                        cout << nuevaReserva ->getCodigoReserva() << endl;
                        cout << huespedActual ->getNombre() << endl;
                        cout << nuevaReserva ->getAlojamiento() ->getCodigo() << endl;
                        cout << "Fecha de inicio: ";
                        nuevaReserva ->getFechaEntrada().fechaPalabras();
                        cout << "\nFecha de finalizacion: ";
                        nuevaReserva ->getFechaFin().fechaPalabras();
                        reservasCargadas++;
                        break;
                    }
                }
            }

            else if(opcionBusqueda == "2"){
                string puntuaMinimaStr = "";
                unsigned int puntuaMinima= 0;
                while(true){
                    cout << "Ingrese la puntuacion minima del Anfitrion: ";
                    getline(cin, puntuaMinimaStr);
                    try {
                        puntuaMinima = stof(puntuaMinimaStr);
                        filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, 0, puntuaMinima, true, false);
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                while(true){
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        codigoReserva = to_string((stoi(arregloReservasGlobales[reservasCargadas-1] ->getCodigoReserva())) + 1);
                        cout << "Ingrese el metodo de pago: ";
                        getline(cin, metodoPago);
                        montoPago = (arregloAnfitriones[indiceAnfitrion] -> getAlojamiento(indiceAlojamiento) ->getPrecioNoche()) * estadiaNoches;

                        while(true){
                            cout << "Desea dejar alguna inquietud en su reserva? (S/N): ";
                            getline(cin, respuesta);
                            if(respuesta == "S"){
                                getline(cin, inquietudes);
                                break;
                            } else if(respuesta == "N"){
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo" << endl;
                            }
                        }

                        Reserva* nuevaReserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago.sumarDias(1), estadiaNoches, montoPago, huespedActual, arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento));
                        arregloReservasGlobales[reservasCargadas] = nuevaReserva;
                        huespedActual ->agregarReserva(nuevaReserva);
                        arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento) ->agregarReserva(nuevaReserva);

                        cout << "COMPROBANTE DE CONFIRMACION DE RESERVA";
                        cout << nuevaReserva ->getCodigoReserva() << endl;
                        cout << huespedActual ->getNombre() << endl;
                        cout << nuevaReserva ->getAlojamiento() ->getCodigo() << endl;
                        cout << "Fecha de inicio: ";
                        nuevaReserva ->getFechaEntrada().fechaPalabras();
                        cout << "\nFecha de finalizacion: ";
                        nuevaReserva ->getFechaFin().fechaPalabras();
                        reservasCargadas++;
                        break;
                    }
                }
            }

            else if(opcionBusqueda == "3"){
                string costoMaximoStr = "";
                unsigned int costoMaximo= 0;
                while(true){
                    cout << "Ingrese el precio maximo por alojamiento: ";
                    getline(cin, costoMaximoStr);
                    try {
                        costoMaximo = static_cast<unsigned int>(stoi(costoMaximoStr));
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
                    cout << "Ingrese la puntuacion minima del Anfitrion: ";
                    getline(cin, puntuaMinimaStr);
                    try {
                        puntuaMinima = stof(puntuaMinimaStr);
                    } catch(invalid_argument& excepcion){
                        cerr <<"Valor invalido: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(out_of_range& excepcion){
                        cerr <<"Error en el valor numerico de la fecha (fuera de rango): " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    } catch(runtime_error& excepcion){
                        cerr <<"Error al procesar el valor: " << excepcion.what() << " .Por favor, intente de nuevo" << endl;
                    }
                }

                while(true){
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        codigoReserva = to_string((stoi(arregloReservasGlobales[reservasCargadas-1] ->getCodigoReserva())) + 1);
                        cout << "Ingrese el metodo de pago: ";
                        getline(cin, metodoPago);
                        montoPago = (arregloAnfitriones[indiceAnfitrion] -> getAlojamiento(indiceAlojamiento) ->getPrecioNoche()) * estadiaNoches;

                        while(true){
                            cout << "Desea dejar alguna inquietud en su reserva? (S/N): ";
                            getline(cin, respuesta);
                            if(respuesta == "S"){
                                getline(cin, inquietudes);
                                break;
                            } else if(respuesta == "N"){
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo" << endl;
                            }
                        }

                        Reserva* nuevaReserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago.sumarDias(1), estadiaNoches, montoPago, huespedActual, arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento));
                        arregloReservasGlobales[reservasCargadas] = nuevaReserva;
                        huespedActual ->agregarReserva(nuevaReserva);
                        arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento) ->agregarReserva(nuevaReserva);

                        cout << "COMPROBANTE DE CONFIRMACION DE RESERVA";
                        cout << nuevaReserva ->getCodigoReserva() << endl;
                        cout << huespedActual ->getNombre() << endl;
                        cout << nuevaReserva ->getAlojamiento() ->getCodigo() << endl;
                        cout << "Fecha de inicio: ";
                        nuevaReserva ->getFechaEntrada().fechaPalabras();
                        cout << "\nFecha de finalizacion: ";
                        nuevaReserva ->getFechaFin().fechaPalabras();
                        reservasCargadas++;
                        break;
                    }
                }
            }

            else {
                filtroReservas(arregloAnfitriones, anfitrionesCargados, municipio, fechaEntrada, estadiaNoches, 0, 0, false, false);

                while(true){
                    cout << "Ingrese el codigo del alojamiento donde desea hospedarse: ";
                    getline(cin, codigoAlojamiento);
                    codigoValido = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, anfitrionesCargados, indiceAnfitrion, indiceAlojamiento);

                    if(codigoValido){
                        codigoReserva = to_string((stoi(arregloReservasGlobales[reservasCargadas-1] ->getCodigoReserva())) + 1);
                        cout << "Ingrese el metodo de pago: ";
                        getline(cin, metodoPago);
                        montoPago = (arregloAnfitriones[indiceAnfitrion] -> getAlojamiento(indiceAlojamiento) ->getPrecioNoche()) * estadiaNoches;

                        while(true){
                            cout << "Desea dejar alguna inquietud en su reserva? (S/N): ";
                            getline(cin, respuesta);
                            if(respuesta == "S"){
                                getline(cin, inquietudes);
                                break;
                            } else if(respuesta == "N"){
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo" << endl;
                            }
                        }

                        Reserva* nuevaReserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago = fechaEntrada.sumarDias(1), estadiaNoches, montoPago, huespedActual, arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento));
                        arregloReservasGlobales[reservasCargadas] = nuevaReserva;
                        huespedActual ->agregarReserva(nuevaReserva);
                        arregloAnfitriones[indiceAnfitrion] ->getAlojamiento(indiceAlojamiento) ->agregarReserva(nuevaReserva);

                        cout << "COMPROBANTE DE CONFIRMACION DE RESERVA";
                        cout << nuevaReserva ->getCodigoReserva() << endl;
                        cout << huespedActual ->getNombre() << endl;
                        cout << nuevaReserva ->getAlojamiento() ->getCodigo() << endl;
                        cout << "Fecha de inicio: ";
                        nuevaReserva ->getFechaEntrada().fechaPalabras();
                        cout << "\nFecha de finalizacion: ";
                        nuevaReserva ->getFechaFin().fechaPalabras();
                        reservasCargadas++;
                        break;
                    }
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
