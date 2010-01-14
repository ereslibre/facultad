#include "poligonoconvexo.h"

PoligonoConvexo::PoligonoConvexo(const PV2f &pos)
    : Obstaculo(pos)
{
}

void PoligonoConvexo::dibuja(Lapiz &lapiz) const
{
}

bool PoligonoConvexo::colisiona(const Pelota &pelota, GLdouble &thit, PV2f &n)
{
    return false;
}
