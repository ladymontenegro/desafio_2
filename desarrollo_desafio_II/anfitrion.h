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
    Alojamiento **alojamientos; //destructor

public:
    Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses);

    // Metodos get
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getAntiguedadMeses() const;

    // Metodos set
    void setDocumento(const string &_documento);
    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setAlojamientos(Alojamiento **_alojamientos, unsigned int numeroAlojamientos);

    // Otros metodos
    void consultarReservas() const; // Declaración, implementación en .cpp si es compleja
    void anularReserva();
};

#endif // ANFITRION_H
