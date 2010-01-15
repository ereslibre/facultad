#include "pelota.h"
#include "general.h"
#include "lapiz.h"

#include <math.h>

Pelota::Pelota(const PV2f &pos)
    : Obstaculo(pos)
    , m_centro(0, 0)
    , m_sentido(PV2f::Vector)
    , m_fuerza(0)
    , m_radio(RADIO_PELOTA)
{
}

Pelota::~Pelota()
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

void Pelota::dibuja(Lapiz &lapiz) const
{
//     glBegin(GL_LINE_STRIP);
//     for(size_t i = 0; i <= 360; i++) {
//         glVertex2d(sin(i * M_PI / 180.0) * pos, cos(i * M_PI / 180.0) * 5);
//     }
//     glEnd();
}

void Pelota::dibujaEnvoltorio(Lapiz &lapiz) const
{
}

void Pelota::dibujaNormales(Lapiz &lapiz) const
{
    dibujaNormal(m_pos);
}

bool Pelota::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}