#ifndef FECHA_H
#define FECHA_H

class Fecha
{
private:
    unsigned int dia;
    unsigned int mes;
    unsigned int anio;

public:
    Fecha(unsigned int _dia, unsigned int _mes, unsigned int _anio);

    // Metodos get
    unsigned int getDia() const;
    unsigned int getMes() const;
    unsigned int getAnio() const;

    // Metodos set
    void setDia(unsigned int _dia);
    void setMes(unsigned int _mes);
    void setAnio(unsigned int _anio);

    // Otros metodos
    void fechaPalabras(unsigned int _dia, unsigned int _mes, unsigned int _anio);
    void sumarDias(unsigned int _dias);
};

#endif // FECHA_H
