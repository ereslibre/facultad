#include "pared.h"
#include "lapiz.h"
#include "general.h"

#include <math.h>

Pared::Pared(const PV2f &pos, GLdouble anchura, GLdouble altura)
    : Obstaculo(pos)
    , m_anchura(anchura)
    , m_altura(altura)
{
}

void Pared::dibuja(Lapiz &lapiz) const
{
    glBegin(GL_LINE_STRIP);
    glVertex2d(m_pos.getX(), m_pos.getY());
    glVertex2d(m_pos.getX(), m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY());
    glVertex2d(m_pos.getX(), m_pos.getY());
    glEnd();
}

void Pared::dibujaEnvoltorio(Lapiz &lapiz) const
{
    glBegin(GL_LINE_STRIP);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glEnd();
}

void Pared::dibujaNormales(Lapiz &lapiz) const
{
    glBegin(GL_LINES);
    {
    }
    {
    }
    {
    }
    {
    }
    glEnd();
}

bool Pared::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}