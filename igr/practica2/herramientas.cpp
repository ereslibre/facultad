#include "herramientas.h"

#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>

#define NUM_HERRAMIENTAS 7

Herramientas::Herramientas(QWidget *parent)
    : QWidget(parent)
    , m_ninguna(new QPushButton("Ninguna", this))
    , m_recortar(new QPushButton("Recortar", this))
    , m_mover(new QPushButton("Mover", this))
    , m_manual(new QPushButton("Manual", this))
    , m_poliEspiral(new QPushButton("Poli-espiral", this))
    , m_poliRegular(new QPushButton("Poligono regular", this))
    , m_hipotrocoide(new QPushButton("Hipotrocoide", this))
{
    QPushButton *herramientas[] = { m_ninguna, m_recortar, m_mover, m_manual, m_poliEspiral, m_poliRegular,
                                    m_hipotrocoide };
    QVBoxLayout *layout = new QVBoxLayout;
    for (uint i = 0; i < NUM_HERRAMIENTAS; ++i) {
        herramientas[i]->setCheckable(true);
        herramientas[i]->setAutoExclusive(true);
    }
    m_ninguna->toggle();
    for (uint i = 0; i < NUM_HERRAMIENTAS; ++i) {
        connect(herramientas[i], SIGNAL(clicked(bool)), this, SLOT(herramientaSeleccionada()));
        layout->addWidget(herramientas[i]);
    }
    setLayout(layout);
}

Herramientas::~Herramientas()
{
}

void Herramientas::herramientaSeleccionada()
{
    QPushButton *herramientas[] = { m_ninguna, m_recortar, m_mover, m_manual, m_poliEspiral, m_poliRegular,
                                    m_hipotrocoide };
    QPushButton *herramienta = qobject_cast<QPushButton*>(sender());
    for (uint i = 0; i < NUM_HERRAMIENTAS; ++i) {
        if (herramienta == herramientas[i]) {
            emit cambioHerramienta(i);
            return;
        }
    }
}

#include "herramientas.moc"
