#include "escena.h"
#include "pared.h"
#include "general.h"

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>

#include <math.h>

Escena::Escena(QWidget *parent)
    : QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

Escena::~Escena()
{
    makeCurrent();
}

void Escena::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            break;
        case Qt::Key_Down:
            break;
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        default:
            event->ignore();
            return;
    }
    update();
}

void Escena::initializeGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, ESCENA_WIDTH, ESCENA_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ESCENA_WIDTH, 0, ESCENA_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    m_listaObstaculos << new Pared(PV2f(0, 0), ESCENA_WIDTH , 20);
    m_listaObstaculos << new Pared(PV2f(0, 0), 20, ESCENA_HEIGHT);
    m_listaObstaculos << new Pared(PV2f(0, ESCENA_HEIGHT - 20), ESCENA_WIDTH, 20);
    m_listaObstaculos << new Pared(PV2f(ESCENA_WIDTH - 20, 0), 20, ESCENA_HEIGHT);
}

void Escena::paintGL()
{
    Q_FOREACH(Obstaculo *const obstaculo, m_listaObstaculos) {
        glPushMatrix();
        m_lapiz.salvaEstado();
        obstaculo->dibuja(m_lapiz);
        m_lapiz.recuperaEstado();
        glPopMatrix();
    }
}
