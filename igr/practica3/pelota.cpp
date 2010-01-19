#include "pelota.h"
#include "general.h"
#include "lapiz.h"

#include <math.h>

#define ROZAMIENTO 0.95

Pelota::Pelota(const PV2f &pos, Tipo tipo)
    : Obstaculo(pos)
    , m_sentido(1, 0, PV2f::Vector)
    , m_fuerza(0)
    , m_radio(RADIO_PELOTA)
    , m_angulo(0)
    , m_tipo(tipo)
{
}

Pelota::~Pelota()
{
}

PV2f Pelota::getCentro() const
{
    return m_pos;
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
    m_sentido = PV2f(cos(m_angulo), sin(m_angulo), PV2f::Vector);
}

void Pelota::decrementaAngulo()
{
    m_angulo -= 0.1;
    m_sentido = PV2f(cos(m_angulo), sin(m_angulo), PV2f::Vector);
}

void Pelota::avanza()
{
    m_pos = (m_sentido * m_fuerza) + m_pos;
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
    if (m_tipo == NoProtagonista) {
        const GLdouble DEG2RAD = M_PI / 180.0;
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++) {
            float degInRad = i * DEG2RAD;
            glVertex2f(m_pos.getX() + cos(degInRad) * RADIO_PELOTA * 2.0, m_pos.getY() + sin(degInRad) * RADIO_PELOTA * 2.0);
        }
        glEnd();
    }
}

void Pelota::dibujaNormales(Lapiz &lapiz) const
{
    if (m_tipo == Protagonista) {
        dibujaLinea(m_pos, m_angulo, RADIO_PELOTA + m_fuerza);
    }
}

bool Pelota::colisiona(Pelota *pelota, GLdouble &thit, PV2f &n)
{
    if (m_tipo == Protagonista) {
        return false;
    }
    return false;
}