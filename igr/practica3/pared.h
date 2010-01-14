#ifndef PARED_H
#define PARED_H

#include "obstaculo.h"

class Pared
    : public Obstaculo
{
public:
    virtual void dibuja() const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);
};

#endif