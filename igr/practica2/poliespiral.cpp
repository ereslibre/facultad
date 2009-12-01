#include "poliespiral.h"

PoliEspiral::PoliEspiral(Lapiz &l, const PV2f &centro, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado)
    : DibujoLineas(l, centro)
    , m_nPasos(nPasos)
    , m_incLado(incLado)
    , m_incDir(incDir)
    , m_lado(lado)
{
    l.salvaEstado();
    l.setPos(centro);
    PV2f a = centro;
    for (uint i = 0; i < m_nPasos; ++i) {
        m_l.avanzar(lado, Lapiz::NoDejarRastro);
        m_listaSegmentos << Segmento(a, m_l.getPos());
        a = m_l.getPos();
        lado += m_incLado;
        m_l.girar(m_incDir);
    }
    l.recuperaEstado();
}

QString PoliEspiral::getNombre() const
{
    return "Poli-espiral";
}

void PoliEspiral::dibuja(Estado estado) const
{
    if (estado & Seleccionado) {
        glColor3f(1.0, 1.0, 0);
    } else {
        glColor3f(1.0, 1.0, 1.0);
    }
    GLfloat lado = m_lado;
    for (uint i = 0; i < m_nPasos; ++i) {
        m_l.avanzar(lado);
        lado += m_incLado;
        m_l.girar(m_incDir);
    }
}

QWidget *PoliEspiral::configWidget() const
{
    return 0;
}

