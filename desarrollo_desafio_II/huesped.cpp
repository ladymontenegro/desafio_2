#include "huesped.h"

Huesped::Huesped(const string &_nombre,
                 const string &_documento,
                 float _puntuacion,
                 unsigned short _antiguedadMeses)
    : nombre(_nombre)
    , documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
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

unsigned short Huesped::getaAtiguedadMeses() const
{
    return antiguedadMeses;
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

// Otros metodos
