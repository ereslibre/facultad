#include "dibujomanual.h"

DibujoManual::DibujoManual(Lapiz &l)
    : DibujoLineas(l)
{
}

void DibujoManual::dibuja() const
{
    glBegin(GL_LINES);
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        glVertex2d(segmento.getA().getX(), segmento.getA().getY());
        glVertex2d(segmento.getB().getX(), segmento.getB().getY());
        ++it;
    }
    glEnd();
}
