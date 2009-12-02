#include "dibujomanual.h"

DibujoManual::DibujoManual(Lapiz &l)
    : DibujoLineas(l)
{
}

QString DibujoManual::getNombre() const
{
    return "Dibujo Manual";
}

QWidget *DibujoManual::configWidget()
{
    return 0;
}

void DibujoManual::salva(QTextStream &stream) const
{
}

void DibujoManual::invalidar()
{
}
