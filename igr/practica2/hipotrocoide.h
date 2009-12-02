#ifndef HIPOTROCOIDE_H
#define HIPOTROCOIDE_H

#include "dibujolineas.h"

class Hipotrocoide
    : public DibujoLineas
{
public:
    Hipotrocoide(Lapiz &l, const PV2f &centro, uint a, uint b, uint c, uint precision, uint rotacion = 0);

    QString getNombre() const;

    DibujoLineas *clonar() const;
    QWidget *configWidget();
    void salva(QTextStream &stream) const;
    void invalidar();

private:
    void calculaSegmentos();

    uint          m_a;
    uint          m_b;
    uint          m_c;
    uint          m_precision;
    uint          m_rotacion;
    class ConfigWidget;
    ConfigWidget *m_configWidget;
};

#endif
