#include "hipotrocoide.h"

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

#include <math.h>

#include <boost/math/common_factor.hpp>

class Hipotrocoide::ConfigWidget
    : public QWidget
{
public:
    ConfigWidget();

    QLineEdit *a() const;
    QLineEdit *b() const;
    QLineEdit *c() const;
    QLineEdit *precision() const;

private:
    QLineEdit *m_a;
    QLineEdit *m_b;
    QLineEdit *m_c;
    QLineEdit *m_precision;
};

QLineEdit *Hipotrocoide::ConfigWidget::a() const
{
    return m_a;
}

QLineEdit *Hipotrocoide::ConfigWidget::b() const
{
    return m_b;
}

QLineEdit *Hipotrocoide::ConfigWidget::c() const
{
    return m_c;
}

QLineEdit *Hipotrocoide::ConfigWidget::precision() const
{
    return m_precision;
}

Hipotrocoide::ConfigWidget::ConfigWidget()
    : m_a(new QLineEdit(this))
    , m_b(new QLineEdit(this))
    , m_c(new QLineEdit(this))
    , m_precision(new QLineEdit(this))
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("a", this), 0, 0);
    layout->addWidget(new QLabel("b", this), 1, 0);
    layout->addWidget(new QLabel("c", this), 2, 0);
    layout->addWidget(new QLabel("Precision", this), 3, 0);
    m_a->setText("300");
    m_b->setText("280");
    m_c->setText("50");
    m_precision->setText("500");
    layout->addWidget(m_a, 0, 1);
    layout->addWidget(m_b, 1, 1);
    layout->addWidget(m_c, 2, 1);
    layout->addWidget(m_precision, 3, 1);
    setLayout(layout);
}

Hipotrocoide::Hipotrocoide(Lapiz &l, const PV2f &centro, uint a, uint b, uint c, uint precision)
    : DibujoLineas(l, centro)
    , m_a(a)
    , m_b(b)
    , m_c(c)
    , m_precision(precision)
    , m_configWidget(0)
{
    calculaSegmentos();
}

QString Hipotrocoide::getNombre() const
{
    return "Hipotrocoide";
}

void Hipotrocoide::dibuja(Estado estado) const
{
    if (estado & Seleccionado) {
        glColor3f(1.0, 1.0, 0);
    } else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glBegin(GL_LINES);
    QList<Segmento>::ConstIterator it = m_listaSegmentos.begin();
    while (it != m_listaSegmentos.end()) {
        const Segmento segmento = *it;
        glVertex2d(segmento.getA().getX(), segmento.getA().getY());
        glVertex2d(segmento.getB().getX(), segmento.getB().getY());
        ++it;
    }
    glEnd();
}

QWidget *Hipotrocoide::configWidget()
{
    if (m_configWidget) {
        return m_configWidget;
    }
    m_configWidget = new ConfigWidget;
    connect(m_configWidget->a(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->b(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->c(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->precision(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    return m_configWidget;
}

void Hipotrocoide::invalidar()
{
    m_a = m_configWidget->a()->text().toInt();
    m_b = m_configWidget->b()->text().toInt();
    m_c = m_configWidget->c()->text().toInt();
    m_precision = m_configWidget->precision()->text().toInt();
    calculaSegmentos();
    DibujoLineas::invalidar();
}

void Hipotrocoide::calculaSegmentos()
{
    m_listaSegmentos.clear();
    const int numVueltas = (m_b / boost::math::gcd(m_a, m_b)) * m_precision;
    const GLdouble stepSize = 2.0 * M_PI / m_precision;
    GLdouble currStepSize = 0;
    PV2f pa((m_a - m_b) * cos(currStepSize) + m_c * cos(currStepSize * (m_a - m_b) / m_b) + m_centro.getX(),
            (m_a - m_b) * sin(currStepSize) - m_c * sin(currStepSize * (m_a - m_b) / m_b) + m_centro.getY());
    for (int i = 0; i <= numVueltas; ++i) {
        currStepSize += stepSize;
        const PV2f pb((m_a - m_b) * cos(currStepSize) + m_c * cos(currStepSize * (m_a - m_b) / m_b) + m_centro.getX(),
                      (m_a - m_b) * sin(currStepSize) - m_c * sin(currStepSize * (m_a - m_b) / m_b) + m_centro.getY());
        m_listaSegmentos << Segmento(pa, pb);
        pa = pb;
    }
}
