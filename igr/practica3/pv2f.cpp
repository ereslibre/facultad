#include "pv2f.h"

#include <QtCore/QDebug>
#include <math.h>

PV2f::PV2f(Tipo tipo)
    : m_x(0)
    , m_y(0)
    , m_tipo(tipo)
{
}

PV2f::PV2f(const PV2f &pv2f)
    : m_x(pv2f.m_x)
    , m_y(pv2f.m_y)
    , m_tipo(pv2f.m_tipo)
{
}

PV2f::PV2f(GLdouble x, GLdouble y, Tipo tipo)
    : m_x(x)
    , m_y(y)
    , m_tipo(tipo)
{
}

GLdouble PV2f::getX() const
{
    return m_x;
}

GLdouble PV2f::getY() const
{
    return m_y;
}

GLdouble &PV2f::rX()
{
    return m_x;
}

GLdouble &PV2f::rY()
{
    return m_y;
}

void PV2f::setX(GLdouble x)
{
    m_x = x;
}

void PV2f::setY(GLdouble y)
{
    m_y = y;
}

PV2f::Tipo PV2f::getTipo() const
{
    return m_tipo;
}

GLdouble PV2f::dot(const PV2f &pv2f) const
{
    if (m_tipo != Vector) {
        qDebug() << "!!! cuenta con PV2f ilegal en dot";
        return 0;
    }
    return m_x * pv2f.m_x + m_y * pv2f.m_y;
}

GLdouble PV2f::mod() const
{
    if (m_tipo != Vector) {
        qDebug() << "!!! cuenta con PV2f ilegal en mod";
        return 0;
    }
    return sqrt(m_x * m_x + m_y * m_y);
}

PV2f PV2f::normal(Normal normal) const
{
    PV2f res;
    if (m_tipo != Vector) {
        qDebug() << "!!! cuenta con PV2f ilegal en normal";
        return res;
    }
    res.m_tipo = Vector;
    if (normal == Izquierda) {
        res.m_x = -m_y;
        res.m_y = m_x;
    } else {
        res.m_x = m_y;
        res.m_y = -m_x;
    }
    return res;
}

void PV2f::normalizar()
{
    if (m_tipo != Vector) {
        qDebug() << "!!! cuenta con PV2f ilegal en normalizar";
        return;
    }
    const GLdouble c = 1 / sqrt(m_x * m_x + m_y * m_y);
    m_x *= c;
    m_y *= c;
}

void PV2f::rotar(const PV2f &centro, GLdouble angulo)
{
    if (m_tipo != Punto) {
        qDebug() << "!!! cuenta con PV2f ilegal en rotar";
        return;
    }
    const GLdouble cx = centro.getX();
    const GLdouble cy = centro.getY();
    const GLdouble dx = (1.0 - cos(angulo)) * cx + sin(angulo) * cy;
    const GLdouble dy = -sin(angulo) * cx + (1.0 - cos(angulo)) * cy;
    const GLdouble x = m_x * cos(angulo) - m_y * sin(angulo) + dx;
    const GLdouble y = m_x * sin(angulo) + m_y * cos(angulo) + dy;
    m_x = x;
    m_y = y;
}

PV2f PV2f::operator*(const PV2f &pv2f) const
{
    qDebug() << "!!! cuenta con PV2f ilegal en operator*(PV2f)";
    return *this;
}

PV2f &PV2f::operator*=(const PV2f &pv2f)
{
    qDebug() << "!!! cuenta con PV2f ilegal en operator*=(PV2f)";
    return *this;
}

PV2f PV2f::operator*(GLdouble x) const
{
    PV2f res;
    if (m_tipo == Vector) {
        res.m_tipo = Vector;
        res.m_x = m_x * x;
        res.m_y = m_y * x;
    } else {
        qDebug() << "!!! cuenta con PV2f ilegal en operator*(GLdouble)";
    }
    return res;
}

PV2f &PV2f::operator*=(GLdouble x)
{
    if (m_tipo != Vector) {
        qDebug() << "!!! cuenta con PV2f ilegal en operator*=(GLdouble)";
        return *this;
    }
    m_x *= x;
    m_y *= x;
    return *this;
}

PV2f PV2f::operator+(const PV2f &pv2f) const
{
    PV2f res;
    if (m_tipo == Punto && pv2f.m_tipo == Vector || m_tipo == Vector && pv2f.m_tipo == Punto) {
        res.m_tipo = Punto;
    } else if (m_tipo == Vector && pv2f.m_tipo == Vector) {
        res.m_tipo = Vector;
    } else {
        qDebug() << "!!! cuenta con PV2f ilegal en operator+(PV2f)";
        return res;
    }
    res.m_x = m_x + pv2f.m_x;
    res.m_y = m_y + pv2f.m_y;
    return res;
}

PV2f &PV2f::operator+=(const PV2f &pv2f)
{
    if (m_tipo == Punto && pv2f.m_tipo == Vector || m_tipo == Vector && pv2f.m_tipo == Punto) {
        m_tipo = Punto;
    } else if (m_tipo == Vector && pv2f.m_tipo == Vector) {
        m_tipo = Vector;
    } else {
        qDebug() << "!!! cuenta con PV2f ilegal en operator+=(PV2f)";
        return *this;
    }
    m_x += pv2f.m_x;
    m_y += pv2f.m_y;
    return *this;
}

PV2f PV2f::operator-(const PV2f &pv2f) const
{
    PV2f res;
    if (m_tipo == Punto && pv2f.m_tipo == Punto || m_tipo == Vector && pv2f.m_tipo == Vector) {
        res.m_tipo = Vector;
    } else {
        qDebug() << "!!! cuenta con PV2f ilegal en operator-(PV2f)";
        return res;
    }
    res.m_x = m_x - pv2f.m_x;
    res.m_y = m_y - pv2f.m_y;
    return res;
}

PV2f &PV2f::operator-=(const PV2f &pv2f)
{
    if (m_tipo == Punto && pv2f.m_tipo == Punto || m_tipo == Vector && pv2f.m_tipo == Vector) {
        m_tipo = Vector;
    } else {
        qDebug() << "!!! cuenta con PV2f ilegal en operator-=(PV2f)";
        return *this;
    }
    m_x -= pv2f.m_x;
    m_y -= pv2f.m_y;
    return *this;
}

bool PV2f::operator==(const PV2f &rhs) const
{
    return m_x == rhs.m_x && m_y == rhs.m_y && m_tipo == rhs.m_tipo;
}

bool PV2f::operator!=(const PV2f &rhs) const
{
    return m_x != rhs.m_x || m_y != rhs.m_y || m_tipo != rhs.m_tipo;
}
