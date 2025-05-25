#ifndef ANFITRION_H
#define ANFITRION_H

#include "alojamiento.h"
#include <string>
using namespace std;

class Anfitrion
{
private:
    const string documento;
    float puntuacion;
    unsigned short antiguedadMeses;
    Alojamiento **alojamientos;

public:
    Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses);

    // Metodos get
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getAntiguedadMeses() const;
    Alojamiento **getAlojamimentos() const;

    // Metodos set
    void setDocumento(const string &_documento);
    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setAlojamientos(Alojamiento **_alojamientos);

    // Otros metodos
    void consultarReservas() const;
    void anularReserva();
};

#endif // ANFITRION_H
