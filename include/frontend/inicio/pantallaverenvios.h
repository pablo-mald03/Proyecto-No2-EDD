#ifndef PANTALLAVERENVIOS_H
#define PANTALLAVERENVIOS_H

#include <QWidget>

namespace Ui {
class PantallaVerEnvios;
}

class PantallaVerEnvios : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaVerEnvios(QWidget *parent = nullptr);
    ~PantallaVerEnvios();

private:
    Ui::PantallaVerEnvios *ui;
};

#endif // PANTALLAVERENVIOS_H
