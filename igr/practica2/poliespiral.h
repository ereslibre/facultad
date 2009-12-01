#ifndef POLIESPIRAL_H
#define POLIESPIRAL_H

#include "dibujolineas.h"

class PoliEspiral
    : public DibujoLineas
{
public:
    PoliEspiral(Lapiz &l, const PV2f &centro, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado);

    QString getNombre() const;

    void dibuja(Estado estado) const;
    QWidget *configWidget();
    void invalidar();

private:
    uint    m_nPasos;
    GLfloat m_incLado;
    GLfloat m_incDir;
    GLfloat m_lado;
};

#endif
