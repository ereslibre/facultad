#include "segmento.h"

Segmento::Segmento(const PV2f &a, const PV2f &b)
    : m_a(a)
    , m_b(b)
{
}

Segmento::Segmento(const Segmento &segmento)
    : m_a(segmento.m_a)
    , m_b(segmento.m_b)
{
}

const PV2f &Segmento::getA() const
{
    return m_a;
}

const PV2f &Segmento::getB() const
{
    return m_b;
}

void Segmento::setA(const PV2f &a)
{
    m_a = a;
}

void Segmento::setB(const PV2f &b)
{
    m_b = b;
}

bool Segmento::esValido() const
{
    return m_a != m_b;
}

void Segmento::cohenSutherland(const PV2f &tl, const PV2f &bm)
{
}
