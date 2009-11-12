#include "widgetprincipal.h"
#include "widgetdesplazamiento.h"

#include <QtGui/QBoxLayout>
#include <QtGui/QSlider>
#include <QtGui/QLabel>

WidgetPrincipal::WidgetPrincipal(QWidget *parent)
    : QWidget(parent)
    , m_zoom(new QSlider(Qt::Horizontal, this))
{
    QVBoxLayout *principal = new QVBoxLayout;
    QHBoxLayout *zoomLayout = new QHBoxLayout;
    QLabel *zoomLabel = new QLabel("Zoom", this);
    m_zoom->setMinimum(0);
    m_zoom->setMaximum(99);
    m_zoom->setValue(50);
    m_zoom->setTickInterval(1);
    zoomLayout->addWidget(zoomLabel);
    zoomLayout->addWidget(m_zoom);
    principal->addLayout(zoomLayout);
    QHBoxLayout *desplazamientoLayout = new QHBoxLayout;
    WidgetDesplazamiento *widgetDesplazamiento = new WidgetDesplazamiento(this);
    desplazamientoLayout->addWidget(widgetDesplazamiento);
    principal->addLayout(desplazamientoLayout);
    setLayout(principal);

    connect(m_zoom, SIGNAL(valueChanged(int)), this, SIGNAL(zoomChanged(int)));
    connect(widgetDesplazamiento, SIGNAL(arriba()), this, SIGNAL(arriba()));
    connect(widgetDesplazamiento, SIGNAL(abajo()), this, SIGNAL(abajo()));
    connect(widgetDesplazamiento, SIGNAL(izquierda()), this, SIGNAL(izquierda()));
    connect(widgetDesplazamiento, SIGNAL(derecha()), this, SIGNAL(derecha()));
    connect(widgetDesplazamiento, SIGNAL(centrar()), this, SIGNAL(centrar()));
}

WidgetPrincipal::~WidgetPrincipal()
{
}

void WidgetPrincipal::zoomIn()
{
    m_zoom->blockSignals(true);
    m_zoom->setValue(m_zoom->value() + 10);
    m_zoom->blockSignals(false);
    emit zoomChanged(m_zoom->value());
}

void WidgetPrincipal::zoomOut()
{
    m_zoom->blockSignals(true);
    m_zoom->setValue(m_zoom->value() - 10);
    m_zoom->blockSignals(false);
    emit zoomChanged(m_zoom->value());
}

#include "widgetprincipal.moc"

