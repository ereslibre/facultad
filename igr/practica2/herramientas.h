#ifndef HERRAMIENTAS_H
#define HERRAMIENTAS_H

#include <QtGui/QWidget>

class QPushButton;

class Herramientas
    : public QWidget
{
    Q_OBJECT

public:
    Herramientas(QWidget *parent = 0);
    ~Herramientas();

    enum Herramienta {
        Ninguna = 0,
        Manual,
        PoliEspiral,
        PoliRegular,
        Roseta,
        Estrella,
        PoliArco,
        Arco,
        Circunferencia,
        Hipotrocoide
    };

Q_SIGNALS:
    void cambioHerramienta(uint herramienta);

private Q_SLOTS:
    void herramientaSeleccionada();

private:
    QPushButton *m_ninguna;
    QPushButton *m_manual;
    QPushButton *m_poliEspiral;
    QPushButton *m_poliRegular;
    QPushButton *m_roseta;
    QPushButton *m_estrella;
    QPushButton *m_poliArco;
    QPushButton *m_arco;
    QPushButton *m_circunferencia;
    QPushButton *m_hipotrocoide;
};

#endif
