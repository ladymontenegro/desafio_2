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
    Reserva **reservas;

public:
    Huesped(const string &_nombre,
            const string &_documento,
            float _puntuacion,
            unsigned short _antioguedadMeses);

    // Metodos get

    const string getNombre();
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getaAntiguedadMeses() const;
    Reserva **getReservas() const;

    // Metodos set

    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setReservas(Reserva **_reservas);

    // Otros metodos
};

#endif // HUESPED_H
