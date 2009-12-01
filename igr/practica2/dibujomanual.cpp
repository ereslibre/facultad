#include "dibujomanual.h"

DibujoManual::DibujoManual(Lapiz &l)
    : DibujoLineas(l)
{
}

QString DibujoManual::getNombre() const
{
    return "Dibujo Manual";
}

void DibujoManual::dibuja(Estado estado) const
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

QWidget *DibujoManual::configWidget()
{
    return 0;
}

void DibujoManual::invalidar()
{
}
