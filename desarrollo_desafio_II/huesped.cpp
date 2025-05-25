#include "huesped.h"

Huesped::Huesped(const string &_nombre,
                 const string &_documento,
                 float _puntuacion,
                 unsigned short _antiguedadMeses)
    : nombre(_nombre)
    , documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , reservas(nullptr)
{}

// Metodos get
const string Huesped::getNombre()
{
    return nombre;
}

const string Huesped::getDocumento()
{
    return documento;
}

float Huesped::getPuntuacion() const
{
    return puntuacion;
}

unsigned short Huesped::getaAntiguedadMeses() const
{
    return antiguedadMeses;
}

Reserva **Huesped::getReservas() const
{
    return reservas;
}

// Metodos set

void Huesped::setPuntuacion(float _puntuacion)
{
    puntuacion = _puntuacion;
}

void Huesped::setAntiguedadMeses(unsigned short _antiguedadMeses)
{
    antiguedadMeses = _antiguedadMeses;
}

void Huesped::setReservas(Reserva **_reservas)
{
    reservas = _reservas;
}

// Otros metodos
