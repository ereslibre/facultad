#include "pelota.h"
#include "general.h"
#include "lapiz.h"

#include <math.h>

#define ROZAMIENTO 0.95

Pelota::Pelota(const PV2f &pos)
    : Obstaculo(pos)
    , m_centro(0, 0)
    , m_sentido(PV2f::Vector)
    , m_fuerza(0)
    , m_radio(RADIO_PELOTA)
    , m_angulo(0)
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

void Pelota::incrementaFuerza()
{
    m_fuerza += 0.5;
    if (m_fuerza == 50.0) {
        m_fuerza = 0;
    }
}

void Pelota::incrementaAngulo()
{
    m_angulo += 0.1;
}

void Pelota::decrementaAngulo()
{
    m_angulo -= 0.1;
}

void Pelota::avanza()
{
    m_fuerza *= ROZAMIENTO;
}

void Pelota::reflexion(const PV2f &n)
{
}

void Pelota::dibuja(Lapiz &lapiz) const
{
    const GLdouble DEG2RAD = M_PI / 180.0;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * DEG2RAD;
        glVertex2f(m_pos.getX() + cos(degInRad) * RADIO_PELOTA, m_pos.getY() + sin(degInRad) * RADIO_PELOTA);
    }
    glEnd();
}

void Pelota::dibujaEnvoltorio(Lapiz &lapiz) const
{
}

void Pelota::dibujaNormales(Lapiz &lapiz) const
{
    dibujaNormal(m_pos, m_angulo, RADIO_PELOTA + m_fuerza);
}

bool Pelota::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}