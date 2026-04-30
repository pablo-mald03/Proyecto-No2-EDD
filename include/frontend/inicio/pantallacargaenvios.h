#ifndef PANTALLACARGAENVIOS_H
#define PANTALLACARGAENVIOS_H

#include <QWidget>

namespace Ui {
class PantallaCargaEnvios;
}

class PantallaCargaEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaCargaEnvios(QWidget *parent = nullptr);
    ~PantallaCargaEnvios();

private:
    Ui::PantallaCargaEnvios *ui;
};

#endif // PANTALLACARGAENVIOS_H
