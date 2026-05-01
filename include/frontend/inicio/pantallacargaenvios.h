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

    void limpiarLogs();

    std::vector<std::vector<QString>> parsearCSV(const QString &contenido);

public slots:
    void appendLogCarga(QString mensaje, QString color);
    void appendGrafoLog(QString mensaje, QString color);
    void mostrarTiempo(int estructura, double milisegundos);

signals:
    void csvEnviosCargado(const std::vector<std::vector<QString>> & data);
private slots:
    void on_btnCargar_clicked();
};

#endif // PANTALLACARGAENVIOS_H
