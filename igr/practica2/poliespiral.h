#ifndef POLIESPIRAL_H
#define POLIESPIRAL_H

#include "dibujolineas.h"

class PoliEspiral
    : public DibujoLineas
{
public:
    PoliEspiral(Lapiz &l, const PV2f &centro, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado);

    QString getNombre() const;

    DibujoLineas *clonar() const;
    QWidget *configWidget();
    void salva(QTextStream &stream) const;
    void invalidar();

private:
    void calculaSegmentos();

    uint    m_nPasos;
    GLfloat m_incLado;
    GLfloat m_incDir;
    GLfloat m_lado;
    class ConfigWidget;
    ConfigWidget *m_configWidget;
};

#endif
