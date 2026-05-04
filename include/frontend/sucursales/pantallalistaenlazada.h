#ifndef PANTALLALISTAENLAZADA_H
#define PANTALLALISTAENLAZADA_H

#include <QWidget>

namespace Ui {
class PantallaListaEnlazada;
}

class PantallaListaEnlazada : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaListaEnlazada(QWidget *parent = nullptr);
    ~PantallaListaEnlazada();

private:
    Ui::PantallaListaEnlazada *ui;
};

#endif // PANTALLALISTAENLAZADA_H
