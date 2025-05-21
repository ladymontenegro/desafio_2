#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;

class Reserva
{
private:
    string codigoReserva;
    string metodoPago;
    string codigoAlojamiento;
    string documentoHuesped;
    string inquietudes;
    Fecha fechaEntrada;
    Fecha fechaPago;
    unsigned short estadiaNoches;
    unsigned int montoPago;

public:
    Reserva(const string &_codigoReserva,
            const string &_metodoPago,
            const string &_codigoAlojamiento,
            const string &_documentoHuesped,
            const string &_inquietudes,
            const Fecha &_fechaEntrada,
            const Fecha &_fechaPago,
            unsigned short _estadiaNoches,
            unsigned int _montoPago);

    // Metodos get
    string getCodigoReserva() const;
    string getMetodoPago() const;
    string getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    string getInquietudes() const;
    Fecha getFechaEntrada() const;
    Fecha getFechaPago() const;
    unsigned short getEstadiaNoches() const;
    unsigned int getMontoPago() const;

    // Metodos set
    void setCodigoReserva(const string &_codigoReserva);
    void setMetodoPago(const string &_metodoPago);
    void setCodigoAlojamiento(const string &_codigoAlojamiento);
    void setDocumentoHuesped(const string &_docuemntoHuesped);
    void setInquietudes(const string &_inquietudes);
    void setFechaEntrada(const Fecha &_fechaInicio);
    void setFechaPago(const Fecha &_fechaPago);
    void setEstadiaNoches(unsigned short _estadiaNoches);
    void setMontoPago(unsigned int _montoPago);

    // Otros metodos
    void setCodigoReserva(const string &codigoReserva,
                          const string &nuevoCodigoReserva); // Sobrecarga
    void setMetodoPago(const string &codigoReserva,
                       const string &nuevoMetodoPago); // Sobrecarga
    void setCodigoAlojamiento(const string &codigoReserva,
                              const string &nuevoCodigoAlojamiento); // Sobrecarga
    string getDocumentoAnfitrion(const string &codigoReserva) const;
};

#endif // RESERVA_H
