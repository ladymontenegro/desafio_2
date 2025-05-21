#include "anfitrion.h"

Anfitrion::Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses)
    : documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , alojamientos(nullptr)
{}

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

// Metodos set

void Anfitrion::setPuntuacion(float _puntuacion)
{
    puntuacion = _puntuacion;
}

void Anfitrion::setAntiguedadMeses(unsigned short _antiguedadMeses)
{
    antiguedadMeses = _antiguedadMeses;
}

void Anfitrion::setAlojamientos(Alojamiento **_alojamientos, unsigned int numeroAlojamientos) {}

// Otros metodos
void Anfitrion::consultarReservas() const {}

void Anfitrion::anularReserva() {}
