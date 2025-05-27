TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp\
        menuHuesped.cpp\
        menuAnfitrion.cpp\
        funciones_carga_archivos.cpp\
        funciones_auxiliares_carga_datos.cpp\
        funciones_carga_datos.cpp\
        alojamiento.cpp\
        anfitrion.cpp\
        fecha.cpp\
        huesped.cpp\
        reserva.cpp

HEADERS += \
        funcionesPrincipales.h\
        header_funciones.h\
        alojamiento.h\
        anfitrion.h\
        fecha.h\
        huesped.h\
        reserva.h

