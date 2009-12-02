#include "poliespiral.h"

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

class PoliEspiral::ConfigWidget
    : public QWidget
{
public:
    ConfigWidget(uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado);

    QLineEdit *nPasos() const;
    QLineEdit *incLado() const;
    QLineEdit *incDir() const;
    QLineEdit *lado() const;

private:
    QLineEdit *m_nPasos;
    QLineEdit *m_incLado;
    QLineEdit *m_incDir;
    QLineEdit *m_lado;
};

QLineEdit *PoliEspiral::ConfigWidget::nPasos() const
{
    return m_nPasos;
}

QLineEdit *PoliEspiral::ConfigWidget::incLado() const
{
    return m_incLado;
}

QLineEdit *PoliEspiral::ConfigWidget::incDir() const
{
    return m_incDir;
}

QLineEdit *PoliEspiral::ConfigWidget::lado() const
{
    return m_lado;
}

PoliEspiral::ConfigWidget::ConfigWidget(uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado)
    : m_nPasos(new QLineEdit(this))
    , m_incLado(new QLineEdit(this))
    , m_incDir(new QLineEdit(this))
    , m_lado(new QLineEdit(this))
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("Pasos", this), 0, 0);
    layout->addWidget(new QLabel("Inc. Lado", this), 1, 0);
    layout->addWidget(new QLabel("Inc. Dir", this), 2, 0);
    layout->addWidget(new QLabel("Lado", this), 3, 0);
    m_nPasos->setText(QString::number(nPasos));
    m_incLado->setText(QString::number(incLado));
    m_incDir->setText(QString::number(incDir));
    m_lado->setText(QString::number(lado));
    layout->addWidget(m_nPasos, 0, 1);
    layout->addWidget(m_incLado, 1, 1);
    layout->addWidget(m_incDir, 2, 1);
    layout->addWidget(m_lado, 3, 1);
    setLayout(layout);
}

PoliEspiral::PoliEspiral(Lapiz &l, const PV2f &centro, uint nPasos, GLfloat incLado, GLfloat incDir, GLfloat lado)
    : DibujoLineas(l, centro)
    , m_nPasos(nPasos)
    , m_incLado(incLado)
    , m_incDir(incDir)
    , m_lado(lado)
    , m_configWidget(0)
{
    calculaSegmentos();
}

QString PoliEspiral::getNombre() const
{
    return "Poli-espiral";
}

DibujoLineas *PoliEspiral::clonar() const
{
    return new PoliEspiral(m_l, m_centro, m_nPasos, m_incLado, m_incDir, m_lado);
}

QWidget *PoliEspiral::configWidget()
{
    if (m_configWidget) {
        return m_configWidget;
    }
    m_configWidget = new ConfigWidget(m_nPasos, m_incLado, m_incDir, m_lado);
    connect(m_configWidget->nPasos(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->incLado(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->incDir(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    connect(m_configWidget->lado(), SIGNAL(textEdited(QString)), this, SLOT(invalidar()));
    return m_configWidget;
}

void PoliEspiral::salva(QTextStream &stream) const
{
    stream << "PoliEspiral\n";
    stream << QString::number(m_centro.getX()) << ',' << QString::number(m_centro.getY()) << '\n';
    stream << QString::number(m_nPasos) << ',' << QString::number(m_incLado) << ',' <<
              QString::number(m_incDir) << ',' << QString::number(m_lado) << '\n';
}

void PoliEspiral::invalidar()
{
    m_nPasos = m_configWidget->nPasos()->text().toInt();
    m_incLado = m_configWidget->incLado()->text().toFloat();
    m_incDir = m_configWidget->incDir()->text().toFloat();
    m_lado = m_configWidget->lado()->text().toFloat();
    calculaSegmentos();
    DibujoLineas::invalidar();
}

void PoliEspiral::calculaSegmentos()
{
    m_listaSegmentos.clear();
    m_l.salvaEstado();
    m_l.setPos(m_centro);
    PV2f a = m_centro;
    GLfloat lado = m_lado;
    for (uint i = 0; i < m_nPasos; ++i) {
        m_l.avanzar(lado, Lapiz::NoDejarRastro);
        m_listaSegmentos << Segmento(a, m_l.getPos());
        a = m_l.getPos();
        lado += m_incLado;
        m_l.girar(m_incDir);
    }
    m_l.recuperaEstado();
}
