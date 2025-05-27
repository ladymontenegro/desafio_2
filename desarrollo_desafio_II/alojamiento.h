#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "reserva.h"
#include <string>
using namespace std;

class Alojamiento
{
private:
    string nombre;
    string amenidades;
    const string codigo;
    const string municipio;
    const string departamento;
    const string tipo;
    const string direccion;
    const string documentoAnfitrion;
    unsigned int precioNoche;
    unsigned short capacidadReservas;
    unsigned short reservasCargadas;
    Reserva **reservas;

public:
    Alojamiento(const string &_nombre,
                const string &_amenidades,
                const string &_codigo,
                const string &_municipio,
                const string &_departamento,
                const string &_tipo,
                const string &_direccion,
                const string &_documentoAnfitrion,
                unsigned int _precioNoche);

    Alojamiento(const Alojamiento &otro);

    ~Alojamiento();

    // Metodos get
    string getNombre() const;
    string getAmenidades() const;
    const string getCodigo();
    const string getMunicipio();
    const string getDepartamento();
    const string getTipo();
    const string getDireccion();
    const string getDocumentoAnfitrion();
    unsigned int getPrecioNoche() const;
    unsigned short getCapacidadReservas() const;
    unsigned short getReservasCargadas() const;
    Reserva **getReservas() const;

    // Metodos set
    void setNombre(const string &_nombre);
    void setAmenidades(const string &_amenidades);
    void setPrecioNoches(const unsigned int _precioNoche);
    void setReservas(Reserva **_reservas);

    // Otros metodos
    bool alojamientoDisponible(Fecha fechaInicio, unsigned int cantidadDeNoches) const;
    void eliminarReserva(string codigoReserva);
    void agregarReserva(Reserva *nuevaReserva);
    void mostrarAlojamiento();
};

#endif // ALOJAMIENTO_H
