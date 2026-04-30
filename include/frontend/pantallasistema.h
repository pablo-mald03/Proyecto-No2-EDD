#ifndef PANTALLASISTEMA_H
#define PANTALLASISTEMA_H

#include <QWidget>

namespace Ui {
class PantallaSistema;
}

class PantallaSistema : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSistema(QWidget *parent = nullptr);
    ~PantallaSistema();


    /*Metodos para poder comunicarse desde fuera con la pantalla*/
    void setPantallanInicio();

private:
    Ui::PantallaSistema *ui;
};

#endif // PANTALLASISTEMA_H
