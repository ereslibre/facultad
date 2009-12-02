#ifndef DIBUJOMANUAL_H
#define DIBUJOMANUAL_H

#include "dibujolineas.h"

class DibujoManual
    : public DibujoLineas
{
public:
    DibujoManual(Lapiz &l);

    QString getNombre() const;

    DibujoLineas *clonar() const;
    QWidget *configWidget();
    void salva(QTextStream &stream) const;
    void invalidar();
};

#endif
