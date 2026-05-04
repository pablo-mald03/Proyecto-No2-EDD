#ifndef PANTALLAVERESTADOENVIOS_H
#define PANTALLAVERESTADOENVIOS_H

#include <QWidget>

namespace Ui {
class PantallaVerEstadoEnvios;
}

class PantallaVerEstadoEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerEstadoEnvios(QWidget *parent = nullptr);
    ~PantallaVerEstadoEnvios();

private:
    Ui::PantallaVerEstadoEnvios *ui;
};

#endif // PANTALLAVERESTADOENVIOS_H
