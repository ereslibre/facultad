#include "pared.h"
#include "lapiz.h"
#include "general.h"

#include <math.h>

Pared::Pared(const PV2f &pos, GLdouble anchura, GLdouble altura)
    : Obstaculo(pos)
    , m_anchura(anchura)
    , m_altura(altura)
{
}

void Pared::dibuja(Lapiz &lapiz) const
{
    glBegin(GL_LINE_STRIP);
    glVertex2d(m_pos.getX(), m_pos.getY());
    glVertex2d(m_pos.getX(), m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY() + m_altura);
    glVertex2d(m_pos.getX() + m_anchura, m_pos.getY());
    glVertex2d(m_pos.getX(), m_pos.getY());
    glEnd();
}

void Pared::dibujaEnvoltorio(Lapiz &lapiz) const
{
    glBegin(GL_LINE_STRIP);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    glVertex2d(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glVertex2d(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glEnd();
}

void Pared::dibujaNormales(Lapiz &lapiz) const
{
    const PV2f bl = PV2f(m_pos.getX() - RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    const PV2f tl = PV2f(m_pos.getX() - RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    const PV2f tr = PV2f(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() + m_altura + RADIO_PELOTA);
    const PV2f br = PV2f(m_pos.getX() + m_anchura + RADIO_PELOTA, m_pos.getY() - RADIO_PELOTA);
    glBegin(GL_LINES);
    {
        const PV2f medPos = PV2f(tl.getX(), tl.getY() - (m_altura + RADIO_PELOTA * 2.0) / 2.0);
        PV2f aux = tl - bl;
        aux = aux.normal(PV2f::Izquierda);
        aux *= 0.1;
        glVertex2d(medPos.getX(), medPos.getY());
        glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
    }
    {
        const PV2f medPos = PV2f(tl.getX() + (m_anchura + RADIO_PELOTA * 2.0) / 2.0, tl.getY());
        PV2f aux = tr - tl;
        aux = aux.normal(PV2f::Izquierda);
        aux *= 0.1;
        glVertex2d(medPos.getX(), medPos.getY());
        glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
    }
    {
        const PV2f medPos = PV2f(tr.getX(), tr.getY() - (m_altura + RADIO_PELOTA * 2.0) / 2.0);
        PV2f aux = br - tr;
        aux = aux.normal(PV2f::Izquierda);
        aux *= 0.1;
        glVertex2d(medPos.getX(), medPos.getY());
        glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
    }
    {
        const PV2f medPos = PV2f(br.getX() - (m_anchura + RADIO_PELOTA * 2.0) / 2.0, br.getY());
        PV2f aux = bl - br;
        aux = aux.normal(PV2f::Izquierda);
        aux *= 0.1;
        glVertex2d(medPos.getX(), medPos.getY());
        glVertex2d((aux + medPos).getX(), (aux + medPos).getY());
    }
    glEnd();
}

bool Pared::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}