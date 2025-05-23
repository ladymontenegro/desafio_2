#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//FUNCIONES PARA CARGA DE DATOS EN ESTRUCTURAS Y CLASES
void cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion* arregloAnfitriones[]) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
        return -1;
    }

    short anfitrionesCargados = 0;
    short alojamientosCargados = 0;
    bool anfitrionActivo = false;
    string linea;

    while (getline(archivo, linea)) {
        size_t inicio = 0;

        if (esDocumento(linea, inicio)) { //pa ver si es anfitrion
            if (!puedeAgregar(anfitrionesCargados, anfitriones)) {
                cerr << "Limite de anfitriones alcanzado (" << anfitriones << ")\n";
                continue;
            }

            //obtener atributos de anfitrion
            string documento = obtenerDato(linea, inicio);
            float puntuacion = stof(obtenerDato(linea, inicio));
            short antiguedad = static_cast<short>(stoi(obtenerDato(linea, inicio)));

            arregloAnfitriones[anfitrionesCargados] = new Anfitrion(documento, puntuacion, antiguedad);
            anfitrionesCargados++;
            alojamientosCargados = 0;  //se resetea pa contar cada uno de los alojamientos relacionados a un anfitrion
            anfitrionActivo = true;
        }
        else if (anfitrionActivo) {  //si no es anfitrion, es alojamiento
            if (!puedeAgregar(alojamientosCargados, alojamientosPorAnfitrion)) {
                cerr << "Límite de alojamientos alcanzado para anfitrión " << arregloAnfitriones[anfitrionesCargados-1] -> getDocumento()<< " (" << alojamientosPorAnfitrion << ")\n";
                continue;
            }

            //obtener atributos de alojamiento
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

            if (arregloAnfitriones[anfitrionesCargados-1] -> agregarAlojamiento(nuevoAlojamiento)) {
                alojamientosCargados++;
            } else {
                delete nuevoAlojamiento;  //libera memoria si no se pudo agregar
            }
        }
    }

    archivo.close();
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

bool esDocumento(const string& lineaArchivo, size_t& inicio){
    bool documento = false;
    size_t fin = lineaArchivo.find(',', inicio);
    string identificador = lineaArchivo.substr(inicio, fin - inicio);

    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool puedeAgregar(short cantidadActual, short limite) { //funcion de monitoreo de tamanio
    return cantidadActual < limite;
}
