#ifndef HIPOTROCOIDE_H
#define HIPOTROCOIDE_H

#include <QtOpenGL/QGLWidget>

class Hipotrocoide
    : public QGLWidget
{
    Q_OBJECT

public:
    Hipotrocoide(QWidget *parent = 0);
    ~Hipotrocoide();

    virtual QSize sizeHint() const;

public Q_SLOTS:
    void setZoom(int zoom);
    void arriba();
    void abajo();
    void izquierda();
    void derecha();
    void centrar();
    void sa(int a);
    void sb(int b);
    void sc(int c);
    void sprecision(int precision);
    void sanimado(bool animado);
    void sembaldosado(bool embaldosado);
    void sfilas(int filas);
    void scolumnas(int columnas);
    void dibuja();

Q_SIGNALS:
    void zoomIn();
    void zoomOut();

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    void realizaDibujo();

    struct Color {
        Color()
            : r(0)
            , g(0)
            , b(0)
        {
        }

        GLint r;
        GLint g;
        GLint b;
    };

    GLint        m_a;
    GLint        m_b;
    GLint        m_c;
    GLint        m_precision;
    GLfloat      m_width;
    GLfloat      m_height;
    GLfloat      m_ratio;
    GLfloat      m_zoom;
    GLfloat      m_xoffsetAcumulado;
    GLfloat      m_yoffsetAcumulado;
    QPointF      m_oldPos;
    bool         m_clicked;
    bool         m_animado;
    bool         m_embaldosado;
    int          m_filas;
    int          m_columnas;
    unsigned int m_animacionStep;
    Color        m_stepColor;
    Color        m_colorInicial;
    QTimer      *m_timer;
};

#endif

