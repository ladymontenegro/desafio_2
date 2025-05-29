#include "anfitrion.h"
#include "variablesIteracionesMemoria.h"
#include <iostream>

//Constructor de la clase
Anfitrion::Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses)
    : documento(_documento)
    , puntuacion(_puntuacion)
    , antiguedadMeses(_antiguedadMeses)
    , capacidadDeAlojamientos(10)
    , alojamientosCargados(0)
{
    alojamientos = new Alojamiento *[capacidadDeAlojamientos]();
}

//Constructor copia

Anfitrion::Anfitrion(const Anfitrion &otro)
    : documento(otro.documento)
    , puntuacion(otro.puntuacion)
    , antiguedadMeses(otro.antiguedadMeses)
    , capacidadDeAlojamientos(otro.capacidadDeAlojamientos)
    , alojamientosCargados(otro.alojamientosCargados)
{
    alojamientos = new Alojamiento *[capacidadDeAlojamientos]();

    for (unsigned short i = 0; i < alojamientosCargados; ++i) {
        Globales::contadorIteraciones++;
        if (otro.alojamientos[i] != nullptr) {
            alojamientos[i] = new Alojamiento(*(otro.alojamientos[i]));
        } else {
            alojamientos[i] = nullptr;
        }
    }
}

//Destructor de la clase
Anfitrion::~Anfitrion()
{
    for (unsigned short i = 0; i < alojamientosCargados; ++i) {
        Globales::contadorIteraciones++;
        if (alojamientos[i] != nullptr) {
            delete alojamientos[i];
            alojamientos[i] = nullptr;
        }
    }
    delete[] alojamientos;
    alojamientos = nullptr;
}

size_t Anfitrion::calcularMemoria() const {
    size_t total = sizeof(*this); //memoria estatica

    // memoria del arreglo de punteros
    if (alojamientos) {
        total += static_cast<size_t>(capacidadDeAlojamientos) * sizeof(Alojamiento*);

        //memoria de cada alojamiento (solo no nulos)
        for (int i = 0; i < alojamientosCargados; ++i) {
            if (alojamientos[i]) {
                total += alojamientos[i]->calcularMemoria();
            }
        }
    }
    return total;
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

unsigned short Anfitrion::getCapacidadDeAlojamientos() const
{
    return capacidadDeAlojamientos;
}

Alojamiento *Anfitrion::getAlojamiento(unsigned short indice) const
{
    if (indice >= 0 && indice < capacidadDeAlojamientos) {
        return alojamientos[indice];
    } else {
        return nullptr;
    }
}

Alojamiento **Anfitrion::getAlojamientos() const
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
void Anfitrion::consultarReservas(string _codigoAlojamiento) const
{
    for (unsigned short i = 0; i < alojamientosCargados; i++) {
        Globales::contadorIteraciones++;
        if (alojamientos[i]->getCodigo() == _codigoAlojamiento) {
            Reserva **punteroArregloReservas = alojamientos[i]->getReservas();
            unsigned short reservasActualesAlojamiento = alojamientos[i]->getReservasCargadas();
            if (reservasActualesAlojamiento == 0) {
                cout << "\nNo hay reservas cargadas para el alojamiento con codigo "
                     << _codigoAlojamiento << endl;
                return;
            }
            cout << "\n--- Reservas para Alojamiento con codigo " << _codigoAlojamiento << " ---"
                 << endl;
            for (unsigned short j = 0; j < reservasActualesAlojamiento; j++) {
                Globales::contadorIteraciones++;
                (*punteroArregloReservas[j]).mostrarReserva();
            }
            break;
        }
    }
}

bool Anfitrion::agregarAlojamiento(Alojamiento *_alojamiento)
{
    if (alojamientosCargados >= capacidadDeAlojamientos) {
        int nuevaCapacidad = 0;
        if (capacidadDeAlojamientos == 0) {
            nuevaCapacidad = 1;
        } else {
            nuevaCapacidad = capacidadDeAlojamientos * 2;
        }

        Alojamiento **nuevoArreglo = new Alojamiento *[nuevaCapacidad];

        for (int i = 0; i < alojamientosCargados; i++) {
            Globales::contadorIteraciones++;
            nuevoArreglo[i] = alojamientos[i];
        }

        for (int i = alojamientosCargados; i < nuevaCapacidad; i++) {
            Globales::contadorIteraciones++;
            nuevoArreglo[i] = nullptr;
        }
        delete[] alojamientos;

        alojamientos = nuevoArreglo;
        capacidadDeAlojamientos = nuevaCapacidad;
    }
    alojamientos[alojamientosCargados] = _alojamiento;
    alojamientosCargados++;
    return true;
}
