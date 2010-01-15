#include "pared.h"
#include "lapiz.h"

#include <math.h>

Pared::Pared(const PV2f &pos, GLdouble anchura, GLdouble altura)
    : Obstaculo(pos)
    , m_anchura(anchura)
    , m_altura(altura)
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

bool Pared::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}