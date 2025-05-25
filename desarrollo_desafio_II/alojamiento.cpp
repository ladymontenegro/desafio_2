#include "alojamiento.h"

#include <iostream>

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
    , cantidadDeReservas(0)
{
    reservas = new Reserva *[cantidadDeReservas];
}

Alojamiento::~Alojamiento()
{
    for (unsigned short i = 0; i < cantidadDeReservas; ++i) {
        delete reservas[i]; //libera cada Alojamiento
    }
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

    for (unsigned short i = 0; i < cantidadDeReservas; i++) {
        Fecha entradaExistente = reservas[i]->getFechaEntrada();
        Fecha salidaExistente = entradaExistente.sumarDias(reservas[i]->getEstadiaNoches());

        if (!(fechaSalida <= entradaExistente || fechaInicio >= salidaExistente)) {
            return false; // Hay traslape
        }
    }
    return true; // No hay traslape con ninguna reserva
}

void Alojamiento::eliminarReserva(string _codigoReserva)
{
    for (unsigned short i = 0; i < cantidadDeReservas; i++) {
        if ((reservas[i]->getCodigoReserva()) == _codigoReserva) {
            reservas[i] = nullptr;
            cout << "Reserva eliminada" << endl;
        }
    }
    cout << "No existe alguna reserva con este codigo..." << endl;
}
