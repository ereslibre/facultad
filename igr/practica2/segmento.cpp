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

void Segmento::cohenSutherland(const PV2f &tl, const PV2f &br)
{
    int codigoA = codigo(m_a, tl, br);
    const int codigoB = codigo(m_b, tl, br);
    for (int frontera = 0; frontera < 4; ++frontera) {
        if (!(codigoA | codigoB)) {
            return;
        } else if (codigoA & codigoB) {
            m_a = PV2f(0, 0);
            m_b = PV2f(0, 0);
            return;
        }

        if (!codigoA) {
            //int buf1 = startCode; startCode = endCode; endCode = buf1;
            //Vector2 buf2 = line.Start; line.Start = line.End; line.End = buf2;
        } else if ((codigoA & 1) == 1) {
            //line.Start.Y += dydx * (_clipMin.X - line.Start.X);
            //line.Start.X = _clipMin.X;
        } else if ((codigoA & 2) == 2) {
            //line.Start.Y += dydx * (_clipMax.X - line.Start.X);
            //line.Start.X = _clipMax.X;
        } else if ((codigoA & 4) == 4) {
            //line.Start.X += dxdy * (_clipMax.Y - line.Start.Y);
            //line.Start.Y = _clipMax.Y;
        } else if ((codigoA & 8) == 8) {
            //line.Start.X += dxdy * (_clipMin.Y - line.Start.Y);
            //line.Start.Y = _clipMin.Y;
        }
        codigoA = codigo(m_a, tl, br);
    }
}

int Segmento::codigo(const PV2f &p, const PV2f &tl, const PV2f &br) const
{
    int resultado = 0;
    if (p.getX() < tl.getX()) {
        resultado |= 1;
    } else if (p.getX() > br.getX()) {
        resultado |= 2;
    }
    if (p.getY() < tl.getY()) {
        resultado |= 4;
    } else if (p.getY() > br.getY()) {
        resultado |= 8;
    }
    return resultado;
}
