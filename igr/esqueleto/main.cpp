#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>

class Test
    : public QGLWidget
{
public:
    Test(QWidget *parent = 0);
    ~Test();

    virtual QSize sizeHint() const;

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
};

Test::Test(QWidget *parent)
    : QGLWidget(parent)
{
}

Test::~Test()
{
    makeCurrent();
}

QSize Test::sizeHint() const
{
    return QSize(640, 480);
}

void Test::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
}

void Test::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(100, 100);
    glVertex2f(200, 200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(440, 100);
    glVertex2f(340, 250);
    glVertex2f(540, 250);
    glEnd();
}

void Test::resizeGL(int width, int height)
{
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Test test;
    test.show();
    return app.exec();
}
