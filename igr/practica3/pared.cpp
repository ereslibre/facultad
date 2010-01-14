#include "pared.h"
#include "lapiz.h"

#include <math.h>

Pared::Pared(const PV2f &pos, GLdouble anchura, GLdouble altura)
    : Obstaculo(pos)
    , m_anchura(anchura)
    , m_altura(altura)
{
}

void Pared::dibuja(Lapiz &lapiz) const
{
    lapiz.setPos(m_pos);
    lapiz.setDir(M_PI / 2.0);
    lapiz.avanzar(m_altura);
    lapiz.setDir(0);
    lapiz.avanzar(m_anchura);
    lapiz.setDir(-M_PI / 2.0);
    lapiz.avanzar(m_altura);
    lapiz.setDir(M_PI);
    lapiz.avanzar(m_anchura);
}

bool Pared::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}