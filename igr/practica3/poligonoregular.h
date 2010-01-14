#ifndef POLIGONOREGULAR_H
#define POLIGONOREGULAR_H

#include "dibujolineas.h"

class PoligonoRegular
    : public DibujoLineas
{
public:
    PoligonoRegular(Lapiz &l, const PV2f &centro, GLfloat lado, int nLados);

private:
    GLfloat m_lado;
    uint    m_nLados;
};

#endif
