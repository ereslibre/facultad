#ifndef SEGMENTO_H
#define SEGMENTO_H

#include "pv2f.h"

class Segmento
{
public:
    Segmento(const PV2f &a, const PV2f &b);
    Segmento(const Segmento &segmento);

    const PV2f &getA() const;
    const PV2f &getB() const;

    void setA(const PV2f &a);
    void setB(const PV2f &b);

    bool esValido() const;

    void cohenSutherland(const PV2f &tl, const PV2f &br);

private:
    int codigo(const PV2f &p, const PV2f &tl, const PV2f &br) const;

    PV2f m_a;
    PV2f m_b;
};

#endif
