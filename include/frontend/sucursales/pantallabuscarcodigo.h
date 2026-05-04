#ifndef PANTALLABUSCARCODIGO_H
#define PANTALLABUSCARCODIGO_H

#include <QWidget>

namespace Ui {
class PantallaBuscarCodigo;
}

class PantallaBuscarCodigo : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaBuscarCodigo(QWidget *parent = nullptr);
    ~PantallaBuscarCodigo();

private:
    Ui::PantallaBuscarCodigo *ui;
};

#endif // PANTALLABUSCARCODIGO_H
