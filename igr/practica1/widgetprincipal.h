#ifndef WIDGETPRINCIPAL_H
#define WIDGETPRINCIPAL_H

#include <QtGui/QWidget>

class Hipotrocoide;
class QSlider;

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

Q_SIGNALS:
    void zoomChanged(int zoom);
    void arriba();
    void abajo();
    void izquierda();
    void derecha();
    void centrar();
    void a(int a);
    void b(int b);
    void c(int c);
    void precision(int precision);
    void animado(bool animado);
    void embaldosado(bool embaldosado);
    void filas(int filas);
    void columnas(int columnas);

private:
    QSlider *m_zoom;
};

#endif

