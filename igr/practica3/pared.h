#ifndef PARED_H
#define PARED_H

#include "obstaculo.h"

class Pared
    : public Obstaculo
{
public:
    enum Tipo {
        EsPared = 0,
        NoEsPared
    };

    Pared(const PV2f &pos, GLdouble anchura, GLdouble altura);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales(Lapiz &lapiz) const;
    virtual bool colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz);

private:
    GLdouble m_anchura;
    GLdouble m_altura;
};

#endif