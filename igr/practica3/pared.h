#ifndef PARED_H
#define PARED_H

#include "obstaculo.h"

class Pared
    : public Obstaculo
{
public:
    Pared(const PV2f &pos, GLdouble anchura, GLdouble altura);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales() const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);

private:
    GLdouble m_anchura;
    GLdouble m_altura;
};

#endif