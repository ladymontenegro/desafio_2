TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        funciones_auxiliares_carga_datos.cpp \
        funciones_carga_datos.cpp \
        main.cpp\
        alojamiento.cpp\
        anfitrion.cpp\
        fecha.cpp\
        huesped.cpp\
        reserva.cpp

HEADERS += \
    header_funciones.h\
    alojamiento.h\
    anfitrion.h\
    fecha.h\
    huesped.h\
    reserva.h
