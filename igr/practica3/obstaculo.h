#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <GL/gl.h>
#include "pv2f.h"

class Pelota;
class Lapiz;

class Obstaculo
{
public:
    enum Orientacion {
        Norte = 0,
        Este,
        Sur,
        Oeste
    };

    Obstaculo(const PV2f &pos);

    PV2f getPos() const;

    void dibujaLinea(const PV2f &pos, const PV2f &sentido) const;

    virtual void dibuja(Lapiz &lapiz) const = 0;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const = 0;
    virtual void dibujaNormales(Lapiz &lapiz) const = 0;
    virtual bool colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz) = 0;

protected:
    PV2f m_pos;
};

#endif
