#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> //pa las excepciones estandar

#include "funcionesAuxiliares.h"

using namespace std;

//FUNCIONES PARA CARGA DE DATOS EN ESTRUCTURAS Y CLASES
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion**& arregloAnfitriones) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
        cerr << "Error: No se pudo abrir el archivo '" << rutaArchivo << "'" << endl;
        return -1;
    }

    char delimitador = ',';
    unsigned short anfitrionesCargados = 0;
    unsigned short alojamientosCargados = 0;
    unsigned short capacidadAnfitriones = 40;
    bool anfitrionActivo = false;
    string linea;

    if (arregloAnfitriones == nullptr) {
        arregloAnfitriones = new Anfitrion*[capacidadAnfitriones];
        for (int i = 0; i < capacidadAnfitriones; ++i) {
            arregloAnfitriones[i] = nullptr;
        }
    }

    try {
        while (getline(archivo, linea)) {
            size_t inicio = 0;
            Anfitrion* nuevoAnfitrion = nullptr;
            Alojamiento* nuevoAlojamiento = nullptr;

            try { //try para manejar errores en el procesamiento de linea
                if (esDocumento(linea,inicio)) {
                    //validacion de documento
                    string documento = obtenerDato(linea,inicio,delimitador);

                    float puntuacion;
                    try {
                        string puntuacion_str = obtenerDato(linea, inicio, delimitador);
                        puntuacion = stof(puntuacion_str);
                        if ((puntuacion < 0.0f) || (puntuacion > 5.0f)){
                            throw out_of_range("La puntuacion debe estar entre 0 y 5");
                        }
                    } catch(const exception& e){
                        throw runtime_error("Error en puntuacion: " + string(e.what()));
                    }

                    unsigned short antiguedad;
                    try {
                        antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));
                    } catch(const exception& e) {
                        throw runtime_error("Error en antigüedad: " + string(e.what()));
                    }

                    if(anfitrionesCargados >= capacidadAnfitriones){
                        redimensionarArreglo(capacidadAnfitriones, anfitrionesCargados, arregloAnfitriones);
                    }

                    nuevoAnfitrion = new Anfitrion(documento, puntuacion, antiguedad);
                    arregloAnfitriones[anfitrionesCargados] = nuevoAnfitrion;
                    anfitrionesCargados++;

                    alojamientosCargados = 0;
                    anfitrionActivo = true;

                } else if (anfitrionActivo) {
                    //validacion de existencia de anfitrion
                    if(anfitrionesCargados == 0) {
                        throw logic_error("No hay anfitriones registrados para agregar alojamiento");
                    }
                    string documento = arregloAnfitriones[anfitrionesCargados-1] -> getDocumento();
                    string codigoAlojamiento = obtenerDato(linea,inicio,delimitador);
                    string nombre = obtenerDato(linea,inicio,delimitador);
                    string municipio = obtenerDato(linea,inicio,delimitador);
                    string departamento = obtenerDato(linea,inicio,delimitador);

                    unsigned int precioNoche;
                    try {
                        precioNoche = static_cast<unsigned int>(stoi(obtenerDato(linea,inicio,delimitador)));
                    } catch(const exception& e) {
                        throw runtime_error("Error en precio: " + string(e.what()));
                    }

                    string tipo = obtenerDato(linea,inicio,delimitador);
                    string direccion = obtenerDato(linea,inicio,delimitador);
                    string amenidades = obtenerDato(linea,inicio,delimitador, false);

                    Alojamiento* nuevoAlojamiento = new Alojamiento(nombre, amenidades, codigoAlojamiento, municipio, departamento, tipo, direccion, documento, precioNoche);

                    if (!arregloAnfitriones[anfitrionesCargados-1] -> agregarAlojamiento(nuevoAlojamiento)) {
                        delete nuevoAlojamiento;
                        throw runtime_error("No se pudo agregar alojamiento al anfitrion");
                    }
                    alojamientosCargados++;
                } else {
                    throw runtime_error("Linea inesperada o alojamiento sin anfitrion activo.");
                }
            } catch(const exception& e) {
                cerr << "Error procesando linea: '" << linea << "'\nMotivo: " << e.what() << endl;
                if (nuevoAnfitrion != nullptr) {
                    delete nuevoAnfitrion;
                }
                if (nuevoAlojamiento != nullptr) {
                    delete nuevoAlojamiento;
                }
                anfitrionActivo = false;
                continue;
            }
        }
    } catch(const exception& e) {
        cerr << "Error critico al cargar anfitriones y alojamientos: " << e.what() << endl;
        archivo.close();

        //limpiar toda la memoria asignada hasta el momento
        for (short i = 0; i < anfitrionesCargados; ++i) {
            delete arregloAnfitriones[i];
        }
        delete[] arregloAnfitriones;
        arregloAnfitriones = nullptr;
        throw;
    }


    archivo.close();
    return anfitrionesCargados;
}

int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes){
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        cerr << "Error: No se pudo abrir el archivo '" << rutaArchivo << "'" << endl;
        return -1;
    }

    string linea = "";
    char delimitador = ',';
    unsigned short capacidadHuespedes = 70;

    if (arregloHuespedes == nullptr) {
        arregloHuespedes = new Huesped*[capacidadHuespedes];
        for(short i = 0; i < capacidadHuespedes; i++){
            arregloHuespedes[i] = nullptr;
        }
    }

    short huespedesCargados = 0;

    try {
        while(getline(archivo, linea)) {
            size_t inicio = 0;
            Huesped* nuevoHuesped = nullptr;

            try {
                if(linea.empty()) continue;  //pa saltar lineas vacias en lugar de romper el ciclo

                string documento = obtenerDato(linea, inicio, delimitador);
                string nombre = obtenerDato(linea, inicio, delimitador);

                float puntuacion;
                try {
                    string puntuacion_str = obtenerDato(linea, inicio, delimitador);
                    puntuacion = stof(puntuacion_str);
                    if ((puntuacion < 0.0f) || (puntuacion > 5.0f)){
                        throw out_of_range("La puntuacion debe estar entre 0 y 5");
                    }

                } catch(const exception& e){
                    throw runtime_error("Error en puntuacion: " + string(e.what()));
                }

                unsigned short antiguedad;
                try {
                    string antiguedad_str = obtenerDato(linea, inicio, delimitador);
                    antiguedad = static_cast<unsigned short>(stoi(antiguedad_str));
                } catch(const exception& e) {
                    throw runtime_error("Antigüedad invalida: " + string(e.what()));
                }

                if(huespedesCargados >= capacidadHuespedes) {
                    redimensionarArreglo(capacidadHuespedes, huespedesCargados, arregloHuespedes);
                }

                nuevoHuesped = new Huesped(nombre, documento, puntuacion, antiguedad);
                arregloHuespedes[huespedesCargados] = nuevoHuesped;
                huespedesCargados++;

            } catch(const exception& e) {
                cerr << "Error procesando linea: " << linea << "\nCausa: " << e.what() << endl;
                if (nuevoHuesped != nullptr) {
                    delete nuevoHuesped;
                }
                continue;
            }
        }

    } catch(const exception& e) {
        cerr << "Error critico al cargar huespedes: " << e.what() << endl;
        archivo.close();

        for (short i = 0; i < huespedesCargados; ++i) {
            delete arregloHuespedes[i];
        }
        delete[] arregloHuespedes;
        arregloHuespedes = nullptr;
        throw;
    }

    return huespedesCargados;
}

int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes) {

    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << rutaArchivo << "'" << endl;
        return -1;
    }

    unsigned short capacidadReservasGlobales = 150;
    char delimitador = ',';
    string linea = "";
    string codigoAlojamiento;
    short indiceAnfitrion = 0;
    short indiceAlojamiento = 0;
    short indiceHuesped = 0;
    short reservasCargadas = 0;
    bool alojamientoActivo = false;

    if (arregloReservas == nullptr) {
        arregloReservas = new Reserva*[capacidadReservasGlobales];
        for (short i = 0; i < capacidadReservasGlobales; ++i) {
            arregloReservas[i] = nullptr;
        }
    }

    try { //este try de aca es pa manejar los errores que puede haber antes del try interno del while
        while (getline(archivo, linea)) {
            size_t inicio = 0;

            if (linea.empty()) continue;

            if (linea.length() == 4) {
                codigoAlojamiento = linea;
                bool codigoEncontrado = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, cantidadAnfitriones, indiceAnfitrion, indiceAlojamiento);

                if (!codigoEncontrado) {
                    throw invalid_argument("Codigo de alojamiento no encontrado: " + codigoAlojamiento + " en linea: " + linea);
                }
                alojamientoActivo = true;
                continue;
            }

            if (alojamientoActivo) {
                Reserva* nuevaReserva = nullptr;

                try { //este try es solo para los errores que puede haber en la linea que se lee
                    string _fechaEntradaStr = obtenerDato(linea, inicio, delimitador);
                    Fecha fechaEntrada = crearFecha(_fechaEntradaStr);
                    string codigoReserva = obtenerDato(linea, inicio, delimitador);
                    string documentoHuesped = obtenerDato(linea, inicio, delimitador);

                    // Campos numericos (usando la plantilla sin unsigned long intermedio)
                    unsigned short estadiaNoches;
                    try {
                        string estadiaNoches_str = obtenerDato(linea, inicio, delimitador);
                        estadiaNoches = static_cast<unsigned short>(stoi(estadiaNoches_str));
                    } catch(const exception& e) {
                        throw runtime_error("Estadia de noche invalida: " + string(e.what()));
                    }

                    string metodoPago = obtenerDato(linea, inicio, delimitador);
                    string _fechaPagoStr = obtenerDato(linea, inicio, delimitador);
                    Fecha fechaPago = crearFecha(_fechaPagoStr);

                    unsigned int montoPago;
                    try {
                        string montoPago_str = obtenerDato(linea, inicio, delimitador);
                        montoPago = static_cast<unsigned int>(stoi(montoPago_str));
                    } catch(const exception& e) {
                        throw runtime_error("Monto de pago invalida: " + string(e.what()));
                    }

                    string inquietudes = obtenerDato(linea, inicio, delimitador, false);

                    //validaciones de indices y punteros
                    if (indiceAnfitrion >= cantidadAnfitriones || indiceAnfitrion < 0) {
                        throw out_of_range("indice de anfitrion invalido.");
                    }

                    indiceHuesped = buscarHuespedPorDocumento(arregloHuespedes, documentoHuesped, cantidadHuespedes);
                    if (indiceHuesped == -1) {
                        throw invalid_argument("Huesped no registrado: " + documentoHuesped);
                    }

                    Anfitrion* anfitrion = arregloAnfitriones[indiceAnfitrion];
                    if (anfitrion == nullptr) {
                        throw logic_error("Anfitrion no inicializado en el indice: " + to_string(indiceAnfitrion));
                    }

                    Alojamiento* alojamientoActual = anfitrion -> getAlojamiento(indiceAlojamiento);
                    Huesped* huespedActual = arregloHuespedes[indiceHuesped];

                    if (alojamientoActual == nullptr || huespedActual == nullptr) {
                        throw logic_error("Alojamiento o huesped asociado no encontrado.");
                    }

                    if (reservasCargadas >= capacidadReservasGlobales) {
                        redimensionarArreglo(capacidadReservasGlobales, reservasCargadas, arregloReservas);
                    }

                    nuevaReserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago, estadiaNoches, montoPago, huespedActual, alojamientoActual);
                    arregloReservas[reservasCargadas] = nuevaReserva;
                    alojamientoActual -> agregarReserva(nuevaReserva);
                    huespedActual -> agregarReserva(nuevaReserva);
                    reservasCargadas++;

                } catch (const exception& e) {
                    cerr << "Error al procesar linea de reserva: '" << linea << "'. Causa: " << e.what() << endl;
                    if (nuevaReserva != nullptr) {
                        delete nuevaReserva;
                    }
                    continue;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error critico al cargar las reservas: " << e.what() << endl;
        archivo.close();
        for (short i = 0; i < reservasCargadas; ++i) {
            delete arregloReservas[i];
        }
        delete[] arregloReservas;
        arregloReservas = nullptr;
        throw;
    }

    archivo.close();
    return reservasCargadas;
}
