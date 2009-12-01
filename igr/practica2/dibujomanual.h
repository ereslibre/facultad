#ifndef DIBUJOMANUAL_H
#define DIBUJOMANUAL_H

#include "dibujolineas.h"

class DibujoManual
    : public DibujoLineas
{
public:
    DibujoManual(Lapiz &l);

    void dibuja(Estado estado) const;
    QWidget *configWidget() const;
};

#endif
