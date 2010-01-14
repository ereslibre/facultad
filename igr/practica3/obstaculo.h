#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <GL/gl.h>

class Pelota;
class PV2f;

class Obstaculo
{
public:
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n) = 0;
};

#endif
