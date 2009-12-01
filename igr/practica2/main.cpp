#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>

#include "escena.h"
#include "herramientas.h"
#include "widgetprincipal.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow v;
    Escena *e = new Escena(&v);
    WidgetPrincipal *w = new WidgetPrincipal(&v);
    Herramientas *h = new Herramientas(&v);
    QObject::connect(w, SIGNAL(zoomChanged(int)), e, SLOT(setZoom(int)));
    QObject::connect(w, SIGNAL(arriba()), e, SLOT(arriba()));
    QObject::connect(w, SIGNAL(abajo()), e, SLOT(abajo()));
    QObject::connect(w, SIGNAL(izquierda()), e, SLOT(izquierda()));
    QObject::connect(w, SIGNAL(derecha()), e, SLOT(derecha()));
    QObject::connect(w, SIGNAL(centrar()), e, SLOT(centrar()));
    QObject::connect(h, SIGNAL(cambioHerramienta(uint)), e, SLOT(cambioHerramienta(uint)));
    QObject::connect(e, SIGNAL(zoomIn()), w, SLOT(zoomIn()));
    QObject::connect(e, SIGNAL(zoomOut()), w, SLOT(zoomOut()));
    QObject::connect(e, SIGNAL(elementosSeleccionados(QList<DibujoLineas*>)), w, SLOT(elementosSeleccionados(QList<DibujoLineas*>)));
    QDockWidget *opciones = new QDockWidget("Opciones", &v);
    opciones->setWidget(w);
    QDockWidget *herramientasDock = new QDockWidget("Herramientas", &v);
    herramientasDock->setWidget(h);
    v.setCentralWidget(e);
    v.addDockWidget(Qt::BottomDockWidgetArea, opciones);
    v.addDockWidget(Qt::RightDockWidgetArea, herramientasDock);
    v.show();
    return app.exec();
}

