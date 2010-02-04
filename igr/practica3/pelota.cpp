#include "pelota.h"
#include "general.h"
#include "lapiz.h"

#include <math.h>

#define ROZAMIENTO 0.95

Pelota::Pelota(const PV2f &pos, GLdouble radio, Tipo tipo)
    : Obstaculo(pos)
    , m_sentido(1, 0, PV2f::Vector)
    , m_fuerza(0)
    , m_radio(radio)
    , m_tipo(tipo)
{
}

Pelota::~Pelota()
{
}

PV2f Pelota::getSentido() const
{
    return m_sentido;
}

void Pelota::setFuerza(GLdouble fuerza)
{
    m_fuerza = fuerza;
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
    if (m_fuerza >= 50.0) {
        m_fuerza = 0;
    }
}

void Pelota::incrementaAngulo()
{
    m_sentido = PV2f(m_sentido.getX() * cos(0.1) - m_sentido.getY() * sin(0.1),
                     m_sentido.getX() * sin(0.1) + m_sentido.getY() * cos(0.1), PV2f::Vector);
}

void Pelota::decrementaAngulo()
{
    m_sentido = PV2f(m_sentido.getX() * cos(-0.1) - m_sentido.getY() * sin(-0.1),
                     m_sentido.getX() * sin(-0.1) + m_sentido.getY() * cos(-0.1), PV2f::Vector);
}

void Pelota::avanza(GLdouble paso)
{
    m_pos = (m_sentido * (paso == -1.0 ? m_fuerza : paso)) + m_pos;
    m_fuerza *= ROZAMIENTO;
}

void Pelota::reflexion(const PV2f &n_)
{
    PV2f n(n_);
    n.normalizar();
    m_sentido = m_sentido - (n * (n.dot(m_sentido) * 2.0));
}

void Pelota::dibuja(Lapiz &lapiz) const
{
    const GLdouble DEG2RAD = M_PI / 180.0;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * DEG2RAD;
        glVertex2f(m_pos.getX() + cos(degInRad) * m_radio, m_pos.getY() + sin(degInRad) * m_radio);
    }
    glEnd();
}

void Pelota::dibujaEnvoltorio(Lapiz &lapiz) const
{
}

void Pelota::dibujaNormales(Lapiz &lapiz) const
{
    if (m_tipo == Protagonista) {
        dibujaLinea(m_pos, m_sentido * (RADIO_PELOTA + m_fuerza));
    }
}

bool Pelota::colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz)
{
    if (m_tipo == Protagonista) {
        return false;
    }
    const PV2f distancia = pelota->getPos() - m_pos;
    if (distancia.mod() < pelota->getRadio() + (pelota->getSentido() * pelota->getFuerza()).mod() + m_radio) {
        thit = (pelota->getPos() - m_pos).mod() - pelota->getRadio() - (pelota->getSentido() * pelota->getFuerza()).mod() - m_radio;
        PV2f res = pelota->getPos() - m_pos;
        res.normalizar();
        n = res;
        return true;
    }
    return false;
}