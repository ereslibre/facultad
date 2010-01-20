#include "poligonoconvexo.h"
#include "lapiz.h"
#include "general.h"
#include "pelota.h"

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
        const PV2f oldPos = lapiz.getPos();
        lapiz.avanzar((m_lado + 2 * a) / 2.0, Lapiz::NoDejarRastro);
        const PV2f medPos = lapiz.getPos();
        lapiz.avanzar((m_lado + 2 * a) / 2.0, Lapiz::NoDejarRastro);
        const PV2f pos = lapiz.getPos();
        PV2f aux = oldPos - pos;
        aux = aux.normal(PV2f::Izquierda);
        aux.normalizar();
        aux *= RADIO_PELOTA;
        glBegin(GL_LINES);
        glVertex2d(medPos.getX(), medPos.getY());
        glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
        glEnd();
        lapiz.girar(alpha);
    }
}
#include <QtCore/QDebug>
bool PoligonoConvexo::colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz)
{
    GLdouble tin = 0.0;
    GLdouble tout = 1.0;
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
        if (tin > tout) {
            break;
        }
        const PV2f oldPos = lapiz.getPos();
        lapiz.avanzar(m_lado + 2 * a, Lapiz::NoDejarRastro);
        const PV2f pos = lapiz.getPos();
        const PV2f co = pos - pelota->getPos();
        PV2f n_ = (pos - oldPos).normal(PV2f::Derecha);
        n_.normalizar();
        const GLdouble num = n_.dot(co);
        const GLdouble den = pelota->getSentido().dot(n_);
        if (!den) {
            if (num <= 0) {
                return false;
            }
        } else {
            thit = num / den;
            if (den < 0) {
                if (thit > tin) {
                    n = n_;
                }
                tin = qMax(tin, thit);
            } else {
                if (thit < tout) {
                    n = n_;
                }
                tout = qMin(tout, thit);
            }
        }
        lapiz.girar(alpha);
    }
    return tin <= tout;
}
