#include "escena.h"

#include "dibujomanual.h"
#include "poliespiral.h"
#include "poligonoregular.h"
#include "hipotrocoide.h"
#include "herramientas.h"

#include <QtGui/QMainWindow>
#include <QtGui/QWheelEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>

#include <math.h>

Escena::Escena(QWidget *parent)
    : QGLWidget(parent)
    , m_zoom(50)
    , m_xoffsetAcumulado(0)
    , m_yoffsetAcumulado(0)
    , m_dibujoManualAct(0)
    , m_herramienta(Herramientas::Ninguna)
    , m_estado(Idle)
    , m_escenaModificada(false)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QMainWindow *const v = qobject_cast<QMainWindow*>(parentWidget());
    QMenu *const archivo = v->menuBar()->addMenu("&Archivo");
    m_nuevo = new QAction("&Nuevo", archivo);
    m_abrir = new QAction("&Abrir...", archivo);
    m_guardar = new QAction("&Guardar", archivo);
    m_guardar->setEnabled(false);
    m_guardarComo = new QAction("Guardar &como...", archivo);
    m_salir = new QAction("&Salir...", archivo);
    archivo->addAction(m_nuevo);
    archivo->addSeparator();
    archivo->addAction(m_abrir);
    archivo->addAction(m_guardar);
    archivo->addAction(m_guardarComo);
    archivo->addSeparator();
    archivo->addAction(m_salir);
    QMenu *const editar = v->menuBar()->addMenu("&Editar");
    m_deshacer = new QAction("&Deshacer", editar);
    m_deshacer->setEnabled(false);
    m_copiar = new QAction("&Copiar", editar);
    m_copiar->setEnabled(false);
    m_cortar = new QAction("Cor&tar", editar);
    m_cortar->setEnabled(false);
    m_pegar = new QAction("&Pegar", editar);
    m_pegar->setEnabled(false);
    editar->addAction(m_deshacer);
    editar->addSeparator();
    editar->addAction(m_copiar);
    editar->addAction(m_cortar);
    editar->addAction(m_pegar);
    QObject::connect(m_nuevo, SIGNAL(triggered(bool)), this, SLOT(nuevo()));
    QObject::connect(m_abrir, SIGNAL(triggered(bool)), this, SLOT(abrir()));
    QObject::connect(m_guardar, SIGNAL(triggered(bool)), this, SLOT(guardar()));
    QObject::connect(m_guardarComo, SIGNAL(triggered(bool)), this, SLOT(guardarComo()));
    QObject::connect(m_salir, SIGNAL(triggered(bool)), this, SLOT(salir()));
    QObject::connect(m_deshacer, SIGNAL(triggered(bool)), this, SLOT(deshacer()));
    QObject::connect(m_copiar, SIGNAL(triggered(bool)), this, SLOT(copiar()));
    QObject::connect(m_cortar, SIGNAL(triggered(bool)), this, SLOT(cortar()));
    QObject::connect(m_pegar, SIGNAL(triggered(bool)), this, SLOT(pegar()));
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

void Escena::nuevo()
{
    if (m_escenaModificada) {
        if (QMessageBox::question(this, "Nuevo", "Seguro que quieres comenzar un nuevo documento?", QMessageBox::Yes |
                                                                                                    QMessageBox::No) == QMessageBox::No) {
            return;
        }
    }
    m_oldPos = QPointF();
    m_listaDibujoLineas.clear();
    m_dibujoManualAct = 0;
    m_ultimoClick = QPointF();
    m_posActual = QPointF();
    m_estado = Idle;
    m_listaSeleccion.clear();
    m_escenaModificada = false;
    emit elementosSeleccionados(QList<DibujoLineas*>());
    update();
}

void Escena::abrir()
{
}

void Escena::guardar()
{
}

void Escena::guardarComo()
{
}

void Escena::salir()
{
}

void Escena::deshacer()
{
}

void Escena::copiar()
{
}

void Escena::cortar()
{
}

void Escena::pegar()
{
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
        case Qt::Key_Delete:
            borrar();
            emit elementosSeleccionados(m_listaSeleccion);
            break;
        default:
            event->ignore();
            return;
    }
    event->accept();
    update();
}

void Escena::mousePressEvent(QMouseEvent *event)
{
    const QPointF posClick = mapeaPVaAVE(event->pos());
    DibujoLineas *dibujoLineas = 0;
    if (m_herramienta == Herramientas::Ninguna) {
        if (!(event->modifiers() & Qt::ControlModifier)) {
            m_listaSeleccion.clear();
        }
        QList<DibujoLineas*>::ConstIterator it = m_listaDibujoLineas.begin();
        while (it != m_listaDibujoLineas.end()) {
            DibujoLineas *const dibujoLineas = *it;
            if (dibujoLineas->clickSobreFigura(PV2f(posClick.x(), posClick.y()))) {
                if ((event->modifiers() & Qt::ControlModifier) && m_listaSeleccion.contains(dibujoLineas)) {
                    m_listaSeleccion.removeAll(dibujoLineas);
                } else {
                    m_listaSeleccion << dibujoLineas;
                }
                return;
            }
            ++it;
        }
    } else if (m_herramienta == Herramientas::Recortar) {
        if (m_estado == Idle) {
            m_estado = Recortando;
            m_ultimoClick = posClick;
            m_posActual = posClick;
        }
    } else if (m_herramienta == Herramientas::Manual) {
        if (!m_dibujoManualAct) {
            m_dibujoManualAct = new DibujoManual(m_lapiz);
            dibujoLineas = m_dibujoManualAct;
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
        dibujoLineas = new PoliEspiral(m_lapiz, PV2f(posClick.x(), posClick.y()), 10, 2, M_PI / 4.0, 5);
    } else if (m_herramienta == Herramientas::PoliRegular) {
        dibujoLineas = new PoligonoRegular(m_lapiz, PV2f(posClick.x(), posClick.y()), 20, 6);
    } else if (m_herramienta == Herramientas::Hipotrocoide) {
        dibujoLineas = new Hipotrocoide(m_lapiz, PV2f(posClick.x(), posClick.y()), 300, 280, 50, 500);
    }
    if (dibujoLineas) {
        m_listaDibujoLineas << dibujoLineas;
        m_escenaModificada = true;
        connect(dibujoLineas, SIGNAL(invalidada()), this, SLOT(update()));
    }
}

void Escena::mouseMoveEvent(QMouseEvent *event)
{
    if (m_herramienta == Herramientas::Recortar && m_estado == Recortando) {
        m_posActual = mapeaPVaAVE(event->pos());
        update();
    }
}

void Escena::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_herramienta == Herramientas::Recortar) {
        const QRectF ventana(m_ultimoClick, m_posActual);
        const QRectF ventanaNormalizada = ventana.normalized();
        QList<DibujoLineas*>::ConstIterator it = m_listaDibujoLineas.begin();
        while (it != m_listaDibujoLineas.end()) {
            DibujoLineas *const dibujoLineas = *it;
            dibujoLineas->cohenSutherland(PV2f(ventanaNormalizada.topLeft().x(),
                                               ventanaNormalizada.topLeft().y()),
                                          PV2f(ventanaNormalizada.bottomRight().x(),
                                               ventanaNormalizada.bottomRight().y()));
            ++it;
        }
        m_estado = Idle;
        m_ultimoClick = QPointF();
        m_posActual = QPointF();
    }
    emit elementosSeleccionados(m_listaSeleccion);
    update();
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
        if (m_listaSeleccion.contains(dibujoLineas)) {
            dibujoLineas->dibuja(DibujoLineas::Seleccionado);
        } else {
            dibujoLineas->dibuja();
        }
        m_lapiz.recuperaEstado();
        ++it;
    }
    if (m_herramienta == Herramientas::Recortar && m_estado == Recortando) {
        const GLfloat minx = qMin(m_ultimoClick.x(), m_posActual.x());
        const GLfloat miny = qMin(m_ultimoClick.y(), m_posActual.y());
        const GLfloat maxx = qMax(m_ultimoClick.x(), m_posActual.x());
        const GLfloat maxy = qMax(m_ultimoClick.y(), m_posActual.y());
        glBegin(GL_LINE_STRIP);
        glVertex2d(minx, miny);
        glVertex2d(minx, maxy);
        glVertex2d(maxx, maxy);
        glVertex2d(maxx, miny);
        glVertex2d(minx, miny);
        glEnd();
    }
}

void Escena::resizeGL(int width, int height)
{
    m_ratio = (GLfloat) width / (GLfloat) height;
    m_width = width;
    m_height = height;
}

void Escena::borrar()
{
    QList<DibujoLineas*>::ConstIterator it = m_listaSeleccion.begin();
    while (it != m_listaSeleccion.end()) {
        DibujoLineas *const dibujoLineas = *it;
        m_listaDibujoLineas.removeAll(dibujoLineas);
        delete dibujoLineas;
        ++it;
    }
    m_listaSeleccion.clear();
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
