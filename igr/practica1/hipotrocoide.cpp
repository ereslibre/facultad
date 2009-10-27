#include "hipotrocoide.h"

#include <QtCore/QTimer>
#include <QtGui/QWheelEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>

#include <math.h>

#include <boost/math/common_factor.hpp>

Hipotrocoide::Hipotrocoide(QWidget *parent)
    : QGLWidget(parent)
    , m_a(300)
    , m_b(280)
    , m_c(50)
    , m_precision(500)
    , m_zoom(50)
    , m_xoffsetAcumulado(0)
    , m_yoffsetAcumulado(0)
    , m_clicked(false)
    , m_animado(false)
    , m_embaldosado(false)
    , m_filas(5)
    , m_columnas(5)
    , m_animacionStep(0)
    , m_timer(new QTimer(this))
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    m_timer->setInterval(100);
    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(dibuja()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

Hipotrocoide::~Hipotrocoide()
{
    makeCurrent();
}

void Hipotrocoide::setZoom(int zoom)
{
    m_zoom = 100.0 - zoom;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::arriba()
{
    m_yoffsetAcumulado += 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::abajo()
{
    m_yoffsetAcumulado -= 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::izquierda()
{
    m_xoffsetAcumulado -= 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::derecha()
{
    m_xoffsetAcumulado += 100 * m_zoom / 100.0;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::centrar()
{
    m_xoffsetAcumulado = 0;
    m_yoffsetAcumulado = 0;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::sa(int a)
{
    m_a = a;
    m_animacionStep = 0;
    if (m_animado && !m_timer->isActive()) {
        m_timer->start();
    } else {
        update();
    }
}

void Hipotrocoide::sb(int b)
{
    m_b = b;
    m_animacionStep = 0;
    if (m_animado && !m_timer->isActive()) {
        m_timer->start();
    } else {
        update();
    }
}

void Hipotrocoide::sc(int c)
{
    m_c = c;
    m_animacionStep = 0;
    if (m_animado && !m_timer->isActive()) {
        m_timer->start();
    } else {
        update();
    }
}

void Hipotrocoide::sprecision(int precision)
{
    m_precision = precision;
    m_animacionStep = 0;
    if (m_animado && !m_timer->isActive()) {
        m_timer->start();
    } else {
        update();
    }
}

void Hipotrocoide::sanimado(bool animado)
{
    m_animado = animado;
    m_animacionStep = 0;
    if (animado) {
        m_timer->start();
    } else {
        m_timer->stop();
        update();
    }
}

void Hipotrocoide::sembaldosado(bool embaldosado)
{
    m_embaldosado = embaldosado;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::sfilas(int filas)
{
    m_filas = filas;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::scolumnas(int columnas)
{
    m_columnas = columnas;
    resizeGL(m_width, m_height);
    update();
}

void Hipotrocoide::dibuja()
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
    if (m_embaldosado) {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        GLint viewportWidth = m_width / m_columnas;
        GLint viewportHeight = m_height / m_filas;
        GLint x = 0;
        GLint y = 0;
        for (int i = 0; i < m_filas; ++i) {
            for (int j = 0; j < m_columnas; ++j) {
                glViewport(x, y, viewportWidth, viewportHeight);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(left * m_zoom + m_xoffsetAcumulado / 2.0, right * m_zoom + m_xoffsetAcumulado / 2.0,
                        bottom * m_zoom + m_yoffsetAcumulado / 2.0, top * m_zoom + m_yoffsetAcumulado / 2.0, -1.0, 1.0);
                glMatrixMode(GL_MODELVIEW);
                realizaDibujo();
                x += viewportWidth;
            }
            x = 0;
            y += viewportHeight;
        }
    } else {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, m_width, m_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left * m_zoom + m_xoffsetAcumulado / 2.0, right * m_zoom + m_xoffsetAcumulado / 2.0,
                bottom * m_zoom + m_yoffsetAcumulado / 2.0, top * m_zoom + m_yoffsetAcumulado / 2.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        realizaDibujo();
    }
    if (m_animado && m_animacionStep < m_precision) {
        ++m_animacionStep;
    } else if (m_animado) {
        m_timer->stop();
    }
}

QSize Hipotrocoide::sizeHint() const
{
    return QSize(640, 480);
}

void Hipotrocoide::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        emit zoomIn();
    } else {
        emit zoomOut();
    }
    event->accept();
}

void Hipotrocoide::keyPressEvent(QKeyEvent *event)
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

void Hipotrocoide::mousePressEvent(QMouseEvent *event)
{
    m_clicked = true;
}

void Hipotrocoide::mouseReleaseEvent(QMouseEvent *event)
{
    m_clicked = false;
}

void Hipotrocoide::mouseMoveEvent(QMouseEvent *event)
{
    if (m_clicked) {
        QPointF res = event->posF() - m_oldPos;
        res.rx() *= m_ratio * (m_zoom / 100.0);
        res.ry() *= m_ratio * (m_zoom / 100.0);
        m_xoffsetAcumulado += res.x();
        m_yoffsetAcumulado -= res.y();
        resizeGL(m_width, m_height);
        update();
    }
    m_oldPos = event->posF();
    event->accept();
}

void Hipotrocoide::initializeGL()
{
    srandom(time(0));
    m_stepColor.r = random() % 256;
    m_stepColor.g = random() % 256;
    m_stepColor.b = random() % 256;
    m_colorInicial.r = random() % 256;
    m_colorInicial.g = random() % 256;
    m_colorInicial.b = random() % 256;
    glPointSize(3);
}

void Hipotrocoide::paintGL()
{
    if (!m_animado || !m_timer->isActive()) {
        dibuja();
    }
}

void Hipotrocoide::resizeGL(int width, int height)
{
    m_ratio = (m_embaldosado ? ((GLfloat) width / (GLfloat) m_columnas) / ((GLfloat) height / (GLfloat) m_filas)
                             : (GLfloat) width / (GLfloat) height);
    m_width = width;
    m_height = height;
}

void Hipotrocoide::realizaDibujo()
{
    const int numVueltas = (m_b / boost::math::gcd(m_a, m_b)) * (m_animado ? m_animacionStep : m_precision);
    const GLdouble stepSize = 2.0 * M_PI / m_precision;
    GLdouble currStepSize = 0;
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2i(0, 0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    Color c;
    c.r = m_colorInicial.r;
    c.g = m_colorInicial.g;
    c.b = m_colorInicial.b;
    glColor3ub(c.r, c.g, c.b);
    int numAristas = 0;
    for (int i = 0; i <= numVueltas; ++i) {
        glVertex2f((m_a - m_b) * cos(currStepSize) + m_c * cos(currStepSize * (m_a - m_b) / m_b),
                   (m_a - m_b) * sin(currStepSize) - m_c * sin(currStepSize * (m_a - m_b) / m_b));
        currStepSize += stepSize;
        if (numAristas == ((m_b / boost::math::gcd(m_a, m_b)) * m_precision / 255)) {
            numAristas = 0;
            c.r = c.r + m_stepColor.r % 256;
            c.g = c.g + m_stepColor.g % 256;
            c.b = c.b + m_stepColor.b % 256;
            glColor3ub(c.r, c.g, c.b);
        } else {
            ++numAristas;
        }
    }
    glEnd();
}

#include "hipotrocoide.moc"

