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

    void dibujaNormal(const PV2f &pos, GLdouble orientacion = 0) const;

    virtual void dibuja(Lapiz &lapiz) const = 0;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const = 0;
    virtual void dibujaNormales() const = 0;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n) = 0;

protected:
    PV2f m_pos;
};

#endif
