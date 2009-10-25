#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>

#include "hipotrocoide.h"
#include "widgetprincipal.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow v;
    Hipotrocoide *h = new Hipotrocoide(&v);
    WidgetPrincipal *w = new WidgetPrincipal(&v);
    QObject::connect(w, SIGNAL(zoomChanged(int)), h, SLOT(setZoom(int)));
    QObject::connect(w, SIGNAL(arriba()), h, SLOT(arriba()));
    QObject::connect(w, SIGNAL(abajo()), h, SLOT(abajo()));
    QObject::connect(w, SIGNAL(izquierda()), h, SLOT(izquierda()));
    QObject::connect(w, SIGNAL(derecha()), h, SLOT(derecha()));
    QObject::connect(w, SIGNAL(centrar()), h, SLOT(centrar()));
    QObject::connect(w, SIGNAL(a(int)), h, SLOT(sa(int)));
    QObject::connect(w, SIGNAL(b(int)), h, SLOT(sb(int)));
    QObject::connect(w, SIGNAL(c(int)), h, SLOT(sc(int)));
    QObject::connect(w, SIGNAL(precision(int)), h, SLOT(sprecision(int)));
    QObject::connect(w, SIGNAL(animado(bool)), h, SLOT(sanimado(bool)));
    QObject::connect(w, SIGNAL(embaldosado(bool)), h, SLOT(sembaldosado(bool)));
    QObject::connect(w, SIGNAL(filas(int)), h, SLOT(sfilas(int)));
    QObject::connect(w, SIGNAL(columnas(int)), h, SLOT(scolumnas(int)));
    QObject::connect(h, SIGNAL(zoomIn()), w, SLOT(zoomIn()));
    QObject::connect(h, SIGNAL(zoomOut()), w, SLOT(zoomOut()));
    QDockWidget *dock = new QDockWidget("Herramientas", &v);
    dock->setWidget(w);
    v.setCentralWidget(h);
    v.addDockWidget(Qt::BottomDockWidgetArea, dock);
    v.show();
    return app.exec();
}

