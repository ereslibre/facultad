#ifndef POLIESPIRAL_H
#define POLIESPIRAL_H

#include "dibujolineas.h"

class PoliEspiral
    : public DibujoLineas
{
public:
    PoliEspiral(Lapiz &l, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado);

    void dibuja() const;

private:
    uint    m_nPasos;
    GLfloat m_incLado;
    GLfloat m_incDir;
    GLfloat m_lado;
};

#endif
