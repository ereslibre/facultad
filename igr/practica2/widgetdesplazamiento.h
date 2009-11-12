#ifndef WIDGETDESPLAZAMIENTO_H
#define WIDGETDESPLAZAMIENTO_H

#include <QtGui/QWidget>

class WidgetDesplazamiento
    : public QWidget
{
    Q_OBJECT

public:
    WidgetDesplazamiento(QWidget *parent = 0);
    ~WidgetDesplazamiento();

Q_SIGNALS:
    void arriba();
    void abajo();
    void izquierda();
    void derecha();
    void centrar();
};

#endif

