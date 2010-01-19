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

    enum Normal {
        Izquierda = 0,
        Derecha
    };

    PV2f(Tipo tipo = Punto);
    PV2f(const PV2f &pv2f);
    PV2f(GLdouble x, GLdouble y, Tipo tipo = Punto);

    GLdouble getX() const;
    GLdouble getY() const;

    GLdouble &rX();
    GLdouble &rY();

    void setX(GLdouble x);
    void setY(GLdouble y);

    Tipo getTipo() const;

    GLdouble dot(const PV2f &pv2f) const;
    GLdouble mod() const;

    PV2f normal(Normal normal = Izquierda) const;
    void normalizar();

    void rotar(const PV2f &centro, GLdouble angulo);

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
    GLdouble m_x;
    GLdouble m_y;
    Tipo     m_tipo;
};

#endif
