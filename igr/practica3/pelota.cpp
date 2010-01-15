#include "pelota.h"
#include "general.h"
#include "lapiz.h"
#include "poligonoconvexo.h"

#include <math.h>

Pelota::Pelota(const PV2f &pos)
    : Obstaculo(pos)
    , m_centro(0, 0)
    , m_sentido(PV2f::Vector)
    , m_fuerza(0)
    , m_radio(RADIO_PELOTA)
    , m_poligonoConvexo(new PoligonoConvexo(pos, 1, 150))
{
}

Pelota::~Pelota()
{
    delete m_poligonoConvexo;
}

PV2f Pelota::getCentro() const
{
    return m_centro;
}

GLdouble Pelota::getFuerza() const
{
    return m_fuerza;
}

GLdouble Pelota::getRadio() const
{
    return m_radio;
}

void Pelota::avanza(GLdouble pasos)
{
}

void Pelota::reflexion(const PV2f &n)
{
}

void Pelota::dibuja(Lapiz &lapiz) const
{
    m_poligonoConvexo->dibuja(lapiz);
}

void Pelota::dibujaEnvoltorio(Lapiz &lapiz) const
{
}

void Pelota::dibujaNormales(Lapiz &lapiz) const
{
    dibujaNormal(m_pos);
}

bool Pelota::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}