#ifndef DIBUJOLINEAS_H
#define DIBUJOLINEAS_H

#include <GL/gl.h>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include "segmento.h"
#include "lapiz.h"

class QWidget;

class DibujoLineas
    : public QObject
{
    Q_OBJECT

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

    void cohenSutherland(const PV2f &tl, const PV2f &br);

    virtual void dibuja(Estado estado = Ninguno) const = 0;
    virtual QWidget *configWidget() = 0;

public Q_SLOTS:
    virtual void invalidar();

Q_SIGNALS:
    void invalidada();

protected:
    Lapiz          &m_l;
    QList<Segmento> m_listaSegmentos;
    GLdouble        m_radianes;
    PV2f            m_centro;
};

#endif
