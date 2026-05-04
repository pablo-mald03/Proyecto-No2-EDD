#ifndef PANTALLAHISTORIALENVIOS_H
#define PANTALLAHISTORIALENVIOS_H

#include <QWidget>

namespace Ui {
class PantallaHistorialEnvios;
}

class PantallaHistorialEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaHistorialEnvios(QWidget *parent = nullptr);
    ~PantallaHistorialEnvios();

private:
    Ui::PantallaHistorialEnvios *ui;
};

#endif // PANTALLAHISTORIALENVIOS_H
