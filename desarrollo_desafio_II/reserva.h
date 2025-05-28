#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
class Huesped;
class Alojamiento;
using namespace std;

class Reserva
{
private:
    string codigoReserva;
    string metodoPago;
    string inquietudes;
    Fecha fechaEntrada;
    Fecha fechaPago;
    Fecha fechaFin;
    unsigned short estadiaNoches;
    unsigned int montoPago;
    Huesped *huespedAsociado;
    Alojamiento *alojamientoAsociado;

public:
    Reserva(const string &_codigoReserva,
            const string &_metodoPago,
            const string &_inquietudes,
            const Fecha &_fechaEntrada,
            const Fecha &_fechaPago,
            Fecha &_fechaFin,
            unsigned short _estadiaNoches,
            unsigned int _montoPago,
            Huesped *_huespedAsociado,
            Alojamiento *_alojamientoAsociado);

    // Metodos get
    string getCodigoReserva() const;
    string getMetodoPago() const;
    Alojamiento* getAlojamiento();
    string getCodigoAlojamientoAsociado() const;
    Huesped* getHuesped() const;
    string getDocumentoHuespedAsociado() const;
    string getInquietudes() const;
    Fecha getFechaEntrada() const;
    Fecha getFechaPago() const;
    Fecha getFechaFin() const;
    unsigned short getEstadiaNoches() const;
    unsigned int getMontoPago() const;

    // Metodos set
    void setCodigoReserva(const string &_codigoReserva);
    void setMetodoPago(const string &_metodoPago);
    void setInquietudes(const string &_inquietudes);
    void setFechaEntrada(const Fecha &_fechaEntrada);
    void setFechaPago(const Fecha &_fechaPago);
    void setEstadiaNoches(unsigned short _estadiaNoches);
    void setMontoPago(unsigned int _montoPago);

    // Otros metodos
    string reservaString();
    void mostrarReserva();
};

#endif // RESERVA_H
