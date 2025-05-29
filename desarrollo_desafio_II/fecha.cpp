#include "fecha.h"
#include "variablesIteracionesMemoria.h"
#include <iostream>
#include <string>
using namespace std;

Fecha::Fecha(unsigned char _dia, unsigned char _mes, unsigned short _anio)
    : dia(_dia), mes(_mes), anio(_anio)
{
    validacionFecha();
}

//constructor por defecto
Fecha::Fecha() : dia(0), mes(0), anio(0) {}

// Metodos get
unsigned char Fecha::getDia() const
{
    return dia;
}

unsigned char Fecha::getMes() const
{
    return mes;
}

unsigned short Fecha::getAnio() const
{
    return anio;
}

// Metodos set
void Fecha::setDia(unsigned char _dia)
{
    // Validacion ????
    dia = _dia;
}

void Fecha::setMes(unsigned char _mes)
{
    // Validacion ????
    mes = _mes;
}

void Fecha::setAnio(unsigned short _anio)
{
    // Validacion ????
    anio = _anio;
}

// Otros metodos
void Fecha::fechaPalabras()
{
    unsigned char d = dia;
    unsigned char m = mes;
    unsigned short y = anio;

    // Ajustes para Zeller's Congruence:
    // Enero y Febrero son considerados como los meses 13 y 14 del año anterior.
    if (m <= 2) {
        m += 12;
        y -= 1;
    }

    // Algoritmo de Zeller
    unsigned short k = y % 100; // Año del siglo
    unsigned short j = y / 100; // Siglo

    // Formula
    int h = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    // Mapeo del resultado a los nombres de los dias de la semana
    static const string nombresDias[7]
        = {"Sabado", "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};

    static const string nombresMeses[13] = {
        "",
        "Enero",
        "Febrero",
        "Marzo",
        "Abril",
        "Mayo",
        "Junio",
        "Julio",
        "Agosto",
        "Septiembre",
        "Octubre",
        "Noviembre",
        "Diciembre",
    };

    // El resultado 'h' es el indice directo.
    // Si la fecha es valida, h estara en el rango [0, 6].
    cout << "El " << nombresDias[h] << " " << int(getDia()) << " de " << nombresMeses[getMes()]
         << " del " << getAnio() << endl;
}

Fecha Fecha::sumarDias(unsigned int diasASumar)
{
    // Creamos variables temporales para no modificar el objeto original
    unsigned char nuevoDia = dia;
    unsigned char nuevoMes = mes;
    unsigned short nuevoAnio = anio;

    // Arreglo para los dias en cada mes (indice 0 no usado, Febrero 28 por defecto)
    // Usamos static para que se inicialice una sola vez.
    static const unsigned char diasEnMesNoBisiesto[]
        = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (diasASumar > 0) {

        unsigned char diasMaximosMesActual;

        // Determinar dias maximos del mes actual, considerando años bisiestos
        if (nuevoMes == 2 && esBisiesto(nuevoAnio)) {
            diasMaximosMesActual = 29;
        } else {
            diasMaximosMesActual = diasEnMesNoBisiesto[nuevoMes];
        }

        // Calcular cuantos dias quedan en el mes actual
        unsigned int diasRestantesEnMes = diasMaximosMesActual - nuevoDia;

        if (diasASumar <= diasRestantesEnMes) {
            // Si los dias a sumar caben en el mes actual
            nuevoDia += diasASumar;
            diasASumar = 0; // Se sumaron todos los dias
        } else {
            // Si los dias a sumar exceden el mes actual
            diasASumar
                -= (diasRestantesEnMes
                    + 1); // Resta los dias que quedan mas el dia actual (para pasar al 1 del sig. mes)
            nuevoDia = 1; // El dia se convierte en el 1 del siguiente mes

            // Avanzar al siguiente mes
            nuevoMes++;
            if (nuevoMes > 12) {
                nuevoMes = 1; // Volver a enero
                nuevoAnio++;  // Avanzar al siguiente año
            }
        }
    }

    // Retorna un nuevo objeto Fecha con la fecha calculada
    return Fecha(nuevoDia, nuevoMes, nuevoAnio);
}

// Validaciones
bool Fecha::esBisiesto(unsigned short _anio)
{
    if ((_anio % 4 == 0 && _anio % 100 != 0) || (_anio % 400 == 0)) {
        return true;
    } else {
        return false;
    }
}

void Fecha::validacionFecha()
{
    unsigned char diasEnMeses[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (anio < 2025 || anio > 2100) {
        throw invalid_argument("El anio ingresado no es valido (ej. 1900-2100).");
    }

    if (mes == 0 || mes > 12) {
        throw invalid_argument("El mes ingresado no es valido (1-12).");
    }

    if (dia == 0 || dia > 31) {
        throw invalid_argument("El dia ingresado no es valido (1-31).");
    }

    if (mes == 2) { // Febrero
        if (esBisiesto(anio)) {
            if (dia > 29) {
                throw invalid_argument("El dia ingresado es invalido para febrero en anio bisiesto (1-29).");
            }
        } else {
            if (dia > 28) {
                throw invalid_argument("El dia ingresado es invalido para febrero en anio no bisiesto (1-28).");
            }
        }
    } else {
        if (dia > diasEnMeses[mes]) {
            throw invalid_argument("El dia ingresado excede el limite de dias para el mes especificado.");
        }
    }
}

bool Fecha::operator==(const Fecha &_fecha) const
{
    if ((this->dia == _fecha.getDia()) && (this->mes == _fecha.getMes())
        && (this->anio == _fecha.getAnio()))
        return true;
    else
        return false;
}

bool Fecha::operator>=(const Fecha &_fecha) const
{
    if (this->anio > _fecha.getAnio()) {
        return true;
    } else if (this->anio == _fecha.getAnio()) {
        if (this->mes > _fecha.getMes()) {
            return true;
        } else if (this->mes == _fecha.getMes()) {
            if (this->dia >= _fecha.getDia()) {
                return true;
            }
        }
    }
    return false;
}

bool Fecha::operator<=(const Fecha &_fecha) const
{
    if (this->anio < _fecha.getAnio()) {
        return true;
    } else if (this->anio == _fecha.getAnio()) {
        if (this->mes < _fecha.getMes()) {
            return true;
        } else if (this->mes == _fecha.getMes()) {
            if (this->dia <= _fecha.getDia()) {
                return true;
            }
        }
    }
    return false;
}

bool Fecha::operator<(const Fecha &_fecha) const
{
    if (this->anio < _fecha.getAnio()) {
        return true;
    } else if (this->anio == _fecha.getAnio()) {
        if (this->mes < _fecha.getMes()) {
            return true;
        } else if (this->mes == _fecha.getMes()) {
            if (this->dia < _fecha.getDia()) {
                return true;
            }
        }
    }
    return false;
}

string Fecha::fechaString()
{
    Globales::contadorTo_String+=3;
    return to_string(dia) + "-" + to_string(mes) + "-" + to_string(anio);
}

ostream &operator<<(ostream &os, const Fecha &fecha)
{
    os << fecha.getDia() << "-" << fecha.getMes() << "-" << fecha.getAnio();
    return os;
}
