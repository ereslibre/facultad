#include "segmento.h"

#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 4
#define ABAJO 8

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
    int codigoB = codigo(m_b, tl, br);
    for (int frontera = 0; frontera < 4; ++frontera) {
        if (!(codigoA | codigoB)) {
            return;
        } else if (codigoA & codigoB) {
            m_a = PV2f(0, 0);
            m_b = PV2f(0, 0);
            return;
        }
        if (!codigoA) {
            const int caux = codigoA;
            codigoA = codigoB;
            codigoB = caux;
            const PV2f aux = m_a;
            m_a = m_b;
            m_b = aux;
        } else if ((codigoA & IZQUIERDA) == IZQUIERDA) {
            m_a.setY(m_b.getY() - ((m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX())) * (m_b.getX() - tl.getX()));
            m_a.setX(tl.getX());
        } else if ((codigoA & DERECHA) == DERECHA) {
            m_a.setY(m_b.getY() - ((m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX())) * (m_b.getX() - br.getX()));
            m_a.setX(br.getX());
        } else if ((codigoA & ARRIBA) == ARRIBA) {
            m_a.setX(m_b.getX() - ((m_b.getY() - tl.getY()) * (m_b.getX() - m_a.getX()) / (m_b.getY() - m_a.getY())));
            m_a.setY(tl.getY());
        } else if ((codigoA & ABAJO) == ABAJO) {
            m_a.setX(m_b.getX() - ((m_b.getY() - br.getY()) * (m_b.getX() - m_a.getX()) / (m_b.getY() - m_a.getY())));
            m_a.setY(br.getY());
        }
        codigoA = codigo(m_a, tl, br);
    }
}

int Segmento::codigo(const PV2f &p, const PV2f &tl, const PV2f &br) const
{
    int resultado = 0;
    if (p.getX() < tl.getX()) {
        resultado |= IZQUIERDA;
    } else if (p.getX() > br.getX()) {
        resultado |= DERECHA;
    }
    if (p.getY() < tl.getY()) {
        resultado |= ARRIBA;
    } else if (p.getY() > br.getY()) {
        resultado |= ABAJO;
    }
    return resultado;
}
