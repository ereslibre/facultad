#include "widgetdesplazamiento.h"

#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>

WidgetDesplazamiento::WidgetDesplazamiento(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *arriba = new QPushButton(this);
    QPushButton *abajo = new QPushButton(this);
    QPushButton *izquierda = new QPushButton(this);
    QPushButton *derecha = new QPushButton(this);
    QPushButton *centrar = new QPushButton(this);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(arriba, 0, 1);
    gridLayout->addWidget(abajo, 2, 1);
    gridLayout->addWidget(izquierda, 1, 0);
    gridLayout->addWidget(derecha, 1, 2);
    gridLayout->addWidget(centrar, 1, 1);
    setLayout(gridLayout);

    arriba->setIcon(QIcon("iconos/arrow-up.png"));
    abajo->setIcon(QIcon("iconos/arrow-down.png"));
    izquierda->setIcon(QIcon("iconos/arrow-left.png"));
    derecha->setIcon(QIcon("iconos/arrow-right.png"));
    centrar->setIcon(QIcon("iconos/view-refresh.png"));

    connect(arriba, SIGNAL(clicked(bool)), this, SIGNAL(arriba()));
    connect(abajo, SIGNAL(clicked(bool)), this, SIGNAL(abajo()));
    connect(izquierda, SIGNAL(clicked(bool)), this, SIGNAL(izquierda()));
    connect(derecha, SIGNAL(clicked(bool)), this, SIGNAL(derecha()));
    connect(centrar, SIGNAL(clicked(bool)), this, SIGNAL(centrar()));
}

WidgetDesplazamiento::~WidgetDesplazamiento()
{
}

#include "widgetdesplazamiento.moc"

