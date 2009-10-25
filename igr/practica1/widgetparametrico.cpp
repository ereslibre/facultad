#include "widgetparametrico.h"

#include <QtGui/QGridLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>

WidgetParametrico::WidgetParametrico(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel("a", this), 0, 0);
    layout->addWidget(new QLabel("b", this), 1, 0);
    layout->addWidget(new QLabel("c", this), 2, 0);
    layout->addWidget(new QLabel("Precision", this), 3, 0);
    QLineEdit *a = new QLineEdit(this);
    a->setText("300");
    QLineEdit *b = new QLineEdit(this);
    b->setText("280");
    QLineEdit *c = new QLineEdit(this);
    c->setText("50");
    QLineEdit *precision = new QLineEdit(this);
    precision->setText("500");
    layout->addWidget(a, 0, 1);
    layout->addWidget(b, 1, 1);
    layout->addWidget(c, 2, 1);
    layout->addWidget(precision, 3, 1);
    QCheckBox *animado = new QCheckBox("Animado", this);
    layout->addWidget(animado, 4, 1);
    QCheckBox *embaldosado = new QCheckBox("Embaldosado", this);
    m_filasLabel = new QLabel("Filas", this);
    m_filas = new QLineEdit(this);
    m_columnasLabel = new QLabel("Columnas", this);
    m_columnas = new QLineEdit(this);
    m_filas->setText("5");
    m_columnas->setText("5");
    m_filasLabel->setEnabled(false);
    m_filas->setEnabled(false);
    m_columnasLabel->setEnabled(false);
    m_columnas->setEnabled(false);
    QGridLayout *embaldosadoLayout = new QGridLayout;
    embaldosadoLayout->addWidget(embaldosado, 0, 0);
    embaldosadoLayout->addWidget(m_filasLabel, 0, 1);
    embaldosadoLayout->addWidget(m_columnasLabel, 1, 1);
    embaldosadoLayout->addWidget(m_filas, 0, 2);
    embaldosadoLayout->addWidget(m_columnas, 1, 2);
    layout->addLayout(embaldosadoLayout, 5, 1);
    setLayout(layout);
    connect(a, SIGNAL(textEdited(const QString&)), this, SLOT(sa(const QString &)));
    connect(b, SIGNAL(textEdited(const QString&)), this, SLOT(sb(const QString &)));
    connect(c, SIGNAL(textEdited(const QString&)), this, SLOT(sc(const QString &)));
    connect(precision, SIGNAL(textEdited(const QString&)), this, SLOT(sprecision(const QString &)));
    connect(animado, SIGNAL(stateChanged(int)), this, SLOT(sanimado(int)));
    connect(embaldosado, SIGNAL(stateChanged(int)), this, SLOT(sembaldosado(int)));
    connect(m_filas, SIGNAL(textEdited(const QString&)), this, SLOT(sfilas(const QString &)));
    connect(m_columnas, SIGNAL(textEdited(const QString &)), this, SLOT(scolumnas(const QString &)));
}

WidgetParametrico::~WidgetParametrico()
{
}

void WidgetParametrico::sa(const QString &a)
{
    emit this->a(a.toInt());
}

void WidgetParametrico::sb(const QString &b)
{
    emit this->b(b.toInt());
}

void WidgetParametrico::sc(const QString &c)
{
    emit this->c(c.toInt());
}

void WidgetParametrico::sprecision(const QString &precision)
{
    emit this->precision(precision.toInt());
}

void WidgetParametrico::sanimado(int state)
{
    emit animado(state == Qt::Checked);
}

void WidgetParametrico::sembaldosado(int state)
{
    emit embaldosado(state == Qt::Checked);
    m_filasLabel->setEnabled(state == Qt::Checked);
    m_filas->setEnabled(state == Qt::Checked);
    m_columnasLabel->setEnabled(state == Qt::Checked);
    m_columnas->setEnabled(state == Qt::Checked);
}

void WidgetParametrico::sfilas(const QString &filas)
{
    emit this->filas(filas.toInt());
}

void WidgetParametrico::scolumnas(const QString &columnas)
{
    emit this->columnas(columnas.toInt());
}

#include "widgetparametrico.moc"

