#ifndef WIDGETPRINCIPAL_H
#define WIDGETPRINCIPAL_H

#include <QtGui/QWidget>

class DibujoLineas;
class Hipotrocoide;
class QSlider;
class QTabWidget;

class WidgetPrincipal
    : public QWidget
{
    Q_OBJECT

public:
    WidgetPrincipal(QWidget *parent = 0);
    ~WidgetPrincipal();

public Q_SLOTS:
    void zoomIn();
    void zoomOut();
    void elementosSeleccionados(const QList<DibujoLineas*> &seleccion);

Q_SIGNALS:
    void zoomChanged(int zoom);
    void arriba();
    void abajo();
    void izquierda();
    void derecha();
    void centrar();

private:
    QSlider    *m_zoom;
    QWidget    *m_escenaWidget;
    QTabWidget *m_tabWidget;
};

#endif

