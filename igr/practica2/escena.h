#ifndef ESCENA_H
#define ESCENA_H

#include <QtCore/QList>
#include <QtCore/QStack>
#include <QtOpenGL/QGLWidget>
#include "lapiz.h"

class DibujoLineas;
class DibujoManual;

class Escena
    : public QGLWidget
{
    Q_OBJECT

public:
    Escena(QWidget *parent = 0);
    ~Escena();

    virtual QSize sizeHint() const;

public Q_SLOTS:
    void setZoom(int zoom);
    void arriba();
    void abajo();
    void izquierda();
    void derecha();
    void centrar();
    void cambioHerramienta(uint herramienta);

    void nuevo();
    void abrir();
    void guardar();
    void guardarComo();
    void salir();
    void deshacer();
    void copiar();
    void cortar();
    void pegar();

Q_SIGNALS:
    void zoomIn();
    void zoomOut();
    void elementosSeleccionados(const QList<DibujoLineas*> &seleccion);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    enum Estado {
        Idle = 0,
        CreandoDibujo,
        Recortando,
        Arrastrando
    };

    enum EstadoParser {
        PTipo = 0,
        PNumSegmentos,
        PSegmento,
        PAtributos
    };

    enum SiguienteFigura {
        SManual = 0,
        SPoliEspiral,
        SPoliRegular,
        SHipotrocoide
    };

    void guardaEstadoParaDeshacer();
    void borrar();
    QPointF mapeaPVaAVE(const QPoint &p);

    GLfloat              m_width;
    GLfloat              m_height;
    GLfloat              m_ratio;
    GLfloat              m_zoom;
    GLfloat              m_xoffsetAcumulado;
    GLfloat              m_yoffsetAcumulado;
    QPointF              m_oldPos;
    QList<DibujoLineas*> m_listaDibujoLineas;
    DibujoManual        *m_dibujoManualAct;
    QPointF              m_ultimoClick;
    QPointF              m_posActual;
    Lapiz                m_lapiz;
    uint                 m_herramienta;
    Estado               m_estado;
    QList<DibujoLineas*> m_listaSeleccion;
    bool                 m_escenaModificada;
    QString              m_guardarRuta;

    QList<DibujoLineas*> m_bufferCopia;
    QStack<QList<DibujoLineas*> > m_bufferDeshacer;

    QAction *m_nuevo;
    QAction *m_abrir;
    QAction *m_guardar;
    QAction *m_guardarComo;
    QAction *m_salir;

    QAction *m_deshacer;
    QAction *m_copiar;
    QAction *m_cortar;
    QAction *m_pegar;
};

#endif

