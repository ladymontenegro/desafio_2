#include "anfitrion.h"

Anfitrion::Anfitrion(const string &_documento,
                     float _puntuacion,
                     unsigned short _antiguedadMeses,
                     unsigned short _alojamientosCargados)
    : documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , cantidadDeAlojamientos(0)
    , alojamientosCargados(_alojamientosCargados)
{
    alojamientos = new Alojamiento *[cantidadDeAlojamientos];
}

Anfitrion::~Anfitrion()
{
    for (short i = 0; i < cantidadDeAlojamientos; ++i) {
        delete alojamientos[i]; //libera cada Alojamiento
    }
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

unsigned short Anfitrion::getAlojamientosCargados() const
{
    return alojamientosCargados;
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

bool Anfitrion::agregarAlojamiento(Alojamiento *_alojamiento)
{
    if (alojamientosCargados >= cantidadDeAlojamientos) {
        return false; //limite alcanzado
    }
    alojamientos[cantidadDeAlojamientos] = _alojamiento;
    cantidadDeAlojamientos++;
    return true;
}

void Anfitrion::consultarAlojamiento(unsigned short indice) {}
