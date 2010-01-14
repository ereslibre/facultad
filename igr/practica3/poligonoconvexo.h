#ifndef POLIGONOCONVEXO_H
#define POLIGONOCONVEXO_H

#include "obstaculo.h"

class PoligonoConvexo
    : public Obstaculo
{
public:
    virtual void dibuja() const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);
};

#endif