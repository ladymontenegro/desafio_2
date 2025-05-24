#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//FUNCIONES PARA CARGA DE DATOS EN ESTRUCTURAS Y CLASES
int cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion** arregloAnfitriones) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
        return -1;
    }

    short anfitrionesCargados = 0;
    short alojamientosCargados = 0;
    bool anfitrionActivo = false;
    string linea;

    if (arregloAnfitriones == nullptr) {
        arregloAnfitriones = new Anfitrion*[maximoAnfitriones];
        for (int i = 0; i < maximoAnfitriones; ++i) {
            arregloAnfitriones[i] = nullptr;
        }
    }

    while (getline(archivo, linea)) {
        size_t inicio = 0;

        if (esDocumento(linea, inicio)) { //pa ver si es anfitrion
            if (!puedeAgregar(anfitrionesCargados, maximoAnfitriones)) {
                cerr << "Limite de anfitriones alcanzado (" << maximoAnfitriones << ")\n";
                break;
            }

            //obtener atributos de anfitrion
            string documento = obtenerDato(linea, inicio);
            float puntuacion = stof(obtenerDato(linea, inicio));
            unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea, inicio)));

            arregloAnfitriones[anfitrionesCargados] = new Anfitrion(documento, puntuacion, antiguedad);
            anfitrionesCargados++;
            alojamientosCargados = 0;  //se resetea pa contar cada uno de los alojamientos relacionados a un anfitrion
            anfitrionActivo = true;
        }
        else if (anfitrionActivo) {  //si no es anfitrion, es alojamiento
            if (!puedeAgregar(alojamientosCargados, maximoAlojamientosPorAnfitrion)) {
                cerr << "Límite de alojamientos alcanzado para anfitrión " << arregloAnfitriones[anfitrionesCargados-1] -> getDocumento()<< " (" << alojamientosPorAnfitrion << ")\n";
                break;
            }

            //obtener atributos de alojamiento
            string documento = arregloAnfitriones[anfitrionesCargados-1] -> getDocumento();
            string codigoAlojamiento = obtenerDato(linea, inicio);
            string nombre = obtenerDato(linea, inicio);
            string municipio = obtenerDato(linea, inicio);
            string departamento = obtenerDato(linea, inicio);
            string precioNoche = static_cast<unsigned int>(stoi(obtenerDato(linea, inicio)));
            string tipo = obtenerDato(linea, inicio);
            string direccion = obtenerDato(linea, inicio);
            string amenidades = obtenerDato(linea, inicio);

            //crear y agregar alojamiento
            Alojamiento* nuevoAlojamiento = new Alojamiento(nombre, amenidades, codigoAlojamiento, municipio, departamento, tipo, direccion, documento, precioNoche);
            //reserva memoria para un Anfitrion y retorna su dirección (puntero de tipo Anfitrion*).

            if (arregloAnfitriones[anfitrionesCargados-1] -> agregarAlojamiento(nuevoAlojamiento)) {
                alojamientosCargados++;
            } else {
                delete nuevoAlojamiento;  //libera memoria si no se pudo agregar
            }
        }
    }

    archivo.close();
}

int cargarDatosHuespedes(const string& rutaArchivo, Huesped**& arregloHuespedes){
    string linea = "";
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return -1;
    }

    if (arregloHuespedes == nullptr) {
        arregloHuespedes = new Huesped*[maximoHuespedes];
    }

    short huespedesCargados = 0;

    while(getline(archivo, linea)){
        if (!puedeAgregar(huespedesCargados, maximoHuespedes)) {
            cerr << "Limite de anfitriones alcanzado (" << maximoHuespedes << ")\n";
            break;
        }
        size_t inicio = 0;

        //Rrecordar agregar las excepciones !!!
        string documento = obtenerDato(linea, inicio);
        string nombre = obtenerDato(linea, inicio);
        float puntuacion = stof(obtenerDato(linea, inicio));
        unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea, inicio)));

        arregloHuespedes[huespedesCargados] = new Huesped(nombre, documento, puntuacion, antiguedad);
        //reserva memoria para un Huesped y retorna su dirección (puntero de tipo Hueped*)
        huespedesCargados++;
    }

    return huespedesCargados;
}

void cargarDatosReservas(string& rutaArchivo){
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return -1;
    }

    //Leemos la reserva, extraemos el dato del huesped y del alojamiento y por partes
    //separadas buscamos en el arreglo de alojamiento y de huespedes
    //Busquemo primero en alojamientos

    //Cuando se este vinculando las reservas del huesped con las del alojamiento,
    //hacer una funcion de tipo merge-sort para que sus reserves queden organizadas
    //de la fecha mas cercana a la lejana, al igual que con el alojamiento
}

//FUNCIONES PARA CARGA DE DATOS EN ARCHIVOS

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio) {
    size_t fin = linea.find(',', inicio);
    string atributo;

    if (fin != string::npos) { // si se encontro una coma
        atributo = linea.substr(inicio, fin - inicio);
        inicio = fin + 1; // actualiza el inicio para el proximo atributo, por eso se pasa por referencia
    } else { // pa que igual tome el ultimo atributo que no tiene coma
        atributo = linea.substr(inicio);
        inicio = linea.length(); // evita procesar mas atributos
    }
    return atributo;
}

bool esDocumento(const string& linea, size_t& inicio){
    bool documento = false;
    size_t fin = linea.find(',', inicio);
    string identificador = linea.substr(inicio, fin - inicio);

    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool puedeAgregar(short cantidadActual, short limite) { //funcion de monitoreo de tamanio
    return cantidadActual < limite;
}
