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
    unsigned short capacidadDeAlojamientos;
    unsigned short alojamientosCargados;
    Alojamiento **alojamientos;

public:
    Anfitrion(const string &_documento, float _puntuacion, unsigned short _antiguedadMeses);

    ~Anfitrion();

    // Metodos get
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getAntiguedadMeses() const;
    unsigned short getcapacidadDeAlojamientos() const;
    unsigned short getAlojamientosCargados() const;
    Alojamiento *getAlojamiento(short indice) const;
    Alojamiento **getAlojamimentos() const;

    // Metodos set
    void setDocumento(const string &_documento);
    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setAlojamientos(Alojamiento **_alojamientos);

    // Otros metodos
    void consultarReservas() const;
    void anularReserva();
    bool agregarAlojamiento(Alojamiento *_alojamiento);
    void consultarAlojamiento(unsigned short indice);
};

#endif // ANFITRION_H
