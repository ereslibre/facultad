#include "widgetprincipal.h"
#include "widgetdesplazamiento.h"
#include "widgetparametrico.h"

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
    desplazamientoLayout->addStretch();
    WidgetParametrico *widgetParametrico = new WidgetParametrico(this);
    desplazamientoLayout->addWidget(widgetParametrico);
    principal->addLayout(desplazamientoLayout);
    setLayout(principal);

    connect(m_zoom, SIGNAL(valueChanged(int)), this, SIGNAL(zoomChanged(int)));
    connect(widgetDesplazamiento, SIGNAL(arriba()), this, SIGNAL(arriba()));
    connect(widgetDesplazamiento, SIGNAL(abajo()), this, SIGNAL(abajo()));
    connect(widgetDesplazamiento, SIGNAL(izquierda()), this, SIGNAL(izquierda()));
    connect(widgetDesplazamiento, SIGNAL(derecha()), this, SIGNAL(derecha()));
    connect(widgetDesplazamiento, SIGNAL(centrar()), this, SIGNAL(centrar()));
    connect(widgetParametrico, SIGNAL(a(int)), this, SIGNAL(a(int)));
    connect(widgetParametrico, SIGNAL(b(int)), this, SIGNAL(b(int)));
    connect(widgetParametrico, SIGNAL(c(int)), this, SIGNAL(c(int)));
    connect(widgetParametrico, SIGNAL(precision(int)), this, SIGNAL(precision(int)));
    connect(widgetParametrico, SIGNAL(animado(bool)), this, SIGNAL(animado(bool)));
    connect(widgetParametrico, SIGNAL(embaldosado(bool)), this, SIGNAL(embaldosado(bool)));
    connect(widgetParametrico, SIGNAL(filas(int)), this, SIGNAL(filas(int)));
    connect(widgetParametrico, SIGNAL(columnas(int)), this, SIGNAL(columnas(int)));
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

