#include "huesped.h"

Huesped::Huesped(const string &_nombre,
                 const string &_documento,
                 float _puntuacion,
                 unsigned short _antiguedadMeses)
    : nombre(_nombre)
    , documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    //, reservas(nullptr)
    , capacidadReservas(20)
    , reservasCargadas(0)
{
    reservas = new Reserva *[capacidadReservas];
    for (unsigned short i = 0; i < capacidadReservas; i++) {
        reservas[i] = nullptr;
    }
}

Huesped::~Huesped()
{
    for (short i = 0; i < reservasCargadas; ++i) {
        if (reservas[i] != nullptr) {
            delete reservas[i];
            reservas[i] = nullptr;
        }
    }
    delete[] reservas;
    reservas = nullptr;
}

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

unsigned short Huesped::getAntiguedadMeses() const
{
    return antiguedadMeses;
}

unsigned short Huesped::getCapacidadReservas() const
{
    return capacidadReservas;
}
unsigned short Huesped::getReservasCargadas() const
{
    return reservasCargadas;
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

void Huesped::setCapacidadReservas(unsigned short _capacidadReservas)
{
    capacidadReservas = _capacidadReservas;
}

void Huesped::setReservas(Reserva **_reservas)
{
    reservas = _reservas;
}

// Otros metodos

void Huesped::eliminarReserva(string codigoReserva) {}

void Huesped::agregarReserva(Reserva *nuevaReserva)
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
            nuevoArreglo[i] = reservas[i];
        }

        for (int i = reservasCargadas; i < nuevaCapacidad; i++) {
            nuevoArreglo[i] = nullptr;
        }
        delete[] reservas;

        reservas = nuevoArreglo;
        capacidadReservas = nuevaCapacidad;
    }
    reservas[reservasCargadas] = nuevaReserva;
    reservasCargadas++;
}
