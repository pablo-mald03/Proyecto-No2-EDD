#ifndef PANTALLACOLAINGRESO_H
#define PANTALLACOLAINGRESO_H

#include <QWidget>

namespace Ui {
class PantallaColaIngreso;
}

class PantallaColaIngreso : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaColaIngreso(QWidget *parent = nullptr);
    ~PantallaColaIngreso();

private:
    Ui::PantallaColaIngreso *ui;
};

#endif // PANTALLACOLAINGRESO_H
