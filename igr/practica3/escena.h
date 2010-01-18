#ifndef ESCENA_H
#define ESCENA_H

#include <QtCore/QList>
#include <QtCore/QStack>
#include <QtOpenGL/QGLWidget>
#include "lapiz.h"

#define ESCENA_WIDTH  800.0
#define ESCENA_HEIGHT 500.0

class DibujoLineas;
class Obstaculo;
class Pelota;

class Escena
    : public QGLWidget
{
    Q_OBJECT

public:
    Escena(QWidget *parent = 0);
    ~Escena();

public Q_SLOTS:
    void actualizaEstado();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    virtual void initializeGL();
    virtual void paintGL();

private:
    Lapiz             m_lapiz;
    QList<Obstaculo*> m_listaObstaculos;
    Pelota           *m_pelota;
    QTimer           *m_timer;
};

#endif

