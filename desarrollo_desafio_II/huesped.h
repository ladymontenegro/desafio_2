#ifndef HUESPED_H
#define HUESPED_H

#include "reserva.h"
#include <string>
using namespace std;

class Huesped
{
private:
    const string nombre;
    const string documento;
    float puntuacion;
    unsigned short antiguedadMeses;
    unsigned short capacidadReservas;
    unsigned short reservasCargadas;
    Reserva **reservas;

public:
    Huesped(const string &_nombre,
            const string &_documento,
            float _puntuacion,
            unsigned short _antioguedadMeses);

    Huesped(const Huesped &otro);

    ~Huesped();

    // Metodos get

    const string getNombre();
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getAntiguedadMeses() const;
    unsigned short getCapacidadReservas() const;
    unsigned short getReservasCargadas() const;
    Reserva **getReservas() const;

    // Metodos set

    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setCapacidadReservas(unsigned short _capacidadReservas);
    void setReservas(Reserva **_reservas);

    // Otros metodos

    void eliminarReserva(string codigoReserva);
    void agregarReserva(Reserva *nuevaReserva);
};

#endif // HUESPED_H
