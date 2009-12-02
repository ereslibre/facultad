#include "poligonoregular.h"

#include <math.h>

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

class PoligonoRegular::ConfigWidget
    : public QWidget
{
public:
    ConfigWidget(GLfloat lado, int nLados);

    QLineEdit *lado() const;
    QLineEdit *nLados() const;

private:
    QLineEdit *m_lado;
    QLineEdit *m_nLados;
};

QLineEdit *PoligonoRegular::ConfigWidget::lado() const
{
    return m_lado;
}

QLineEdit *PoligonoRegular::ConfigWidget::nLados() const
{
    return m_nLados;
}

PoligonoRegular::ConfigWidget::ConfigWidget(GLfloat lado, int nLados)
    : m_lado(new QLineEdit(this))
    , m_nLados(new QLineEdit(this))
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("Lado", this), 0, 0);
    layout->addWidget(new QLabel("Num. Lados", this), 1, 0);
    m_lado->setText(QString::number(lado));
    m_nLados->setText(QString::number(nLados));
    layout->addWidget(m_lado, 0, 1);
    layout->addWidget(m_nLados, 1, 1);
    setLayout(layout);
}

PoligonoRegular::PoligonoRegular(Lapiz &l, const PV2f &centro, GLfloat lado, int nLados)
    : DibujoLineas(l, centro)
    , m_lado(lado)
    , m_nLados(nLados)
    , m_configWidget(0)
{
    calculaSegmentos();
}

QString PoligonoRegular::getNombre() const
{
    return "Poligono Regular";
}

DibujoLineas *PoligonoRegular::clonar() const
{
    return new PoligonoRegular(m_l, m_centro, m_lado, m_nLados);
}

QWidget *PoligonoRegular::configWidget()
{
    if (m_configWidget) {
        return m_configWidget;
    }
    m_configWidget = new ConfigWidget(m_lado, m_nLados);
    connect(m_configWidget->lado(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->nLados(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    return m_configWidget;
}

void PoligonoRegular::salva(QTextStream &stream) const
{
    stream << "PoligonoRegular\n";
    stream << QString::number(m_centro.getX()) << ',' << QString::number(m_centro.getY()) << '\n';
    stream << QString::number(m_lado) << ',' << QString::number(m_nLados) << '\n';
}

void PoligonoRegular::invalidar()
{
    m_lado = m_configWidget->lado()->text().toFloat();
    m_nLados = m_configWidget->nLados()->text().toInt();
    calculaSegmentos();
    DibujoLineas::invalidar();
}

void PoligonoRegular::calculaSegmentos()
{
    m_listaSegmentos.clear();
    m_l.salvaEstado();
    m_l.setPos(m_centro);
    const GLfloat alpha = 2.0 * M_PI / (GLfloat) m_nLados;
    const GLfloat beta = (M_PI - alpha) / 2;
    const GLfloat radio = (m_lado / 2.0) / sin(alpha / 2.0);
    const GLfloat gamma = M_PI - beta;
    m_l.avanzar(radio, Lapiz::NoDejarRastro);
    PV2f a = m_l.getPos();
    m_l.girar(gamma);
    for (int i = 0; i < m_nLados; ++i) {
        m_l.avanzar(m_lado, Lapiz::NoDejarRastro);
        m_listaSegmentos << Segmento(a, m_l.getPos());
        a = m_l.getPos();
        m_l.girar(alpha);
    }
    m_l.recuperaEstado();
}
