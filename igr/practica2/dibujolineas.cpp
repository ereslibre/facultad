#include "dibujolineas.h"

DibujoLineas::DibujoLineas(Lapiz &l)
    : m_l(l)
    , m_radianes(0)
{
}

void DibujoLineas::anadeSegmento(const Segmento &segmento)
{
    m_listaSegmentos << segmento;
}

void DibujoLineas::girar(GLdouble radianes)
{
    m_radianes += radianes;
}
