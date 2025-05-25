#include <iostream>
#include <fstream>
#include <string>
using namespace std;


//FUNCIONES PARA CARGA DE DATOS EN ESTRUCTURAS Y CLASES
short cargarDatosAnfitriones(const string& rutaArchivo, Anfitrion** arregloAnfitriones) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
        return -1;
    }

    char delimitador = ',';
    short anfitrionesCargados = 0;
    short alojamientosCargados = 0;
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
            if (!puedeAgregar(anfitrionesCargados, capacidadAnfitriones)) {
                cerr << "Limite de anfitriones alcanzado (" << capacidadAnfitriones << ")\n";
                break;
            }

            //obtener atributos de anfitrion
            string documento = obtenerDato(linea,inicio,delimitador);
            float puntuacion = stof(obtenerDato(linea,inicio,delimitador));
            unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));

            arregloAnfitriones[anfitrionesCargados] = new Anfitrion(documento, puntuacion, antiguedad);
            anfitrionesCargados++;
            alojamientosCargados = 0;  //se resetea pa contar cada uno de los alojamientos relacionados a un anfitrion
            anfitrionActivo = true;
        }
        else if (anfitrionActivo) {  //si no es anfitrion, es alojamiento
            if (!puedeAgregar(alojamientosCargados, capacidadAlojamientosPorAnfitrion)) {
                cerr << "Límite de alojamientos alcanzado para anfitrión " << arregloAnfitriones[anfitrionesCargados-1] -> getDocumento()<< " (" << alojamientosPorAnfitrion << ")\n";
                break;
            }

            //obtener atributos de alojamiento
            string documento = arregloAnfitriones[anfitrionesCargados-1] -> getDocumento();
            string codigoAlojamiento = obtenerDato(linea,inicio,delimitador);
            string nombre = obtenerDato(linea,inicio,delimitador);
            string municipio = obtenerDato(linea,inicio,delimitador);
            string departamento = obtenerDato(linea,inicio,delimitador);
            string precioNoche = static_cast<unsigned int>(stoi(obtenerDato(linea,inicio,delimitador)));
            string tipo = obtenerDato(linea,inicio,delimitador);
            string direccion = obtenerDato(linea,inicio,delimitador);
            string amenidades = obtenerDato(linea,inicio,delimitador);

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

    return anfitrionesCargados;
}

int cargarDatosHuespedes(const string& rutaArchivo, Huesped** arregloHuespedes){
    string linea = "";
    char delimitador = ',';
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return -1;
    }

    if (arregloHuespedes == nullptr) {
        arregloHuespedes = new Huesped*[capacidadHuespedes];
    }

    short huespedesCargados = 0;

    while(getline(archivo, linea)){
        if (!puedeAgregar(huespedesCargados, capacidadHuespedes)) {
            cerr << "Limite de anfitriones alcanzado (" << capacidadHuespedes << ")\n";
            break;
        }
        size_t inicio = 0;

        //Rrecordar agregar las excepciones !!!
        string documento = obtenerDato(linea,inicio,delimitador);
        string nombre = obtenerDato(linea,inicio,delimitador);
        float puntuacion = stof(obtenerDato(linea,inicio,delimitador));
        unsigned short antiguedad = static_cast<unsigned short>(stoi(obtenerDato(linea,inicio,delimitador)));

        arregloHuespedes[huespedesCargados] = new Huesped(nombre, documento, puntuacion, antiguedad);
        //reserva memoria para un Huesped y retorna su dirección (puntero de tipo Hueped*)
        huespedesCargados++;
    }

    return huespedesCargados;
}

int cargarDatosReservas(string& rutaArchivo, Reserva**& arregloReservas, Anfitrion**& arregloAnfitriones, Huesped**& arregloHuespedes, short cantidadAnfitriones, short cantidadHuespedes){
    ifstream archivo(rutaArchivo);
    if(!archivo.is_open()){
        return -1;
    }

    if(arregloReservas == nullptr){
        arregloReservas = new Reserva*[capacidadReservasGlobales];
        for(short i = 0; i < capacidadReservasGlobales; i++){
            arregloReservas[i] = nullptr;
        }
    }

    char delimitador = ',';
    char character = '-';
    string linea = "";
    string codigoAlojamiento;
    short indiceAnfitrion = 0;
    short indiceAlojamiento = 0;
    short indiceHuesped = 0;
    short reservasCargadas = 0;
    short capacidadReservasGlobales = 0;
    bool alojamientoActivo = false;

    while(getline(archivo, linea)){
        size_t inicio = 0;
        Alojamiento* alojamientoActual = nullptr;
        Huesped* huespedActual = nullptr;

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
                    // Manejar error: arreglo lleno
                }
            }
        }
    }
    return reservasCargadas;
}

//FUNCIONES PARA CARGA DE DATOS EN ARCHIVOS

//FUNCIONES AUXILIARES
string obtenerDato(const string& linea, size_t& inicio, char delimitador) {
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
    size_t fin = linea.find(delimitador, inicio);
    string identificador = linea.substr(inicio, fin - inicio);

    if((identificador.length()) == 10){
        documento = true;
    }

    return documento;
}

bool puedeAgregar(short cantidadActual, short limite) { //funcion de monitoreo de tamanio
    return cantidadActual < limite;
}

short buscarHuespedPorDocumento(Huesped**& arregloHuespedes, const string &documento, unsigned short cantidadHuespedes){
    for(short i = 0; i < cantidadHuespedes; i++){
        if(arregloHuespedes[i] -> getDocumento == documento){
            return i;
        }
    }
    return -1;
}

bool buscarAlojamientoPorCodigo(Anfitrion**& arregloAnfitriones, const string &codigo, short cantidadAnfitriones, short &indiceAnfitrion, short &indiceAlojamiento){
    cout << si;
    for(short i = 0; i < cantidadAnfitriones; i++){
        for(short j = 0; j < arregloAnfitriones[i] -> getCantidadAlojamientos; j++){
            if((arregloAnfitriones[i] -> getAlojamiento(j) -> getCodigo) == codigo){
                indiceAnfitrion = i;
                indiceAlojamiento = j;
                return true;
            }
        }
    }
    return false;
}

Fecha crearFecha(const string &fechaStr){
    size_t inicio = 0;
    const char delimitador = '-';
    unsigned char dia = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
    unsigned char mes = static_cast<unsigned char>(stoi(obtenerDato(fechaStr, inicio, delimitador)));
    unsigned short anio = static_cast<unsigned short>(stoi(obtenerDato(fechaStr, inicio, delimitador)));

    Fecha fechaCreada(dia, mes, anio);

    return fechaCreada;
}
