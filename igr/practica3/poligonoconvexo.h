#ifndef POLIGONOCONVEXO_H
#define POLIGONOCONVEXO_H

#include "obstaculo.h"

class PoligonoConvexo
    : public Obstaculo
{
public:
    PoligonoConvexo(const PV2f &pos);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);
};

#endif
