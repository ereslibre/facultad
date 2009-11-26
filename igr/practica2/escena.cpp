#include "escena.h"

#include <QtGui/QWheelEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include "dibujomanual.h"
#include "poliespiral.h"
#include "herramientas.h"

// FIXME
#include <math.h>

Escena::Escena(QWidget *parent)
    : QGLWidget(parent)
    , m_zoom(50)
    , m_xoffsetAcumulado(0)
    , m_yoffsetAcumulado(0)
    , m_dibujoManualAct(0)
    , m_herramienta(Herramientas::Ninguna)
    , m_estado(Idle)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

Escena::~Escena()
{
    makeCurrent();
}

void Escena::setZoom(int zoom)
{
    m_zoom = 100.0 - zoom;
    resizeGL(m_width, m_height);
    update();
}

void Escena::arriba()
{
    m_yoffsetAcumulado += 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Escena::abajo()
{
    m_yoffsetAcumulado -= 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Escena::izquierda()
{
    m_xoffsetAcumulado -= 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Escena::derecha()
{
    m_xoffsetAcumulado += 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Escena::centrar()
{
    m_xoffsetAcumulado = 0;
    m_yoffsetAcumulado = 0;
    resizeGL(m_width, m_height);
    update();
}

void Escena::cambioHerramienta(uint herramienta)
{
    m_herramienta = herramienta;
    if (m_estado == CreandoDibujo) {
        m_dibujoManualAct = 0;
        m_ultimoClick = QPointF();
        m_estado = Idle;
    }
}

QSize Escena::sizeHint() const
{
    return QSize(640, 480);
}

void Escena::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        emit zoomIn();
    } else {
        emit zoomOut();
    }
    event->accept();
}

void Escena::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            arriba();
            break;
        case Qt::Key_Down:
            abajo();
            break;
        case Qt::Key_Left:
            izquierda();
            break;
        case Qt::Key_Right:
            derecha();
            break;
        case Qt::Key_Period:
            centrar();
            break;
        default:
            event->ignore();
            return;
    }
    event->accept();
}

void Escena::mousePressEvent(QMouseEvent *event)
{
    const QPointF posClick = mapeaPVaAVE(event->pos());
    if (m_herramienta == Herramientas::Ninguna) {
        QList<DibujoLineas*>::ConstIterator it = m_listaDibujoLineas.begin();
        while (it != m_listaDibujoLineas.end()) {
            DibujoLineas *const dibujoLineas = *it;
            if (dibujoLineas->clickSobreFigura(PV2f(posClick.x(), posClick.y()))) {
                // se hizo clic en la figura (cerca de algún vértice suyo)
            }
            ++it;
        }
    } else if (m_herramienta == Herramientas::Manual) {
        if (!m_dibujoManualAct) {
            m_dibujoManualAct = new DibujoManual(m_lapiz);
            m_listaDibujoLineas << m_dibujoManualAct;
        }
        if (m_estado == Idle) {
            m_ultimoClick = mapeaPVaAVE(event->pos());
            m_estado = CreandoDibujo;
        } else {
            m_dibujoManualAct->anadeSegmento(Segmento(PV2f(m_ultimoClick.x(), m_ultimoClick.y()),
                                                      PV2f(posClick.x(), posClick.y())));
            m_ultimoClick = posClick;
        }
        event->accept();
    } else if (m_herramienta == Herramientas::PoliEspiral) {
        m_listaDibujoLineas << new PoliEspiral(m_lapiz, PV2f(posClick.x(), posClick.y()), 10, 2, M_PI / 4.0, 5);
    }
    update();
}

void Escena::mouseReleaseEvent(QMouseEvent *event)
{
}

void Escena::initializeGL()
{
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
    glOrtho(left * m_zoom + m_xoffsetAcumulado / 2.0, right * m_zoom + m_xoffsetAcumulado / 2.0,
            bottom * m_zoom + m_yoffsetAcumulado / 2.0, top * m_zoom + m_yoffsetAcumulado / 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    QList<DibujoLineas*>::ConstIterator it = m_listaDibujoLineas.begin();
    while (it != m_listaDibujoLineas.end()) {
        m_lapiz.salvaEstado();
        DibujoLineas *const dibujoLineas = *it;
        m_lapiz.setPos(dibujoLineas->getCentro());
        dibujoLineas->dibuja();
        m_lapiz.recuperaEstado();
        ++it;
    }
}

void Escena::resizeGL(int width, int height)
{
    m_ratio = (GLfloat) width / (GLfloat) height;
    m_width = width;
    m_height = height;
}

QPointF Escena::mapeaPVaAVE(const QPoint &p)
{
    QPointF res;
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
    left = left * m_zoom + m_xoffsetAcumulado / 2.0;
    right = right * m_zoom + m_xoffsetAcumulado / 2.0;
    bottom = bottom * m_zoom - m_yoffsetAcumulado / 2.0;
    top = top * m_zoom - m_yoffsetAcumulado / 2.0;
    res.setX((p.x() * (right - left) / width()) + left);
    res.setY(-((p.y() * (top - bottom) / height()) + bottom));
    return res;
}

#include "escena.moc"
