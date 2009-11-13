#ifndef DIBUJOLINEAS_H
#define DIBUJOLINEAS_H

#include <GL/gl.h>
#include <QtCore/QList>
#include "segmento.h"
#include "lapiz.h"

class DibujoLineas
{
public:
    DibujoLineas(Lapiz &l, const PV2f &centro = PV2f());

    const PV2f &getCentro() const;

    void anadeSegmento(const Segmento &segmento);
    void limpiaDibujo();

    void girar(GLdouble radianes);

    virtual void dibuja() const = 0;

protected:
    Lapiz          &m_l;
    QList<Segmento> m_listaSegmentos;
    GLdouble        m_radianes;
    PV2f            m_centro;
};

#endif
