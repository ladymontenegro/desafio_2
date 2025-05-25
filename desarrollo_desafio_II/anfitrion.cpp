#include "anfitrion.h"

Anfitrion::Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses)
    : documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
{
    alojamientos = new Alojamiento *[10];
}

// Metodos get
const string Anfitrion::getDocumento()
{
    return documento;
}

float Anfitrion::getPuntuacion() const
{
    return puntuacion;
}

unsigned short Anfitrion::getAntiguedadMeses() const
{
    return antiguedadMeses;
}

Alojamiento **Anfitrion::getAlojamimentos() const
{
    return alojamientos;
}

// Metodos set

void Anfitrion::setPuntuacion(float _puntuacion)
{
    puntuacion = _puntuacion;
}

void Anfitrion::setAntiguedadMeses(unsigned short _antiguedadMeses)
{
    antiguedadMeses = _antiguedadMeses;
}

void Anfitrion::setAlojamientos(Alojamiento **_alojamientos)
{
    alojamientos = _alojamientos;
}

// Otros metodos
void Anfitrion::consultarReservas() const {}

void Anfitrion::anularReserva() {}
