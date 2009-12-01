#ifndef DIBUJOLINEAS_H
#define DIBUJOLINEAS_H

#include <GL/gl.h>
#include <QtCore/QList>
#include <QtCore/QString>
#include "segmento.h"
#include "lapiz.h"

class QWidget;

class DibujoLineas
{
public:
    enum Estado {
        Ninguno = 0,
        Seleccionado = 1
    };

    DibujoLineas(Lapiz &l, const PV2f &centro = PV2f());

    virtual QString getNombre() const = 0;

    const PV2f &getCentro() const;

    void anadeSegmento(const Segmento &segmento);
    void limpiaDibujo();

    void girar(GLdouble radianes);

    bool clickSobreFigura(const PV2f &posClick) const;

    virtual void dibuja(Estado estado = Ninguno) const = 0;
    virtual QWidget *configWidget() const = 0;

protected:
    Lapiz          &m_l;
    QList<Segmento> m_listaSegmentos;
    GLdouble        m_radianes;
    PV2f            m_centro;
};

#endif
