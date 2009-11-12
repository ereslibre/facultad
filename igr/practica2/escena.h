#ifndef ESCENA_H
#define ESCENA_H

#include <QtCore/QList>
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

Q_SIGNALS:
    void zoomIn();
    void zoomOut();

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    enum Estado {
        Idle = 0,
        CreandoDibujo
    };

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
    Lapiz                m_lapiz;
    uint                 m_herramienta;
    Estado               m_estado;
};

#endif

