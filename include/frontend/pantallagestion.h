#ifndef PANTALLAGESTION_H
#define PANTALLAGESTION_H

#include <QWidget>

namespace Ui {
class PantallaGestion;
}

class PantallaGestion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaGestion(QWidget *parent = nullptr);
    ~PantallaGestion();

private:
    Ui::PantallaGestion *ui;
};

#endif // PANTALLAGESTION_H
