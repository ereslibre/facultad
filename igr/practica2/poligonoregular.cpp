#include "poligonoregular.h"

#include <math.h>

PoligonoRegular::PoligonoRegular(Lapiz &l, const PV2f &centro, GLfloat lado, int nLados)
    : DibujoLineas(l, centro)
    , m_lado(lado)
    , m_nLados(nLados)
{
    l.salvaEstado();
    l.setPos(centro);
    const GLfloat alpha = 2.0 * M_PI / (GLfloat) m_nLados;
    const GLfloat beta = (M_PI - alpha) / 2;
    const GLfloat radio = (m_lado / 2.0) / sin(alpha / 2.0);
    const GLfloat gamma = M_PI - beta;
    m_l.avanzar(radio, Lapiz::NoDejarRastro);
    PV2f a = m_l.getPos();
    m_l.girar(gamma);
    for (int i = 0; i < m_nLados; ++i) {
        m_l.avanzar(m_lado, Lapiz::NoDejarRastro);
        m_listaSegmentos << Segmento(a, m_l.getPos());
        a = m_l.getPos();
        m_l.girar(alpha);
    }
    l.recuperaEstado();
}

QString PoligonoRegular::getNombre() const
{
    return "Poligono Regular";
}

void PoligonoRegular::dibuja(Estado estado) const
{
    if (estado & Seleccionado) {
        glColor3f(1.0, 1.0, 0);
    } else {
        glColor3f(1.0, 1.0, 1.0);
    }
    const GLfloat alpha = 2.0 * M_PI / (GLfloat) m_nLados;
    const GLfloat beta = (M_PI - alpha) / 2;
    const GLfloat radio = (m_lado / 2.0) / sin(alpha / 2.0);
    const GLfloat gamma = M_PI - beta;
    m_l.avanzar(radio, Lapiz::NoDejarRastro);
    m_l.girar(gamma);
    for (int i = 0; i < m_nLados; ++i) {
        m_l.avanzar(m_lado);
        m_l.girar(alpha);
    }
}

QWidget *PoligonoRegular::configWidget() const
{
    return 0;
}
