#include "obstaculo.h"

#include <math.h>

Obstaculo::Obstaculo(const PV2f &pos)
    : m_pos(pos)
{
}

PV2f Obstaculo::getPos() const
{
    return m_pos;
}

void Obstaculo::dibujaLinea(const PV2f &pos, GLdouble orientacion, GLdouble tamano) const
{
    const GLdouble baseX = pos.getX() + tamano * cos(orientacion);
    const GLdouble baseY = pos.getY() + tamano * sin(orientacion);
    glBegin(GL_LINES);
    glVertex2d(pos.getX(), pos.getY());
    glVertex2d(baseX, baseY);
    glEnd();
}
