#include "widgetprincipal.h"
#include "widgetdesplazamiento.h"
#include "dibujolineas.h"

#include <QtGui/QBoxLayout>
#include <QtGui/QSlider>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>

WidgetPrincipal::WidgetPrincipal(QWidget *parent)
    : QWidget(parent)
    , m_zoom(new QSlider(Qt::Horizontal, this))
    , m_escenaWidget(new QWidget(this))
    , m_tabWidget(new QTabWidget(this))
{
    {
        QVBoxLayout *principal = new QVBoxLayout;
        QHBoxLayout *zoomLayout = new QHBoxLayout;
        QLabel *zoomLabel = new QLabel("Zoom", m_escenaWidget);
        m_zoom->setMinimum(0);
        m_zoom->setMaximum(99);
        m_zoom->setValue(50);
        m_zoom->setTickInterval(1);
        zoomLayout->addWidget(zoomLabel);
        zoomLayout->addWidget(m_zoom);
        principal->addLayout(zoomLayout);
        QHBoxLayout *desplazamientoLayout = new QHBoxLayout;
        WidgetDesplazamiento *widgetDesplazamiento = new WidgetDesplazamiento(m_escenaWidget);
        desplazamientoLayout->addWidget(widgetDesplazamiento);
        desplazamientoLayout->addStretch();
        principal->addLayout(desplazamientoLayout);
        m_escenaWidget->setLayout(principal);

        connect(m_zoom, SIGNAL(valueChanged(int)), this, SIGNAL(zoomChanged(int)));
        connect(widgetDesplazamiento, SIGNAL(arriba()), this, SIGNAL(arriba()));
        connect(widgetDesplazamiento, SIGNAL(abajo()), this, SIGNAL(abajo()));
        connect(widgetDesplazamiento, SIGNAL(izquierda()), this, SIGNAL(izquierda()));
        connect(widgetDesplazamiento, SIGNAL(derecha()), this, SIGNAL(derecha()));
        connect(widgetDesplazamiento, SIGNAL(centrar()), this, SIGNAL(centrar()));
    }
    QVBoxLayout *layout = new QVBoxLayout;
    m_tabWidget->addTab(m_escenaWidget, "Escena");
    layout->addWidget(m_tabWidget);
    setLayout(layout);
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

void WidgetPrincipal::elementosSeleccionados(const QList<DibujoLineas*> &seleccion)
{
    m_tabWidget->clear();
    m_tabWidget->addTab(m_escenaWidget, "Escena");
    QList<DibujoLineas*>::ConstIterator it = seleccion.begin();
    while (it != seleccion.end()) {
        DibujoLineas *const dibujoLineas = *it;
        m_tabWidget->addTab(dibujoLineas->configWidget(), dibujoLineas->getNombre());
        ++it;
    }
}

#include "widgetprincipal.moc"

