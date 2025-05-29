#include <iostream>
#include <fstream>
#include <string>

#include "variablesIteracionesMemoria.h"
#include "alojamiento.h"
#include "anfitrion.h"
#include "fecha.h"
#include "huesped.h"

using namespace std;

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio, char delimitador, bool esCampoObligatorio = true){

    size_t fin = linea.find(delimitador, inicio);
    Globales::contadorFind++;
    string atributo;

    Globales::contadorSubstr++;
    if (fin != string::npos) { //si se encontro la coma
        atributo = linea.substr(inicio, fin - inicio);
        inicio = fin + 1; //actualiza el inicio para el proximo atributo, por eso se pasa por referencia
    } else { //para el ultimo atributo que no tiene delimitador
        atributo = linea.substr(inicio);
        Globales::contadorSubstr++;
        inicio = linea.length(); //evita procesar mas atributos
        Globales::contadorLength++;
    }

    if (esCampoObligatorio && atributo.empty()) {
        throw invalid_argument("Vacio la linea de datos");
    }

    return atributo;
}

bool eliminarReservaTodos(const string &codigoReserva, Reserva **&arregloReservasGlobal, unsigned short &reservasCargadas) {
    for (unsigned short i = 0; i < reservasCargadas; ++i) {
        Globales::contadorIteraciones++;
        if ((arregloReservasGlobal[i] != nullptr) && (arregloReservasGlobal[i] -> getCodigoReserva() == codigoReserva)) {
            //eliminar la reserva del huesped
            Huesped* huesped = arregloReservasGlobal[i] -> getHuesped();
            huesped -> eliminarReserva(codigoReserva);

            //eliminar la reserva del alojamiento
            Alojamiento* alojamiento = arregloReservasGlobal[i] -> getAlojamiento();
            alojamiento -> eliminarReserva(codigoReserva);

            //eliminar la reserva del arreglo global
            delete arregloReservasGlobal[i];
            arregloReservasGlobal[i] = nullptr;

            for (unsigned short j = i; j < reservasCargadas - 1; j++) {
                Globales::contadorIteraciones++;
                arregloReservasGlobal[j] = arregloReservasGlobal[j + 1];
            }
            arregloReservasGlobal[reservasCargadas - 1] = nullptr;
            reservasCargadas--;

            return true;
        }
    }
    return false;
}

bool crearReservaTodos(Reserva** arregloReservasGlobales, unsigned short &reservasCargadas,Anfitrion** arregloAnfitriones,
                    Fecha fechaEntrada, Huesped* huespedActual, unsigned short estadiaNoches, unsigned short indiceAlojamiento, unsigned short indiceAnfitrion){

    string metodoPago = "";
    string inquietudes = "";
    string codigoReserva = "";
    unsigned int montoPago = 0;
    Fecha fechaPago;

    codigoReserva = to_string((stoi(arregloReservasGlobales[reservasCargadas-1] ->getCodigoReserva())) + 1);
    cout << "Ingrese el metodo de pago: ";
    getline(cin, metodoPago);
    montoPago = (arregloAnfitriones[indiceAnfitrion] -> getAlojamiento(indiceAlojamiento) ->getPrecioNoche()) * estadiaNoches;

    while(true){
        Globales::contadorIteraciones++;
        string respuesta = "";
        cout << "Desea dejar alguna inquietud en su reserva? (S/N): ";
        getline(cin, respuesta);
        if(respuesta == "S"){
            cout << "Escriba sus inquietudes: ";
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

    cout << "\n-------------- COMPROBANTE DE CONFIRMACION DE RESERVA --------------" << endl;
    cout << "" << endl;
    cout << "Codigo de la reserva: " << nuevaReserva ->getCodigoReserva() << endl;
    cout << "Nombre del huesped: " << huespedActual ->getNombre() << endl;
    cout << "Codigo alojamiento: " << nuevaReserva ->getAlojamiento() ->getCodigo() << endl;
    cout << "Fecha de inicio: ";
    nuevaReserva ->getFechaEntrada().fechaPalabras();
    cout << "Fecha de finalizacion: ";
    nuevaReserva ->getFechaFin().fechaPalabras();
    cout << "---------------------------------------------------------------------" << endl;
    reservasCargadas++;

    return true;
}

size_t calcularMemoriaTotal(unsigned short anfitrionesCargados, unsigned short huespedesCargados, unsigned short reservasCargadas,
                            Anfitrion** arregloAnfitriones, Huesped** arregloHuespedes, Reserva** arregloReservasGlobales,
                            unsigned short capacidadAnfitriones, unsigned short capacidadHuespedes, unsigned short capacidadReservasGlobales) {
    size_t total = 0;

    //memoria del ARREGLO GLOBAL de anfitriones (todos los slots)
    total += static_cast<size_t>(capacidadAnfitriones) * sizeof(Anfitrion*);

    //memoria de cada anfitrion cargado (no nulo)
    for (unsigned short i = 0; i < anfitrionesCargados; ++i) {
        if (arregloAnfitriones[i]) {
            total += arregloAnfitriones[i]->calcularMemoria();
        }
    }

    //memoria del ARREGLO GLOBAL de huespedes
    total += static_cast<size_t>(capacidadHuespedes) * sizeof(Huesped*);

    //memoria de cada huesped cargado (no nulo)
    for (unsigned short i = 0; i < huespedesCargados; ++i) {
        if (arregloHuespedes[i]) {
            total += arregloHuespedes[i]->calcularMemoria();
        }
    }

    //memoria del ARREGLO GLOBAL de reservas
    total += static_cast<size_t>(capacidadReservasGlobales) * sizeof(Anfitrion*);

    //memoria de cada reserva cargado (no nulo)
    for (unsigned short i = 0; i < reservasCargadas; ++i) {
        if (arregloReservasGlobales[i]) {
            total += arregloReservasGlobales[i]->calcularMemoria();
        }
    }

    return total;
}

//FUNCIONES DE BUSQUEDA
short buscarHuespedPorDocumento(Huesped**& arregloHuespedes, const string &documento, unsigned short cantidadHuespedes, bool &encontrado){
    for(unsigned short i = 0; i < cantidadHuespedes; i++){
        Globales::contadorIteraciones++;
        if((arregloHuespedes[i] -> getDocumento()) == documento){
            encontrado = true;
            return i;
        }
    }
    return -1;
}

bool buscarAlojamientoPorCodigo(Anfitrion**& arregloAnfitriones, const string &codigo, unsigned short cantidadAnfitriones, short &indiceAnfitrion, short &indiceAlojamiento){
    for(unsigned short i = 0; i < cantidadAnfitriones; i++){
        Globales::contadorIteraciones++;
        for(unsigned short j = 0; j < (arregloAnfitriones[i] -> getAlojamientosCargados()); j++){
            Globales::contadorIteraciones++;
            if((arregloAnfitriones[i] -> getAlojamiento(j) -> getCodigo()) == codigo){
                indiceAnfitrion = i;
                indiceAlojamiento = j;
                return true;
            }
        }
    }
    return false;
}

bool filtroReservas(Anfitrion **&arregloAnfitriones, const unsigned short &anfitrionesCargados, const string &municipio, const Fecha &fecha, const unsigned short &cantidadDeNoches,
                    const unsigned int &costoMaximo = 0, const float &puntajeMinimo = 0, bool buscarPorCosto = false, bool buscarPorPuntaje = false)
{
    bool alojamientoEncontradoYMostrado = false;

    for (unsigned short i = 0; i < anfitrionesCargados; i++) {
        Globales::contadorIteraciones++;
        if (arregloAnfitriones[i] == nullptr) {
            continue;
        }
        for (unsigned short j = 0; j < arregloAnfitriones[i]->getAlojamientosCargados(); j++) {
            Globales::contadorIteraciones++;
            Alojamiento *alojamientoActual = arregloAnfitriones[i]->getAlojamiento(j);
            if (alojamientoActual == nullptr) {
                continue;
            }

            // Filtro Base: Municipio y Disponibilidad
            if (alojamientoActual->getMunicipio() == municipio
                && alojamientoActual->alojamientoDisponible(fecha, cantidadDeNoches)) {
                // Una vez que cumple el filtro base, evaluamos los filtros adicionales
                if (!buscarPorCosto && !buscarPorPuntaje) {
                    // Si no hay filtros adicionales, simplemente mostrar el alojamiento
                    alojamientoActual->mostrarAlojamiento();
                    alojamientoEncontradoYMostrado = true;
                } else if (buscarPorCosto && !buscarPorPuntaje) {
                    // Si solo se busca por costo
                    if (alojamientoActual->getPrecioNoche() <= costoMaximo) {
                        alojamientoActual->mostrarAlojamiento();
                        alojamientoEncontradoYMostrado = true;
                    }
                } else if (!buscarPorCosto && buscarPorPuntaje) {
                    // Si solo se busca por puntaje
                    if (arregloAnfitriones[i]->getPuntuacion() >= puntajeMinimo) {
                        alojamientoActual->mostrarAlojamiento();
                        alojamientoEncontradoYMostrado = true;
                    }
                } else if (buscarPorCosto && buscarPorPuntaje) {
                    // Si se busca por costo y puntaje
                    if (alojamientoActual->getPrecioNoche() <= costoMaximo
                        && arregloAnfitriones[i]->getPuntuacion() >= puntajeMinimo) {
                        alojamientoActual->mostrarAlojamiento();
                        alojamientoEncontradoYMostrado = true;
                    }
                }
            }
        }
    }

    if (!alojamientoEncontradoYMostrado) {
        if (!buscarPorCosto && !buscarPorPuntaje) {
            cout << "No se encontro ningun alojamiento en el municipio '" << municipio
                 << "' que este disponible para la fecha y cantidad de noches especificadas"
                 << endl;
        } else if (buscarPorCosto && !buscarPorPuntaje) {
            cout
                << "No se encontro ningun alojamiento en el municipio '" << municipio
                << "' disponible para la fecha especificada con un costo por noche menor o igual a "
                << costoMaximo << endl;
        } else if (!buscarPorCosto && buscarPorPuntaje) {
            cout << "No se encontro ningun alojamiento en el municipio '" << municipio
                 << "' disponible para la fecha especificada cuyo anfitrion tenga una "
                    "puntuacion mayor o igual a "
                 << puntajeMinimo << endl;
        } else if (buscarPorCosto && buscarPorPuntaje) {
            cout << "No se encontro ningun alojamiento en el municipio '" << municipio
                 << "' disponible para la fecha especificada que cumpla con el costo maximo ("
                 << costoMaximo << ") y el puntaje minimo del anfitrion (" << puntajeMinimo << ")"
                 << endl;
        }
    }

    return alojamientoEncontradoYMostrado;
}

//FUNCIONES DE VALIDACION
bool esDocumento(const string& linea, size_t& inicio){
    bool documento = false;
    char delimitador = ',';
    size_t fin = linea.find(delimitador, inicio);
    Globales::contadorFind++;
    string identificador = linea.substr(inicio, fin - inicio);
    Globales::contadorSubstr++;

    Globales::contadorLength++;
    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool es_digito_manual(char c) {
    return c >= '0' && c <= '9';
}

bool validarNumero(string &cadena){
    size_t inicio_ = 0;

    Globales::contadorLength++;
    if (cadena.length() == inicio_) {
        cout << "La entrada no puede estar vacia. Por favor, ingrese un numero." << endl;
        return false;
    } else {
        for (size_t i = inicio_; i < cadena.length(); ++i) {
            Globales::contadorLength++;
            if (!es_digito_manual(cadena[i])) {
                return false;
            }
        }
    }
    return true;
}

unsigned short tipoUsuario(Huesped **&arregloHuespedes, Anfitrion **& arregloAnfitriones, unsigned short &indice, unsigned short anfitrionesCargados, unsigned short huespedesCargados){
    string documento = "";
    bool documentoValido = false;
    bool encontrado = false;

    while(!documentoValido){
        Globales::contadorIteraciones++;
        cout << "Ingrese su numero de documento: ";
        getline(cin, documento);

        Globales::contadorLength++;
        if((documento.length()) == 10){
            documentoValido = true;
        } else {
            cout << "Documento invalido. Asegurese que la longitud del documento sea diez" << endl;
        }
    }
    //verificar si es anfitrion
    for(unsigned short i = 0; i < anfitrionesCargados; i++){
        Globales::contadorIteraciones++;
        if(arregloAnfitriones[i] != nullptr){
            if((arregloAnfitriones[i] -> getDocumento()) == documento){
                indice = i;
                return '1';
            }
        }
    }

    //verificar si es huesped
    indice =  buscarHuespedPorDocumento(arregloHuespedes, documento, huespedesCargados, encontrado);
    if(encontrado){
        return '2';
    }

    //si no hallo nada
    return '3';
}

Fecha crearFecha(const string &fechaStr){
    if(fechaStr.empty()){
        Globales::contadorEmpty++;
        throw invalid_argument("Error: La fecha no puede estar vacia");
    }
    size_t inicio = 0;
    const char delimitador = '-';

    unsigned char dia = 0;
    unsigned char mes = 0;
    unsigned short anio = 0;
    try {
        dia = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        Globales::contadorStoi++;
        mes = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        Globales::contadorStoi++;
        anio = static_cast<unsigned short>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        Globales::contadorStoi++;
    } catch (const invalid_argument& excepcion) {
        throw invalid_argument("Formato de fecha incorrecto.");
    } catch (const out_of_range& excepcion) {
        throw out_of_range("Valores numericos fuera de rango.");
    } catch (const exception& excepcion) {
        throw runtime_error("Error inesperado al procesar la fecha.");
    }

    Fecha fechaCreada(dia, mes, anio);
    return fechaCreada;
}

//FUNCIONES DE ORDENAMIENTO DE DATOS
void mezclar(Reserva** reservas, unsigned short izquierda, unsigned short medio, unsigned short derecha) {
    //tamanio de los subarreglos temporal
    unsigned short n1 = medio - izquierda + 1;
    unsigned short n2 = derecha - medio;

    //crear arreglos temporales dinámicos
    Reserva** izquierdaArr = new Reserva*[n1];
    Reserva** derechaArr = new Reserva*[n2];

    //copir datos a los arreglos temporales, son punteros, asi que aja
    for (unsigned short i = 0; i < n1; i++) {
        Globales::contadorIteraciones++;
        izquierdaArr[i] = reservas[izquierda + i];
    }
    for (unsigned short j = 0; j < n2; j++) {
        Globales::contadorIteraciones++;
        derechaArr[j] = reservas[medio + 1 + j];
    }

    //indices para recorrer los subarreglos
    unsigned short i = 0, j = 0, k = izquierda;

    //mezclar los subarreglos en el arreglo principal
    while (i < n1 && j < n2) {
        Globales::contadorIteraciones++;
        if (izquierdaArr[i] -> getFechaEntrada() <= derechaArr[j] -> getFechaEntrada()) {
            reservas[k] = izquierdaArr[i];
            i++;
        } else {
            reservas[k] = derechaArr[j];
            j++;
        }
        k++;
    }
    //copiar elementos restantes de izquierdaArr (si los hay)
    while (i < n1) {
        Globales::contadorIteraciones++;
        reservas[k] = izquierdaArr[i];
        i++;
        k++;
    }
    //copiar elementos restantes de derechaArr (si los hay)
    while (j < n2) {
        Globales::contadorIteraciones++;
        reservas[k] = derechaArr[j];
        j++;
        k++;
    }
    //liberar memoria de los arreglos temporales
    delete[] izquierdaArr;
    delete[] derechaArr;
}

void mergeSort(Reserva** reservas, unsigned short izquierda, unsigned short derecha) {
    if (izquierda < derecha) {
        unsigned short medio = izquierda + (derecha - izquierda) / 2;

        //ordenar primera y segunda mitad
        mergeSort(reservas, izquierda, medio);
        mergeSort(reservas, medio + 1, derecha);

        //mezclar las mitades ordenadas
        mezclar(reservas, izquierda, medio, derecha);
    }
}

void ordenarReservasDeAlojamiento(Alojamiento* alojamiento) {
    unsigned short reservasCargadas = alojamiento -> getReservasCargadas();
    Reserva** reservas = alojamiento -> getReservas();

    //se ordenan las reservas
    mergeSort(reservas, 0, reservasCargadas - 1);
}







