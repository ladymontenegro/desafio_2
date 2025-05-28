#include <iostream>
#include <fstream>
#include <string>

#include "alojamiento.h"
#include "anfitrion.h"
#include "fecha.h"
#include "huesped.h"

using namespace std;

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio, char delimitador, bool esCampoObligatorio = true){

    size_t fin = linea.find(delimitador, inicio);
    string atributo;

    if (fin != string::npos) { //si se encontro la coma
        atributo = linea.substr(inicio, fin - inicio);
        inicio = fin + 1; //actualiza el inicio para el proximo atributo, por eso se pasa por referencia
    } else { //para el ultimo atributo que no tiene delimitador
        atributo = linea.substr(inicio);
        inicio = linea.length(); //evita procesar mas atributos
    }

    if (esCampoObligatorio && atributo.empty()) {
        throw invalid_argument("Vacio la linea de datos");
    }

    return atributo;
}

bool eliminarReservaTodos(string &codigoReserva, Reserva **&arregloReservasGlobal, unsigned short reservasCargadas) {
    for (int i = 0; i < reservasCargadas; ++i) {
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

            return true;
        }
    }
    return false;
}

//FUNCIONES DE VALIDACION
bool esDocumento(const string& linea, size_t& inicio){
    bool documento = false;
    char delimitador = ',';
    size_t fin = linea.find(delimitador, inicio);
    string identificador = linea.substr(inicio, fin - inicio);

    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool tipoUsuario(Huesped **&arregloHuespedes, Anfitrion **& arregloAnfitriones, unsigned short &indice, unsigned short anfitrionesCargados, unsigned short huespedesCargados){
    string documento = "";
    bool documentoValido = false;

    while(!documentoValido){
        cout << "Ingrese su numero de documento: ";
        getline(cin, documento);

        if((documento.length) == 10){
            documentoValido = true;
        } else {
            cout << "Documento invalido. Asegurese que la longitud del documento sea diez" << endl;
        }
    }
    //verificar si es anfitrion
    for(unsigned short i = 0; i < anfitrionesCargados; i++){
        if(arregloAnfitriones[i] != nullptr){
            if((arregloAnfitriones[i] -> getDocumento()) == documento){
                indice = i;
                return true;
            }
        }
    }

    //verificar si es huesped
    for(unsigned short i = 0; i < huespedesCargados; i++){
        if(arregloHuespedes[i] != nullptr){
            if((arregloHuespedes[i] -> getDocumento()) == documento){
                indice = i;
                return true;
            }
        }
    }
    return false;
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

//FUNCIONES DE BUSQUEDA
short buscarHuespedPorDocumento(Huesped**& arregloHuespedes, const string &documento, unsigned short cantidadHuespedes){
    for(short i = 0; i < cantidadHuespedes; i++){
        if((arregloHuespedes[i] -> getDocumento()) == documento){
            return i;
        }
    }
    return -1;
}

bool buscarAlojamientoPorCodigo(Anfitrion**& arregloAnfitriones, const string &codigo, short cantidadAnfitriones, short &indiceAnfitrion, short &indiceAlojamiento){
    for(short i = 0; i < cantidadAnfitriones; i++){
        for(short j = 0; j < (arregloAnfitriones[i] -> getAlojamientosCargados()); j++){
            if((arregloAnfitriones[i] -> getAlojamiento(j) -> getCodigo()) == codigo){
                indiceAnfitrion = i;
                indiceAlojamiento = j;
                return true;
            }
        }
    }
    return false;
}

void filtroReservas(Anfitrion **&arregloAnfitriones, const unsigned short &anfitrionesCargados, const string &municipio, const Fecha &fecha, const unsigned short &cantidadDeNoches,
                    const unsigned short &costoMaximo = 0, const float &puntajeMinimo = 0, bool buscarPorCosto = false, bool buscarPorPuntaje = false)
{
    bool alojamientoEncontradoYMostrado = false;

    for (unsigned short i = 0; i < anfitrionesCargados; i++) {
        if (arregloAnfitriones[i] == nullptr) {
            continue;
        }
        for (unsigned short j = 0; j < arregloAnfitriones[i]->getAlojamientosCargados(); j++) {
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
}

//FUNCIONES DE ORDENAMIENTO DE DATOS
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

void mezclar(Reserva** reservas, unsigned short izquierda, unsigned short medio, unsigned short derecha) {
    //tamanio de los subarreglos temporal
    unsigned short n1 = medio - izquierda + 1;
    unsigned short n2 = derecha - medio;

    //crear arreglos temporales dinámicos
    Reserva** izquierdaArr = new Reserva*[n1];
    Reserva** derechaArr = new Reserva*[n2];

    //copir datos a los arreglos temporales, son punteros, asi que aja
    for (unsigned short i = 0; i < n1; i++) {
        izquierdaArr[i] = reservas[izquierda + i];
    }
    for (unsigned short j = 0; j < n2; j++) {
        derechaArr[j] = reservas[medio + 1 + j];
    }

    //indices para recorrer los subarreglos
    unsigned short i = 0, j = 0, k = izquierda;

    //mezclar los subarreglos en el arreglo principal
    while (i < n1 && j < n2) {
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
        reservas[k] = izquierdaArr[i];
        i++;
        k++;
    }
    //copiar elementos restantes de derechaArr (si los hay)
    while (j < n2) {
        reservas[k] = derechaArr[j];
        j++;
        k++;
    }
    //liberar memoria de los arreglos temporales
    delete[] izquierdaArr;
    delete[] derechaArr;
}

void ordenarReservasDeAlojamiento(Alojamiento* alojamiento) {
    unsigned short reservasCargadas = alojamiento -> getReservasCargadas();
    Reserva** reservas = alojamiento -> getReservas();

    //se ordenan las reservas
    mergeSort(reservas, 0, reservasCargadas - 1);
}






