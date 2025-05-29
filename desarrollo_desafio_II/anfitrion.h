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

    Anfitrion(const Anfitrion &otro);

    ~Anfitrion();

    size_t calcularMemoria() const;

    // Metodos get
    const string getDocumento();
    float getPuntuacion() const;
    unsigned short getAntiguedadMeses() const;
    unsigned short getCapacidadDeAlojamientos() const;
    unsigned short getAlojamientosCargados() const;
    Alojamiento *getAlojamiento(unsigned short indice) const;
    Alojamiento **getAlojamientos() const;

    // Metodos set
    void setPuntuacion(float _puntuacion);
    void setAntiguedadMeses(unsigned short _antiguedadMeses);
    void setAlojamientos(Alojamiento **_alojamientos);

    // Otros metodos
    void consultarReservas(string _codigoAlojamiento) const;
    bool agregarAlojamiento(Alojamiento *_alojamiento);
};

#endif // ANFITRION_H
