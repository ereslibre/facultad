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
    const GLdouble beta = (M_PI - alpha) / 2.0;
    const GLdouble gamma = M_PI - beta;
    const GLdouble radio = (m_lado / 2.0) / cos(beta);
    PV2f pos(m_pos.getX() + radio, m_pos.getY());
    lapiz.setPos(pos);
    lapiz.girar(gamma);
    for (size_t i = 0; i < m_nLados; ++i) {
        lapiz.avanzar(m_lado);
        lapiz.girar(alpha);
    }
}

void PoligonoConvexo::dibujaEnvoltorio(Lapiz &lapiz) const
{
    const GLdouble alpha = 2.0 * M_PI / (GLdouble) m_nLados;
    const GLdouble b = RADIO_PELOTA;
    const GLdouble c = b / cos(alpha / 2.0);
    const GLdouble a = c * sin(alpha / 2.0);
    const GLdouble beta = (M_PI - alpha) / 2.0;
    const GLdouble gamma = M_PI - beta;
    const GLdouble radio = (m_lado / 2.0) / cos(beta) + c;
    PV2f pos(m_pos.getX() + radio, m_pos.getY());
    lapiz.setPos(pos);
    lapiz.girar(gamma);
    for (size_t i = 0; i < m_nLados; ++i) {
        lapiz.avanzar(m_lado + 2 * a);
        lapiz.girar(alpha);
    }
}

void PoligonoConvexo::dibujaNormales(Lapiz &lapiz) const
{
//     const GLdouble alpha = 2.0 * M_PI / (GLdouble) m_nLados;
//     const GLdouble beta = (M_PI - alpha) / 2.0;
//     const GLdouble gamma = M_PI - beta;
//     const GLdouble radio = ((m_lado + RADIO_PELOTA * 2.0) / 2.0) / cos(beta);
//     PV2f pos(m_pos.getX() + radio, m_pos.getY());
//     lapiz.setPos(pos);
//     lapiz.girar(gamma);
//     for (size_t i = 0; i < m_nLados; ++i) {
//         const PV2f oldPos = lapiz.getPos();
//         lapiz.avanzar((m_lado + RADIO_PELOTA * 2.0) / 2.0, Lapiz::NoDejarRastro);
//         const PV2f medPos = lapiz.getPos();
//         lapiz.avanzar((m_lado + RADIO_PELOTA * 2.0) / 2.0, Lapiz::NoDejarRastro);
//         const PV2f pos = lapiz.getPos();
//         PV2f aux = oldPos - pos;
//         aux = aux.normal(PV2f::Izquierda);
//         aux.normalizar();
//         aux *= RADIO_PELOTA;
//         glBegin(GL_LINES);
//         glVertex2d(medPos.getX(), medPos.getY());
//         glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
//         glEnd();
//         lapiz.girar(alpha);
//     }
}

bool PoligonoConvexo::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}
