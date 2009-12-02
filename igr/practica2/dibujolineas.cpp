#include "dibujolineas.h"

DibujoLineas::DibujoLineas(Lapiz &l, const PV2f &centro)
    : m_l(l)
    , m_radianes(0)
    , m_centro(centro)
{
}

void DibujoLineas::setCentro(const PV2f &centro)
{
    m_centro = centro;
    invalidar();
}

const PV2f &DibujoLineas::getCentro() const
{
    return m_centro;
}

void DibujoLineas::anadeSegmento(const Segmento &segmento)
{
    m_listaSegmentos << segmento;
    invalidar();
}

void DibujoLineas::girar(GLdouble radianes)
{
    m_radianes += radianes;
    invalidar();
}

bool DibujoLineas::clickSobreFigura(const PV2f &posClick) const
{
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        if ((qAbs(posClick.getX() - segmento.getA().getX()) < 3.0 &&
             qAbs(posClick.getY() - segmento.getA().getY()) < 3.0) ||
            (qAbs(posClick.getX() - segmento.getB().getX()) < 3.0 &&
             qAbs(posClick.getY() - segmento.getB().getY()) < 3.0)) {
            return true;
        }
        ++it;
    }
    return false;
}

void DibujoLineas::cohenSutherland(const PV2f &tl, const PV2f &br)
{
    QList<Segmento>::Iterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        Segmento &segmento = *it;
        segmento.cohenSutherland(tl, br);
        ++it;
    }
}

void DibujoLineas::dibuja(Estado estado) const
{
    if (estado & Seleccionado) {
        glColor3f(1.0, 1.0, 0);
    } else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glBegin(GL_LINES);
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        if (segmento.esValido()) {
            glVertex2d(segmento.getA().getX(), segmento.getA().getY());
            glVertex2d(segmento.getB().getX(), segmento.getB().getY());
        }
        ++it;
    }
    glEnd();
}

void DibujoLineas::invalidar()
{
    emit invalidada();
}

#include "dibujolineas.moc"
