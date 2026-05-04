#ifndef PANTALLACOLAPREPARACION_H
#define PANTALLACOLAPREPARACION_H

#include <QWidget>

namespace Ui {
class PantallaColaPreparacion;
}

class PantallaColaPreparacion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaColaPreparacion(QWidget *parent = nullptr);
    ~PantallaColaPreparacion();

private:
    Ui::PantallaColaPreparacion *ui;
};

#endif // PANTALLACOLAPREPARACION_H
