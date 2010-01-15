#include "poligonoconvexo.h"
#include "lapiz.h"
#include "general.h"

#include <math.h>

PoligonoConvexo::PoligonoConvexo(const PV2f &pos, GLdouble lado, size_t nLados)
    : Obstaculo(pos)
    , m_lado(lado)
    , m_nLados(nLados)
{
}

void PoligonoConvexo::dibuja(Lapiz &lapiz) const
{
    const GLdouble alpha = 2.0 * M_PI / (GLdouble) m_nLados;
    const GLdouble beta = (M_PI - alpha) / 2;
    const GLdouble radio = (m_lado / 2.0) / sin(alpha / 2.0);
    const GLdouble gamma = M_PI - beta;
    lapiz.setPos(m_pos);
    lapiz.avanzar(radio, Lapiz::NoDejarRastro);
    lapiz.girar(gamma);
    for (int i = 0; i < m_nLados; ++i) {
        lapiz.avanzar(m_lado);
        lapiz.girar(alpha);
    }
}

void PoligonoConvexo::dibujaEnvoltorio(Lapiz &lapiz) const
{
    const GLdouble alpha = 2.0 * M_PI / (GLdouble) m_nLados;
    const GLdouble beta = (M_PI - alpha) / 2;
    const GLdouble radio = ((m_lado + RADIO_PELOTA) / 2.0) / sin(alpha / 2.0);
    const GLdouble gamma = M_PI - beta;
    lapiz.setPos(m_pos);
    lapiz.avanzar(radio, Lapiz::NoDejarRastro);
    lapiz.girar(gamma);
    for (int i = 0; i < m_nLados; ++i) {
        lapiz.avanzar(m_lado + RADIO_PELOTA);
        lapiz.girar(alpha);
    }
}

bool PoligonoConvexo::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}
