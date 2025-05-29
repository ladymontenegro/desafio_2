#include "alojamiento.h"
#include "variablesIteracionesMemoria.h"
#include <iostream>

//Constructor de la clase
Alojamiento::Alojamiento(const string &_nombre,
                         const string &_amenidades,
                         const string &_codigo,
                         const string &_municipio,
                         const string &_departamento,
                         const string &_tipo,
                         const string &_direccion,
                         const string &_documentoAnfitrion,
                         unsigned int _precioNoche)
    : nombre(_nombre)
    , amenidades(_amenidades)
    , codigo(_codigo)
    , municipio(_municipio)
    , departamento(_departamento)
    , tipo(_tipo)
    , direccion(_direccion)
    , documentoAnfitrion(_documentoAnfitrion)
    , precioNoche(_precioNoche)
    , capacidadReservas(100)
    , reservasCargadas(0)
{
    reservas = new Reserva *[capacidadReservas]();
}

// Costructor de copia
Alojamiento::Alojamiento(const Alojamiento &otro)
    : nombre(otro.nombre)
    , amenidades(otro.amenidades)
    , codigo(otro.codigo)
    , municipio(otro.municipio)
    , departamento(otro.departamento)
    , tipo(otro.tipo)
    , direccion(otro.direccion)
    , documentoAnfitrion(otro.documentoAnfitrion)
    , precioNoche(otro.precioNoche)
    , capacidadReservas(otro.capacidadReservas)
    , reservasCargadas(otro.reservasCargadas)
{
    reservas = new Reserva *[capacidadReservas]();

    for (unsigned short i = 0; i < reservasCargadas; ++i) {
        Globales::contadorIteraciones++;
        if (otro.reservas[i] != nullptr) {
            reservas[i] = new Reserva(*(otro.reservas[i]));
        } else {
            reservas[i] = nullptr;
        }
    }
}

//Destructor de la clase
Alojamiento::~Alojamiento()
{
    for (unsigned short i = 0; i < reservasCargadas; ++i) {
        Globales::contadorIteraciones++;
        if (reservas[i] != nullptr) {
            reservas[i] = nullptr;
        }
    }
    delete[] reservas;
    reservas = nullptr;
}

size_t Alojamiento::calcularMemoria() const {
    size_t total = sizeof(*this);

    //solo suma el ARREGLO DE PUNTEROS
    if (reservas) {
        total += static_cast<size_t>(capacidadReservas) * sizeof(Reserva*);
    }
    return total;
}

// Metodos get
string Alojamiento::getNombre() const
{
    return nombre;
}

string Alojamiento::getAmenidades() const
{
    return amenidades;
}

const string Alojamiento::getCodigo()
{
    return codigo;
}

const string Alojamiento::getMunicipio()
{
    return municipio;
}

const string Alojamiento::getDepartamento()
{
    return departamento;
}

const string Alojamiento::getTipo()
{
    return tipo;
}

const string Alojamiento::getDireccion()
{
    return direccion;
}

const string Alojamiento::getDocumentoAnfitrion()
{
    return documentoAnfitrion;
}

unsigned int Alojamiento::getPrecioNoche() const
{
    return precioNoche;
}

unsigned short Alojamiento::getCapacidadReservas() const
{
    return capacidadReservas;
}

unsigned short Alojamiento::getReservasCargadas() const
{
    return reservasCargadas;
}

Reserva **Alojamiento::getReservas() const
{
    return reservas;
}

// Metodos set
void Alojamiento::setNombre(const string &_nombre)
{
    nombre = _nombre;
}

void Alojamiento::setAmenidades(const string &_amenidades)
{
    amenidades = _amenidades;
}

void Alojamiento::setPrecioNoches(const unsigned int _precioNoche)
{
    precioNoche = _precioNoche;
}

void Alojamiento::setReservas(Reserva **_reservas)
{
    reservas = _reservas;
}

// Otros metodos
bool Alojamiento::alojamientoDisponible(Fecha fechaInicio, unsigned int _cantidadDeNoches) const
{
    Fecha fechaSalida = fechaInicio.sumarDias(_cantidadDeNoches);

    for (unsigned short i = 0; i < reservasCargadas; i++) {
        Globales::contadorIteraciones++;
        if (reservas[i] != nullptr) {
            Fecha entradaExistente = reservas[i]->getFechaEntrada();
            Fecha salidaExistente = entradaExistente.sumarDias(reservas[i]->getEstadiaNoches());

            if (!(fechaSalida <= entradaExistente || fechaInicio >= salidaExistente)) {
                return false; // Hay traslape
            }
        }
    }
    return true; // No hay traslape con ninguna reserva
}

void Alojamiento::eliminarReserva(string _codigoReserva)
{
    for (unsigned short i = 0; i < reservasCargadas; i++) {
        Globales::contadorIteraciones++;
        if (reservas[i] != nullptr) {
            if (reservas[i]->getCodigoReserva() == _codigoReserva) {
                reservas[i] = nullptr;
                if (i != reservasCargadas - 1) {
                    for (unsigned short j = i; j < reservasCargadas - 1; j++) {
                        reservas[j] = reservas[j + 1];
                    }
                    reservas[reservasCargadas - 1] = nullptr;
                }
                reservasCargadas--;
            }
        }
    }
}

void Alojamiento::agregarReserva(Reserva *nuevaReserva)
{
    if (reservasCargadas >= capacidadReservas) {
        int nuevaCapacidad;
        if (capacidadReservas == 0) {
            nuevaCapacidad = 1;
        } else {
            nuevaCapacidad = capacidadReservas * 2;
        }

        Reserva **nuevoArreglo = new Reserva *[nuevaCapacidad];

        for (int i = 0; i < reservasCargadas; i++) {
            Globales::contadorIteraciones++;
            nuevoArreglo[i] = reservas[i];
        }

        for (int i = reservasCargadas; i < nuevaCapacidad; i++) {
            Globales::contadorIteraciones++;
            nuevoArreglo[i] = nullptr;
        }
        delete[] reservas;

        reservas = nuevoArreglo;
        capacidadReservas = nuevaCapacidad;
    }
    reservas[reservasCargadas] = nuevaReserva;
    reservasCargadas++;
}

void Alojamiento::mostrarAlojamiento()
{
    cout << "\nNombre: " << nombre << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Precio por noche: " << precioNoche << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Documento del anfitrion: " << documentoAnfitrion << endl;
    cout << "Amenidades: " << amenidades << endl << endl;
}
