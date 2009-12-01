#include "hipotrocoide.h"

#include <math.h>

#include <boost/math/common_factor.hpp>

Hipotrocoide::Hipotrocoide(Lapiz &l, const PV2f &centro, uint a, uint b, uint c, uint precision)
    : DibujoLineas(l, centro)
    , m_a(a)
    , m_b(b)
    , m_c(c)
    , m_precision(precision)
{
    const int numVueltas = (m_b / boost::math::gcd(m_a, m_b)) * m_precision;
    const GLdouble stepSize = 2.0 * M_PI / m_precision;
    GLdouble currStepSize = 0;
    PV2f pa((m_a - m_b) * cos(currStepSize) + m_c * cos(currStepSize * (m_a - m_b) / m_b) + m_centro.getX(),
            (m_a - m_b) * sin(currStepSize) - m_c * sin(currStepSize * (m_a - m_b) / m_b) + m_centro.getY());
    for (int i = 0; i <= numVueltas; ++i) {
        currStepSize += stepSize;
        const PV2f pb((m_a - m_b) * cos(currStepSize) + m_c * cos(currStepSize * (m_a - m_b) / m_b) + m_centro.getX(),
                      (m_a - m_b) * sin(currStepSize) - m_c * sin(currStepSize * (m_a - m_b) / m_b) + m_centro.getY());
        m_listaSegmentos << Segmento(pa, pb);
        pa = pb;
    }
}

void Hipotrocoide::dibuja(Estado estado) const
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
        glVertex2d(segmento.getA().getX(), segmento.getA().getY());
        glVertex2d(segmento.getB().getX(), segmento.getB().getY());
        ++it;
    }
    glEnd();
}

QWidget *Hipotrocoide::configWidget() const
{
    return 0;
}
