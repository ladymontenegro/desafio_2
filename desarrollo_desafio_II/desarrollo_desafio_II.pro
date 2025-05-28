TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    funcionesAuxiliares.cpp \
    funcionesCargaArchivos.cpp \
    funcionesCargaDatos.cpp \
    main.cpp\
    menuHuesped.cpp\
    menuAnfitrion.cpp\
    alojamiento.cpp\
    anfitrion.cpp\
    fecha.cpp\
    huesped.cpp\
    reserva.cpp \
    variablesIteracionesMemoria.cpp

HEADERS += \
    alojamiento.h\
    anfitrion.h\
    fecha.h\
    funcionesAuxiliares.h \
    huesped.h\
    reserva.h \
    variablesIteracionesMemoria.h

