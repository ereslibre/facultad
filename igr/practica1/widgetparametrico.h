#ifndef WIDGETPARAMETRICO_H
#define WIDGETPARAMETRICO_H

#include <QtGui/QWidget>

class QLabel;
class QLineEdit;

class WidgetParametrico
    : public QWidget
{
    Q_OBJECT

public:
    WidgetParametrico(QWidget *parent = 0);
    ~WidgetParametrico();

public Q_SLOTS:
    void sa(const QString &a);
    void sb(const QString &b);
    void sc(const QString &c);
    void sprecision(const QString &precision);
    void sanimado(int state);
    void sembaldosado(int state);
    void sfilas(const QString &filas);
    void scolumnas(const QString &columnas);

Q_SIGNALS:
    void a(int a);
    void b(int b);
    void c(int c);
    void precision(int precision);
    void animado(bool animado);
    void embaldosado(bool embaldosado);
    void filas(int filas);
    void columnas(int columnas);

private:
    QLabel *m_filasLabel;
    QLineEdit *m_filas;
    QLabel *m_columnasLabel;
    QLineEdit *m_columnas;
};

#endif

