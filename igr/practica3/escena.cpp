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

QSize Escena::sizeHint() const
{
    return QSize(640, 480);
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
    m_listaObstaculos << new Pared(PV2f(-3, 0), 1 , 1);
}

void Escena::paintGL()
{
    GLdouble left;
    GLdouble right;
    GLdouble bottom;
    GLdouble top;
    if (m_ratio < 1.0) {
        left = -2.0;
        right = 2.0;
        bottom = -2.0 * (1.0 / m_ratio);
        top = 2.0 * (1.0 / m_ratio);
    } else {
        left = -2.0 * m_ratio;
        right = 2.0 * m_ratio;
        bottom = -2.0;
        top = 2.0;
    }
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    Q_FOREACH(Obstaculo *const obstaculo, m_listaObstaculos) {
        m_lapiz.salvaEstado();
        obstaculo->dibuja(m_lapiz);
        m_lapiz.recuperaEstado();
    }
}

void Escena::resizeGL(int width, int height)
{
    m_ratio = (GLfloat) width / (GLfloat) height;
    m_width = width;
    m_height = height;
}
