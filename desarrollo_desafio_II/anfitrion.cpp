#include "anfitrion.h"

//Constructor de la clase
Anfitrion::Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses)
    : documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , capacidadDeAlojamientos(10)
    , alojamientosCargados(0)
{
    alojamientos = new Alojamiento *[capacidadDeAlojamientos];
    for (unsigned short i = 0; i < capacidadDeAlojamientos; i++) {
        alojamientos[i] = nullptr;
    }
}

//Destructor de la clase
Anfitrion::~Anfitrion()
{
    for (short i = 0; i < alojamientosCargados; ++i) {
        if (alojamientos[i] != nullptr) {
            delete alojamientos[i];
            alojamientos[i] = nullptr;
        }
    }
    delete[] alojamientos;
    alojamientos = nullptr;
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

unsigned short Anfitrion::getcapacidadDeAlojamientos() const
{
    return capacidadDeAlojamientos;
}

Alojamiento *Anfitrion::getAlojamiento(short indice) const
{
    if (indice >= 0 && indice < capacidadDeAlojamientos) {
        return alojamientos[indice];
    } else {
        return nullptr;
    }
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
    if (alojamientosCargados >= capacidadDeAlojamientos) {
        return false; //limite alcanzado
    }
    alojamientos[alojamientosCargados] = _alojamiento;
    alojamientosCargados++;
    return true;
}

void Anfitrion::consultarAlojamiento(unsigned short indice) {}
