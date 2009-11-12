#include "poliespiral.h"

PoliEspiral::PoliEspiral(Lapiz &l, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado)
    : DibujoLineas(l)
    , m_nPasos(nPasos)
    , m_incLado(incLado)
    , m_incDir(incDir)
    , m_lado(lado)
{
}

void PoliEspiral::dibuja() const
{
    GLfloat lado = m_lado;
    for (uint i = 0; i < m_nPasos; ++i) {
        m_l.avanzar(m_lado);
        lado += m_incLado;
        m_l.girar(m_incDir);
    }
}
