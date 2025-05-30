#include "Reserva.h"
#include "alojamiento.h"
#include "fecha.h"
#include "huesped.h"
#include "variablesIteracionesMemoria.h"

#include <iostream>
#include <string>
using namespace std;

Reserva::Reserva(const string &_codigoReserva,
                 const string &_metodoPago,
                 const string &_inquietudes,
                 const Fecha &_fechaEntrada,
                 const Fecha &_fechaPago,
                 unsigned short _estadiaNoches,
                 unsigned int _montoPago,
                 Huesped *_huespedAsociado,
                 Alojamiento *_alojamientoAsociado)

    : codigoReserva(_codigoReserva)
    , metodoPago(_metodoPago)
    , inquietudes(_inquietudes)
    , fechaEntrada(_fechaEntrada)
    , fechaPago(_fechaPago)
    , fechaFin(fechaEntrada.sumarDias(_estadiaNoches))
    , estadiaNoches(_estadiaNoches)
    , montoPago(_montoPago)
    , huespedAsociado(_huespedAsociado)
    , alojamientoAsociado(_alojamientoAsociado)
{}

size_t Reserva::calcularMemoria() const {
    size_t total = sizeof(*this); // Memoria estática

    // Solo memoria de atributos dinámicos propios (si los tiene)
    // Ej: si tiene un char* para descripción:
    // if (descripcion) total += strlen(descripcion) + 1;

    return total;
}

// Metodos get
string Reserva::getCodigoReserva() const
{
    return codigoReserva;
}

string Reserva::getMetodoPago() const
{
    return metodoPago;
}

string Reserva::getInquietudes() const
{
    return inquietudes;
}

Fecha Reserva::getFechaEntrada() const
{
    return fechaEntrada;
}

Fecha Reserva::getFechaPago() const
{
    return fechaPago;
}

Fecha Reserva::getFechaFin() const
{
    return fechaFin;
}

unsigned short Reserva::getEstadiaNoches() const
{
    return estadiaNoches;
}

unsigned int Reserva::getMontoPago() const
{
    return montoPago;
}

Huesped* Reserva::getHuesped() const
{
    return huespedAsociado;
}

Alojamiento* Reserva::getAlojamiento() const
{
    return alojamientoAsociado;
}

// Metodos set
void Reserva::setCodigoReserva(const string &_codigoReserva)
{
    codigoReserva = _codigoReserva;
}

void Reserva::setMetodoPago(const string &_metodoPago)
{
    metodoPago = _metodoPago;
}

void Reserva::setInquietudes(const string &_inquietudes)
{
    inquietudes = _inquietudes;
}

void Reserva::setFechaEntrada(const Fecha &_fechaEntrada)
{
    fechaEntrada = _fechaEntrada;
}

void Reserva::setFechaPago(const Fecha &_fechaPago)
{
    fechaPago = _fechaPago;
}

void Reserva::setEstadiaNoches(unsigned short _estadiaNoches)
{
    estadiaNoches = _estadiaNoches;
}

void Reserva::setMontoPago(unsigned int _montoPago)
{
    montoPago = _montoPago;
}

// Otros metodos

string Reserva::reservaString()
{
    Globales::contadorTo_String+=2;
    return fechaEntrada.fechaString() + "," + codigoReserva + "," + huespedAsociado->getDocumento()
           + "," + to_string(estadiaNoches) + "," + metodoPago + "," + fechaPago.fechaString() + "," + to_string(montoPago) + ","
           + inquietudes;
}

void Reserva::mostrarReserva()
{
    cout << "\nCodigo: " << codigoReserva << endl;
    cout << "Fecha Entrada: " << fechaEntrada.fechaString() << endl;
    cout << "Estadia: " << estadiaNoches << " noches" << endl;
    cout << "Fecha de Pago: " << fechaPago.fechaString() << endl;
    cout << "Metodo Pago: " << metodoPago << endl;
    cout << "Monto del Pago: " << montoPago << endl;
    cout << "Inquietudes: " << inquietudes << endl;
}
