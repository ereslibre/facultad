#ifndef LAPIZ_H
#define LAPIZ_H

#include <QtCore/QStack>
#include "pv2f.h"

class Lapiz
{
public:
    Lapiz();

    void salvaEstado();
    void recuperaEstado();

    void girar(GLdouble radianes);
    void avanzar(GLfloat distancia, bool dejarRastro = true);

    void setDir(GLdouble dir);
    void setPos(const PV2f &pos);

    GLdouble getDir() const;
    const PV2f &getPos() const;

private:
    struct Estado {
        GLdouble dir;
        PV2f     pos;
    } m_e;
    QStack<Estado> m_pilaEstados;
};

#endif
