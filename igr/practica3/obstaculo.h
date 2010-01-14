#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <GL/gl.h>
#include "pv2f.h"

class Pelota;
class Lapiz;

class Obstaculo
{
public:
    Obstaculo(const PV2f &pos);

    virtual void dibuja(Lapiz &lapiz) const = 0;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n) = 0;

protected:
    PV2f m_pos;
};

#endif
