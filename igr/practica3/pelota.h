#ifndef PELOTA_H
#define PELOTA_H

#include "pv2f.h"

class Pelota
{
public:
    Pelota();

    PV2f getCentro() const;
    GLdouble getFuerza() const;
    GLdouble getRadio() const;

    void avanza(GLdouble pasos);
    void reflexion(const PV2f &n);

private:
    PV2f     m_centro;
    PV2f     m_sentido;
    GLdouble m_fuerza;
    GLdouble m_radio;
};

#endif
