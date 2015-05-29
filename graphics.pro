TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    camera.cpp

HEADERS += \
    camera.h \
    force.h \
    vector3.h \
    plane.h \
    particle.h \
    ParticleSystem.h \
    line.h \
    texturedparticle.h

LIBS+=-lGL -lGLU -lglut -lSOIL -lpthread
