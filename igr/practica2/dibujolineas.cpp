#include "dibujolineas.h"

DibujoLineas::DibujoLineas(Lapiz &l, const PV2f &centro)
    : m_l(l)
    , m_radianes(0)
    , m_centro(centro)
{
}

const PV2f &DibujoLineas::getCentro() const
{
    return m_centro;
}

void DibujoLineas::anadeSegmento(const Segmento &segmento)
{
    m_listaSegmentos << segmento;
}

void DibujoLineas::girar(GLdouble radianes)
{
    m_radianes += radianes;
}

bool DibujoLineas::clickSobreFigura(const PV2f &posClick) const
{
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        glVertex2d(segmento.getA().getX(), segmento.getA().getY());
        glVertex2d(segmento.getB().getX(), segmento.getB().getY());
        if (qAbs(posClick.getX() - segmento.getA().getX()) < 1.0 ||
            qAbs(posClick.getX() - segmento.getB().getX()) < 1.0 ||
            qAbs(posClick.getY() - segmento.getA().getY()) < 1.0 ||
            qAbs(posClick.getY() - segmento.getB().getY()) < 1.0) {
            return true;
        }
        ++it;
    }
    return false;
}

