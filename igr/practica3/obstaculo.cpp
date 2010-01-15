#include "obstaculo.h"

#include <math.h>

Obstaculo::Obstaculo(const PV2f &pos)
    : m_pos(pos)
{
}

#define LONGITUD_VECTOR 50.0

void Obstaculo::dibujaNormal(const PV2f &pos, GLdouble orientacion) const
{
    const GLdouble baseX = pos.getX() + LONGITUD_VECTOR * cos(orientacion);
    const GLdouble baseY = pos.getY() + LONGITUD_VECTOR * sin(orientacion);
    glBegin(GL_LINES);
    glVertex2d(pos.getX(), pos.getY());
    glVertex2d(baseX, baseY);
    glEnd();
}
