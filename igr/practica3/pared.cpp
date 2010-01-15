#include "pared.h"
#include "lapiz.h"
#include "general.h"

#include <math.h>

Pared::Pared(const PV2f &pos, GLdouble anchura, GLdouble altura, Tipo tipo)
    : Obstaculo(pos)
    , m_anchura(anchura)
    , m_altura(altura)
    , m_tipo(tipo)
{
}

void Pared::dibuja(Lapiz &lapiz) const
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(m_pos.getX(), m_pos.getY());
    glVertex2d(m_pos.getX(), m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY());
    glEnd();
}

void Pared::dibujaEnvoltorio(Lapiz &lapiz) const
{
    if (m_tipo == NoEsTablero) {
        glBegin(GL_LINE_STRIP);
        glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
        glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
        glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
        glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
        glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
        glEnd();
    }
}

void Pared::dibujaNormales(Lapiz &lapiz) const
{
    {
        PV2f pos(m_pos);
        pos.rX() += m_anchura / 2.0;
        dibujaNormal(pos, -M_PI / 2);
    }
    {
        PV2f pos(m_pos);
        pos.rX() += m_anchura;
        pos.rY() += m_altura / 2.0;
        dibujaNormal(pos);
    }
    {
        PV2f pos(m_pos);
        pos.rY() += m_altura / 2.0;
        dibujaNormal(pos, M_PI);
    }
    {
        PV2f pos(m_pos);
        pos.rX() += m_anchura / 2.0;
        pos.rY() += m_altura;
        dibujaNormal(pos, M_PI / 2.0);
    }
}

bool Pared::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}