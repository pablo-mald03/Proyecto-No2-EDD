#ifndef PANTALLACOLASALIDA_H
#define PANTALLACOLASALIDA_H

#include <QWidget>

namespace Ui {
class PantallaColaSalida;
}

class PantallaColaSalida : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaColaSalida(QWidget *parent = nullptr);
    ~PantallaColaSalida();

private:
    Ui::PantallaColaSalida *ui;
};

#endif // PANTALLACOLASALIDA_H
