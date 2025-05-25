#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

class Fecha
{
private:
    unsigned char dia;
    unsigned char mes;
    unsigned short anio;

public:
    Fecha(unsigned char _dia, unsigned char _mes, unsigned short _anio);

    // Metodos get
    unsigned char getDia() const;
    unsigned char getMes() const;
    unsigned short getAnio() const;

    // Metodos set
    void setDia(unsigned char _dia);
    void setMes(unsigned char _mes);
    void setAnio(unsigned short _anio);

    // Otros metodos
    void fechaPalabras();
    Fecha sumarDias(unsigned int diasASumar);

    // Validaciones
    bool esBisiesto(unsigned short _anio);
    bool validacionFecha();

    // Sobrecarga de operadores

    bool operator==(const Fecha &_fecha) const;
};

#endif // FECHA_H
