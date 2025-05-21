#include "fecha.h"

using namespace std;

Fecha::Fecha(unsigned int &_dia, unsigned int &_mes, unsigned int &_anio)
    : dia(_dia)
    , mes(_mes)
    , anio(_anio)
{
    //excepcion
}

// Metodos get
unsigned int Fecha::getDia() const
{
    return dia;
}

unsigned int Fecha::getMes() const
{
    return mes;
}

unsigned int Fecha::getAnio() const
{
    return anio;
}

// Metodos set
void Fecha::setDia(unsigned int _dia)
{
    // Validacion ????
    dia = _dia;
}

void Fecha::setMes(unsigned int _mes)
{
    // Validacion ????
    mes = _mes;
}

void Fecha::setAnio(unsigned int _anio)
{
    // Validacion ????
    anio = _anio;
}

// Otros metodos
void Fecha::fechaPalabras(unsigned int _dia, unsigned int _mes, unsigned int _anio)
{
    // La lógica real podría convertir el mes a nombre, etc.
}

void Fecha::sumarDias(unsigned int _dias)
{
    // dia += _dias;
    // while (dia > diasEnMes(mes, anio)) {
    //    dia -= diasEnMes(mes, anio);
    //    mes++;
    //    if (mes > 12) {
    //        mes = 1;
    //        anio++;
    //    }
    // }
}
