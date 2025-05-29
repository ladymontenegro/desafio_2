#include "huesped.h"
#include "variablesIteracionesMemoria.h"
#include <iostream>

Huesped::Huesped(const string &_nombre,
                 const string &_documento,
                 float _puntuacion,
                 unsigned short _antiguedadMeses)
    : nombre(_nombre)
    , documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , capacidadReservas(20)
    , reservasCargadas(0)
{
    reservas = new Reserva *[capacidadReservas]();
}

Huesped::Huesped(const Huesped &otro)
    : nombre(otro.nombre)
    , documento(otro.documento)
    , puntuacion(otro.puntuacion)
    , antiguedadMeses(otro.antiguedadMeses)
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

Huesped::~Huesped()
{
    for (short i = 0; i < reservasCargadas; ++i) {
        Globales::contadorIteraciones++;
        if (reservas[i] != nullptr) {
            reservas[i] = nullptr;
        }
    }
    delete[] reservas;
    reservas = nullptr;
}

size_t Huesped::calcularMemoria() const {
    size_t total = sizeof(*this);

    // Solo suma el ARREGLO DE PUNTEROS (todos los slots)
    if (reservas) {
        total += static_cast<size_t>(capacidadReservas) * sizeof(Reserva*);
    }

    // ¡NO suma objetos Reserva! Son referencias, no ownership
    return total;
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

void Huesped::eliminarReserva(string _codigoReserva)
{
    for (unsigned short i = 0; i < reservasCargadas; i++) {
        Globales::contadorIteraciones++;
        if (reservas[i] != nullptr) {
            if (reservas[i]->getCodigoReserva() == _codigoReserva) {
                reservas[i] = nullptr;
                if (i != reservasCargadas - 1) {
                    for (unsigned short j = i; j < reservasCargadas - 1; j++) {
                        Globales::contadorIteraciones++;
                        reservas[j] = reservas[j + 1];
                    }
                    reservas[reservasCargadas - 1] = nullptr;
                }
            }
        }
    }
    reservasCargadas--;
}

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

void Huesped::mostrarReservas()
{
    cout << "\n--- Reservas Vigentes ---";
    for (unsigned short i = 0; i < reservasCargadas; i++) {
        Globales::contadorIteraciones++;
        cout << "-------------------------------------";
        reservas[i]->mostrarReserva();
    }
}
