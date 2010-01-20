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

void Obstaculo::dibujaLinea(const PV2f &pos, const PV2f &sentido) const
{
    glBegin(GL_LINES);
    glVertex2d(pos.getX(), pos.getY());
    glVertex2d(sentido.getX() + pos.getX(), sentido.getY() + pos.getY());
    glEnd();
}
