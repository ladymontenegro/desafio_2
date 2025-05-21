#include "alojamiento.h"

Alojamiento::Alojamiento(const string &_nombre,
                         const string &_amenidades,
                         const string &_codigo,
                         const string &_municipio,
                         const string &_departamento,
                         const string &_tipo,
                         const string &_direccion,
                         const string &_documentoAnfitrion,
                         unsigned int _precioNoche,
                         Reserva **_reservas)
    : nombre(_nombre)
    , amenidades(_amenidades)
    , codigo(_codigo)
    , municipio(_municipio)
    , departamento(_departamento)
    , tipo(_tipo)
    , direccion(_direccion)
    , documentoAnfitrion(_documentoAnfitrion)
    , precioNoche(_precioNoche)
    , reservas(_reservas)
{
    //Reservar memoria
}

Alojamiento::~Alojamiento()
{
    // Liberar Memoria !!!!!!
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

void Alojamiento::setPrecioNoches(const unsigned int &_precioNoche)
{
    precioNoche = _precioNoche;
}

void Alojamiento::setReservas(Reserva **_reservas)
{
    // ????????????
    reservas = _reservas;
}

/*
// Otros metodos 
bool Alojamiento::alojamientoDisponible(const string &fechaInicio, const string &fechaFin) const
{
    //??????????????????????
    return true;
}
*/
