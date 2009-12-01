#ifndef HIPOTROCOIDE_H
#define HIPOTROCOIDE_H

#include "dibujolineas.h"

class Hipotrocoide
    : public DibujoLineas
{
public:
    Hipotrocoide(Lapiz &l, const PV2f &centro, uint a, uint b, uint c, uint precision);

    QString getNombre() const;

    void dibuja(Estado estado) const;
    QWidget *configWidget();
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
