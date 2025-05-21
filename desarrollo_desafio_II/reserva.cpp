#include "Reserva.h"
#include "Fecha.h"
#include <iostream>
#include <string>
using namespace std;

Reserva::Reserva(const string &_codigoReserva,
                 const string &_metodoPago,
                 const string &_codigoAlojamiento,
                 const string &_documentoHuesped,
                 const string &_inquietudes,
                 const Fecha &_fechaEntrada,
                 const Fecha &_fechaPago,
                 unsigned short _estadiaNoches,
                 unsigned int _montoPago)

    : codigoReserva(_codigoReserva)
    , metodoPago(_metodoPago)
    , codigoAlojamiento(_codigoAlojamiento)
    , documentoHuesped(_documentoHuesped)
    , inquietudes(_inquietudes)
    , fechaEntrada(_fechaEntrada)
    , fechaPago(_fechaPago)
    , estadiaNoches(_estadiaNoches)
    , montoPago(_montoPago)

{}

// Metodos get
string Reserva::getCodigoReserva() const
{
    return codigoReserva;
}

string Reserva::getMetodoPago() const
{
    return metodoPago;
}

string Reserva::getCodigoAlojamiento() const
{
    return codigoAlojamiento;
}

string Reserva::getDocumentoHuesped() const
{
    return documentoHuesped;
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

unsigned short Reserva::getEstadiaNoches() const
{
    return estadiaNoches;
}

unsigned int Reserva::getMontoPago() const
{
    return montoPago;
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

void Reserva::setCodigoAlojamiento(const string &_codigoAlojamiento)
{
    codigoAlojamiento = _codigoAlojamiento;
}

void Reserva::setDocumentoHuesped(const string &_documentoHuesped)
{
    documentoHuesped = _documentoHuesped;
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
void Reserva::setCodigoReserva(const string &codigoReservaConsulta, const string &nuevoCodigoReserva)
{
    // Aquí la lógica asume que 'codigoReservaConsulta' es el código actual
    // del objeto para saber si es el que se debe modificar.
    // Esto es común si se busca un objeto Reserva por su código y luego se modifica.
    if (this->codigoReserva == codigoReservaConsulta) {
        this->codigoReserva = nuevoCodigoReserva;
        cout << "Codigo de reserva " << codigoReservaConsulta << " actualizado a "
             << nuevoCodigoReserva << endl;
    } else {
        cout << "No se encontró la reserva con el código: " << codigoReservaConsulta
             << " para actualizar." << endl;
    }
}

void Reserva::setMetodoPago(const string &codigoReservaConsulta, const string &nuevoMetodoPago)
{
    if (this->codigoReserva == codigoReservaConsulta) {
        this->metodoPago = nuevoMetodoPago;
        cout << "Metodo de pago de reserva " << codigoReservaConsulta << " actualizado a "
             << nuevoMetodoPago << endl;
    } else {
        cout << "No se encontró la reserva con el código: " << codigoReservaConsulta
             << " para actualizar." << endl;
    }
}

void Reserva::setCodigoAlojamiento(const string &codigoReservaConsulta,
                                   const string &nuevoCodigoAlojamiento)
{
    if (this->codigoReserva == codigoReservaConsulta) {
        this->codigoAlojamiento = nuevoCodigoAlojamiento;
        cout << "Codigo de alojamiento de reserva " << codigoReservaConsulta << " actualizado a "
             << nuevoCodigoAlojamiento << endl;
    } else {
        cout << "No se encontró la reserva con el código: " << codigoReservaConsulta
             << " para actualizar." << endl;
    }
}

string Reserva::getDocumentoAnfitrion(const string &codigoReservaConsulta) const
{
    cout << "Buscando documento del anfitrión para la reserva: " << codigoReservaConsulta << endl;
    // Esta función probablemente necesite acceder a una lista de alojamientos o anfitriones
    // para encontrar el anfitrión asociado al codigoAlojamiento de esta reserva.
    // La implementación aquí es un placeholder.
    if (this->codigoReserva == codigoReservaConsulta) {
        // En un sistema real, aquí buscarías el Anfitrion a través del codigoAlojamiento
        // y devolverías su documento.
        cout << "  (Lógica para buscar anfitrión por alojamiento NO implementada aquí)" << endl;
        return "DOCUMENTO_ANFITRION_EJEMPLO"; // Placeholder
    }
    return ""; // Si la reserva no coincide o no se encuentra el anfitrión
}
