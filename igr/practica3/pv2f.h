#ifndef PV2F_H
#define PV2F_H

#include <GL/gl.h>

class PV2f
{
public:
    PV2f();
    PV2f(const PV2f &pv2f);
    PV2f(GLfloat x, GLfloat y);

    GLfloat getX() const;
    GLfloat getY() const;

    GLfloat &rX();
    GLfloat &rY();

    void setX(GLfloat x);
    void setY(GLfloat y);

    void rotar(const PV2f &centro, GLfloat angulo);

    bool operator==(const PV2f &rhs) const;
    bool operator!=(const PV2f &rhs) const;

private:
    GLfloat m_x;
    GLfloat m_y;
};

#endif
