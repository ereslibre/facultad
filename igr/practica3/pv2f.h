#ifndef PV2F_H
#define PV2F_H

#include <GL/gl.h>

class PV2f
{
public:
    enum Tipo {
        Punto = 0,
        Vector
    };

    PV2f(Tipo tipo = Punto);
    PV2f(const PV2f &pv2f, Tipo tipo = Punto);
    PV2f(GLfloat x, GLfloat y, Tipo tipo = Punto);

    GLfloat getX() const;
    GLfloat getY() const;

    GLfloat &rX();
    GLfloat &rY();

    void setX(GLfloat x);
    void setY(GLfloat y);

    Tipo getTipo() const;

    GLdouble dot(const PV2f &pv2f) const;
    GLdouble mod() const;

    void normalizar();
    void rotar(const PV2f &centro, GLfloat angulo);

    PV2f operator*(const PV2f &pv2f) const;
    PV2f &operator*=(const PV2f &pv2f);
    PV2f operator*(GLdouble x) const;
    PV2f &operator*=(GLdouble x);

    PV2f operator+(const PV2f &pv2f) const;
    PV2f &operator+=(const PV2f &pv2f);

    PV2f operator-(const PV2f &pv2f) const;
    PV2f &operator-=(const PV2f &pv2f);

    bool operator==(const PV2f &rhs) const;
    bool operator!=(const PV2f &rhs) const;

private:
    GLfloat m_x;
    GLfloat m_y;
    Tipo    m_tipo;
};

#endif
