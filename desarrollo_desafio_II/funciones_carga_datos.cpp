#include <iostream>
#include <fstream>
#include <string>
#include "header_funciones.h"
using namespace std;


//FUNCIONES PARA CARGA DE DATOS EN ESTRUCTURAS Y CLASES
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion**& arregloAnfitriones) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
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

    while (getline(archivo, linea)) {
        size_t inicio = 0;

        if (esDocumento(linea,inicio)) { //pa ver si es anfitrion
            //obtener atributos de anfitrion
            string documento = obtenerDato(linea,inicio,delimitador);
            float puntuacion = stof(obtenerDato(linea,inicio,delimitador));
            unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));

            if(anfitrionesCargados < capacidadAnfitriones){
                arregloAnfitriones[anfitrionesCargados] = new Anfitrion(documento, puntuacion, antiguedad);
                anfitrionesCargados++;
            } else {
                redimensionarArreglo(capacidadAnfitriones, anfitrionesCargados, arregloAnfitriones);
            }

            alojamientosCargados = 0;  //se resetea pa contar cada uno de los alojamientos relacionados a un anfitrion
            anfitrionActivo = true;
        }
        else if (anfitrionActivo) {  //si no es anfitrion, es alojamiento
            //obtener atributos de alojamiento
            string documento = arregloAnfitriones[anfitrionesCargados-1] -> getDocumento();
            string codigoAlojamiento = obtenerDato(linea,inicio,delimitador);
            string nombre = obtenerDato(linea,inicio,delimitador);
            string municipio = obtenerDato(linea,inicio,delimitador);
            string departamento = obtenerDato(linea,inicio,delimitador);
            unsigned int precioNoche = static_cast<unsigned int>(stoi(obtenerDato(linea,inicio,delimitador)));
            string tipo = obtenerDato(linea,inicio,delimitador);
            string direccion = obtenerDato(linea,inicio,delimitador);
            string amenidades = obtenerDato(linea,inicio,delimitador);

            //crear y agregar alojamiento
            Alojamiento* nuevoAlojamiento = new Alojamiento(nombre, amenidades, codigoAlojamiento, municipio, departamento, tipo, direccion, documento, precioNoche);
            //reserva memoria para un Anfitrion y retorna su dirección (puntero de tipo Anfitrion*).

            if (arregloAnfitriones[anfitrionesCargados - 1] -> agregarAlojamiento(nuevoAlojamiento)) {
                alojamientosCargados++;
            } else {
                delete nuevoAlojamiento;  //libera memoria si no se pudo agregar
            }
        }
    }

    archivo.close();

    return anfitrionesCargados;
}

int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes){
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
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

    while(getline(archivo, linea)){
        size_t inicio = 0;

        if(linea == ""){
            break;
        }

        //Recordar agregar las excepciones !!!
        string documento = obtenerDato(linea,inicio,delimitador);
        string nombre = obtenerDato(linea,inicio,delimitador);
        float puntuacion = stof(obtenerDato(linea,inicio,delimitador));
        unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));

        if(huespedesCargados < capacidadHuespedes){
            arregloHuespedes[huespedesCargados] = new Huesped(nombre, documento, puntuacion, antiguedad);
            //reserva memoria para un Huesped y retorna su dirección (puntero de tipo Hueped*)
            huespedesCargados++;
        } else {
            redimensionarArreglo(capacidadHuespedes, huespedesCargados, arregloHuespedes);
        }
    }
    return huespedesCargados;
}

int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes){
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
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

    if(arregloReservas == nullptr){
        arregloReservas = new Reserva*[capacidadReservasGlobales];
        for(short i = 0; i < capacidadReservasGlobales; i++){
            arregloReservas[i] = nullptr;
        }
    }

    while(getline(archivo, linea)){
        size_t inicio = 0;
        Alojamiento* alojamientoActual = nullptr;
        Huesped* huespedActual = nullptr;

        if(linea == ""){
            break;
        }

        if((linea.length()) == 4){
            codigoAlojamiento = linea;
            bool codigoEncontrado = buscarAlojamientoPorCodigo(arregloAnfitriones, codigoAlojamiento, cantidadAnfitriones, indiceAnfitrion, indiceAlojamiento);
            alojamientoActivo = codigoEncontrado;
        }

        else if(alojamientoActivo){
            string _fechaEntrada = obtenerDato(linea,inicio,delimitador);
            Fecha fechaEntrada = crearFecha(_fechaEntrada);
            string codigoReserva = obtenerDato(linea,inicio,delimitador);
            string documentoHuesped = obtenerDato(linea,inicio,delimitador);
            unsigned short estadiaNoches = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));
            string metodoPago = obtenerDato(linea,inicio,delimitador);
            string _fechaPago = obtenerDato(linea,inicio,delimitador);
            Fecha fechaPago = crearFecha(_fechaPago);
            unsigned int montoPago= stoi(obtenerDato(linea,inicio,delimitador));
            string inquietudes = obtenerDato(linea,inicio,delimitador);

            indiceHuesped = buscarHuespedPorDocumento(arregloHuespedes, documentoHuesped, cantidadHuespedes);
            if (indiceHuesped != -1) {
                huespedActual = arregloHuespedes[indiceHuesped];
            }

            Anfitrion* anfitrion = arregloAnfitriones[indiceAnfitrion];
            if (anfitrion != nullptr) {
                alojamientoActual = anfitrion -> getAlojamiento(indiceAlojamiento);
            }

            if(alojamientoActual != nullptr && huespedActual != nullptr){
                //se instancia el objeto
                Reserva* reserva = new Reserva(codigoReserva, metodoPago, inquietudes, fechaEntrada, fechaPago, estadiaNoches, montoPago, huespedActual, alojamientoActual);

                //se apunta la reserva a sus respectivos alojamiento y huesped
                alojamientoActual -> agregarReserva(reserva);
                huespedActual -> agregarReserva(reserva);

                if (reservasCargadas < capacidadReservasGlobales) {
                    //se agrega la reserva en el arreglo general de reservas
                    arregloReservas[reservasCargadas] = reserva;
                    reservasCargadas++;
                } else {
                    redimensionarArreglo(capacidadReservasGlobales, reservasCargadas, arregloReservas);
                }
            }
        }
    }
    return reservasCargadas;
}

//FUNCIONES PARA CARGA DE DATOS EN ARCHIVOS
