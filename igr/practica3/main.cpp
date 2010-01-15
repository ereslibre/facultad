#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>

#include "escena.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow v;
    v.setFixedSize(ESCENA_WIDTH, ESCENA_HEIGHT);
    v.setCentralWidget(new Escena(&v));
    v.show();
    return app.exec();
}

