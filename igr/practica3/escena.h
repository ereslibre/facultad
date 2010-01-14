#ifndef ESCENA_H
#define ESCENA_H

#include <QtCore/QList>
#include <QtCore/QStack>
#include <QtOpenGL/QGLWidget>
#include "lapiz.h"

class DibujoLineas;

class Escena
    : public QGLWidget
{
public:
    Escena(QWidget *parent = 0);
    ~Escena();

    virtual QSize sizeHint() const;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    void dibujaVectores();

    GLfloat     m_width;
    GLfloat     m_height;
    GLfloat     m_ratio;
    Lapiz       m_lapiz;
    QList<PV2f> m_listaVectores;
};

#endif

