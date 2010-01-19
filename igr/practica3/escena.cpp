#include "escena.h"
#include "pared.h"
#include "general.h"
#include "poligonoconvexo.h"
#include "pelota.h"

#include <QtCore/QTimer>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>

#include <math.h>

Escena::Escena(QWidget *parent)
    : QGLWidget(parent)
    , m_pelota(0)
    , m_timer(new QTimer)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(actualizaEstado()));
}

Escena::~Escena()
{
    makeCurrent();
}

void Escena::actualizaEstado()
{
    if (m_pelota->getFuerza() < 0.5) {
        m_timer->stop();
    }
    m_pelota->avanza();
    update();
}

void Escena::keyPressEvent(QKeyEvent *event)
{
    if (m_timer->isActive()) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Up:
            break;
        case Qt::Key_Down:
            break;
        case Qt::Key_Left:
            m_pelota->decrementaAngulo();
            break;
        case Qt::Key_Right:
            m_pelota->incrementaAngulo();
            break;
        default:
            event->ignore();
            return;
    }
    update();
}

void Escena::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        m_pelota->incrementaFuerza();
        m_timer->start();
    } else {
        event->ignore();
        return;
    }
    update();
}

void Escena::initializeGL()
{
    glViewport(0, 0, ESCENA_WIDTH, ESCENA_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ESCENA_WIDTH, 0, ESCENA_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    m_listaObstaculos << new Pared(PV2f(0, 0), ESCENA_WIDTH , 20, Pared::EsPared);
    m_listaObstaculos << new Pared(PV2f(0, 0), 20, ESCENA_HEIGHT, Pared::EsPared);
    m_listaObstaculos << new Pared(PV2f(0, ESCENA_HEIGHT - 20), ESCENA_WIDTH, 20, Pared::EsPared);
    m_listaObstaculos << new Pared(PV2f(ESCENA_WIDTH - 20, 0), 20, ESCENA_HEIGHT, Pared::EsPared);
    m_listaObstaculos << new Pared(PV2f(620, 350), 40, 40);
    m_listaObstaculos << new PoligonoConvexo(PV2f(300, 250), 100, 5);
    m_pelota = new Pelota(PV2f(650, 150));
    m_listaObstaculos << m_pelota;
}

void Escena::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    Q_FOREACH (Obstaculo *const obstaculo, m_listaObstaculos) {
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
            m_lapiz.salvaEstado();
            obstaculo->dibuja(m_lapiz);
            m_lapiz.recuperaEstado();
            glPopMatrix();
        }
#if DEBUG_MODE
        {
            glColor3f(0.0f, 0.0f, 1.0f);
            glPushMatrix();
            m_lapiz.salvaEstado();
            obstaculo->dibujaEnvoltorio(m_lapiz);
            m_lapiz.recuperaEstado();
            glPopMatrix();
        }
        {
            glColor3f(1.0f, 1.0f, 0.0f);
            glPushMatrix();
            m_lapiz.salvaEstado();
            obstaculo->dibujaNormales(m_lapiz);
            m_lapiz.recuperaEstado();
            glPopMatrix();
        }
#else
        glColor3f(1.0f, 1.0f, 0.0f);
        m_pelota->dibujaNormales(m_lapiz);
#endif
    }
}

#include "escena.moc"
