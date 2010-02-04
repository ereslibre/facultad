#ifndef PELOTA_H
#define PELOTA_H

#include "obstaculo.h"
#include "pv2f.h"
#include "general.h"

class Lapiz;

class Pelota
    : public Obstaculo
{
public:
    enum Tipo {
        Protagonista = 0,
        NoProtagonista
    };

    Pelota(const PV2f &pos, GLdouble radio = RADIO_PELOTA, Tipo tipo = NoProtagonista);
    virtual ~Pelota();

    PV2f getSentido() const;
    void setFuerza(GLdouble fuerza);
    GLdouble getFuerza() const;
    GLdouble getRadio() const;

    void incrementaFuerza();

    void incrementaAngulo();
    void decrementaAngulo();

    void avanza(GLdouble paso = -1.0);
    void reflexion(const PV2f &n);

    virtual void dibuja(Lapiz &lapiz) const;
    virtual void dibujaEnvoltorio(Lapiz &lapiz) const;
    virtual void dibujaNormales(Lapiz &lapiz) const;
    virtual bool colisiona(Pelota *pelota, GLdouble &thit, PV2f &n, Lapiz &lapiz);

private:
    PV2f     m_sentido;
    GLdouble m_fuerza;
    GLdouble m_radio;
    Tipo     m_tipo;
};

#endif
