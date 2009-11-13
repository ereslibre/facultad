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
