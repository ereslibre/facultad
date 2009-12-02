#include "dibujomanual.h"

DibujoManual::DibujoManual(Lapiz &l)
    : DibujoLineas(l)
{
}

QString DibujoManual::getNombre() const
{
    return "Dibujo Manual";
}

DibujoLineas *DibujoManual::clonar() const
{
    DibujoManual *res = new DibujoManual(m_l);
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        res->anadeSegmento(*it);
        ++it;
    }
    return res;
}

QWidget *DibujoManual::configWidget()
{
    return 0;
}

void DibujoManual::salva(QTextStream &stream) const
{
    stream << "DibujoManual\n";
    stream << QString::number(m_listaSegmentos.count()) << '\n';
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        stream << QString::number(segmento.getA().getX()) << ',' << QString::number(segmento.getA().getY()) << ',' <<
                  QString::number(segmento.getB().getX()) << ',' << QString::number(segmento.getB().getY()) << '\n';
        ++it;
    }
}

void DibujoManual::invalidar()
{
}
