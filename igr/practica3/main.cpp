#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>

#include "escena.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow v;
    v.setCentralWidget(new Escena(&v));
    v.show();
    return app.exec();
}

