#ifndef POLIGONOCONVEXO_H
#define POLIGONOCONVEXO_H

#include "obstaculo.h"

class PoligonoConvexo
    : public Obstaculo
{
public:
    PoligonoConvexo(const PV2f &pos, GLdouble lado, size_t nLados);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales(Lapiz &lapiz) const;
    virtual bool colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz);

private:
    GLdouble m_lado;
    size_t   m_nLados;
};

#endif
