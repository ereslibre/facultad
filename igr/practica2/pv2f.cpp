#include "pv2f.h"

PV2f::PV2f()
    : m_x(0)
    , m_y(0)
{
}

PV2f::PV2f(const PV2f &pv2f)
    : m_x(pv2f.m_x)
    , m_y(pv2f.m_y)
{
}

PV2f::PV2f(GLfloat x, GLfloat y)
    : m_x(x)
    , m_y(y)
{
}

GLfloat PV2f::getX() const
{
    return m_x;
}

GLfloat PV2f::getY() const
{
    return m_y;
}

GLfloat &PV2f::rX()
{
    return m_x;
}

GLfloat &PV2f::rY()
{
    return m_y;
}

void PV2f::setX(GLfloat x)
{
    m_x = x;
}

void PV2f::setY(GLfloat y)
{
    m_y = y;
}
