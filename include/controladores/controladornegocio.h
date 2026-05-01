#ifndef CONTROLADORNEGOCIO_H
#define CONTROLADORNEGOCIO_H

#include <QObject>

/*Controlador que permite llevar toda la logica para el manejo principal de las redes de sucursales*/
class ControladorNegocio : public QObject
{
    Q_OBJECT
public:
    explicit ControladorNegocio(QObject *parent = nullptr);
    ~ControladorNegocio();

public slots:
    void procesarCsvSucursal(const std::vector<std::vector<QString>> & data);
    void procesarCsvConexion(const std::vector<std::vector<QString>> & data);

signals:

    /*Metodos que permiten agregar enviar informacion sobre los logs de los datos de las sucursales*/
    void logGrafoSucursales(QString mensaje, QString color);
    void logCargaCsvSucursales(QString mensaje, QString color);

    /*Signal que permite setear el tiempo en el label*/
    void tiempoProcesoSucursales(int estructura, double milisegundos);
};

#endif // CONTROLADORNEGOCIO_H
