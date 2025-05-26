#include <iostream>
#include <fstream>
#include <string>

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
        throw invalid_argument(nombreCampoError + " vacio en la linea de datos.");
    }

    return atributo;
}

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

Fecha crearFecha(const string &fechaStr){
    if(fechaStr != ""){
        size_t inicio = 0;
        const char delimitador = '-';

        unsigned char dia = '';
        unsigned char mes = '';
        unsigned short anio = 0;
        try {
            dia = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
            mes = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
            anio = static_cast<unsigned short>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
        } catch (const exception& e) {
            throw invalid_argument("Error en formato numerico: " + string(e.what()));
        }

        Fecha fechaCreada(dia, mes, anio);

        return fechaCreada;
    }
}






