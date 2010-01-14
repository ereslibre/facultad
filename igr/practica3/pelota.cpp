#include "pelota.h"

Pelota::Pelota()
    : m_centro(0, 0)
    , m_sentido(PV2f::Vector)
    , m_fuerza(0)
    , m_radio(10)
{
}

PV2f Pelota::getCentro() const
{
    return m_centro;
}

GLdouble Pelota::getFuerza() const
{
    return m_fuerza;
}

GLdouble Pelota::getRadio() const
{
    return m_radio;
}

void Pelota::avanza(GLdouble pasos)
{
}

void Pelota::reflexion(const PV2f &n)
{
}