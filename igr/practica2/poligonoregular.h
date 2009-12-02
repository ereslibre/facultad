#ifndef POLIGONOREGULAR_H
#define POLIGONOREGULAR_H

#include "dibujolineas.h"

class PoligonoRegular
    : public DibujoLineas
{
public:
    PoligonoRegular(Lapiz &l, const PV2f &centro, GLfloat lado, int nLados);

    QString getNombre() const;

    DibujoLineas *clonar() const;
    QWidget *configWidget();
    void salva(QTextStream &stream) const;
    void invalidar();

private:
    void calculaSegmentos();

    GLfloat m_lado;
    uint    m_nLados;
    class ConfigWidget;
    ConfigWidget *m_configWidget;
};

#endif
