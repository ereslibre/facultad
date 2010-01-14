#include "lapiz.h"

#include <math.h>

Lapiz::Lapiz()
{
    m_e.dir = 0;
}

void Lapiz::salvaEstado()
{
    m_pilaEstados.push(m_e);
}

void Lapiz::recuperaEstado()
{
    m_e = m_pilaEstados.pop();
}

void Lapiz::girar(GLdouble radianes)
{
    m_e.dir += radianes;
}

void Lapiz::avanzar(GLfloat distancia, Comportamiento comportamiento)
{
    if (comportamiento == DejarRastro) {
        glBegin(GL_LINE_STRIP);
        glVertex2d(m_e.pos.getX(), m_e.pos.getY());
    }
    const GLdouble incX = distancia * cos(m_e.dir);
    const GLdouble incY = distancia * sin(m_e.dir);
    m_e.pos.rX() += incX;
    m_e.pos.rY() += incY;
    if (comportamiento == DejarRastro) {
        glVertex2d(m_e.pos.getX(), m_e.pos.getY());
        glEnd();
    }
}

void Lapiz::setDir(GLdouble dir)
{
    m_e.dir = dir;
}

void Lapiz::setPos(const PV2f &pos)
{
    m_e.pos = pos;
}

GLdouble Lapiz::getDir() const
{
    return m_e.dir;
}

const PV2f &Lapiz::getPos() const
{
    return m_e.pos;
}
