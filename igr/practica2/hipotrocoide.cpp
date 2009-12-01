#include "hipotrocoide.h"

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

#include <math.h>

#include <boost/math/common_factor.hpp>

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
    m_configWidget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("a", m_configWidget), 0, 0);
    layout->addWidget(new QLabel("b", m_configWidget), 1, 0);
    layout->addWidget(new QLabel("c", m_configWidget), 2, 0);
    layout->addWidget(new QLabel("Precision", m_configWidget), 3, 0);
    QLineEdit *a = new QLineEdit(m_configWidget);
    a->setText("300");
    QLineEdit *b = new QLineEdit(m_configWidget);
    b->setText("280");
    QLineEdit *c = new QLineEdit(m_configWidget);
    c->setText("50");
    QLineEdit *precision = new QLineEdit(m_configWidget);
    precision->setText("500");
    layout->addWidget(a, 0, 1);
    layout->addWidget(b, 1, 1);
    layout->addWidget(c, 2, 1);
    layout->addWidget(precision, 3, 1);
    m_configWidget->setLayout(layout);
    connect(a, SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(b, SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(c, SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(precision, SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    return m_configWidget;
}

void Hipotrocoide::invalidar()
{
    calculaSegmentos();
}

void Hipotrocoide::calculaSegmentos()
{
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
