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

    Pared(const PV2f &pos, GLdouble anchura, GLdouble altura, Tipo tipo = NoEsPared);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales(Lapiz &lapiz) const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);

private:
    GLdouble m_anchura;
    GLdouble m_altura;
    Tipo     m_tipo;
};

#endif