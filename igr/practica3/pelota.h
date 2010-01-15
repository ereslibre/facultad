#ifndef PELOTA_H
#define PELOTA_H

#include "obstaculo.h"
#include "pv2f.h"

class Lapiz;

class Pelota
    : public Obstaculo
{
public:
    Pelota(const PV2f &pos);
    virtual ~Pelota();

    PV2f getCentro() const;
    GLdouble getFuerza() const;
    GLdouble getRadio() const;

    void avanza(GLdouble pasos);
    void reflexion(const PV2f &n);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales(Lapiz &lapiz) const;
    virtual bool colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n);

private:
    PV2f             m_centro;
    PV2f             m_sentido;
    GLdouble         m_fuerza;
    GLdouble         m_radio;
};

#endif
