#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto
{

private:
    std::string nombre;
    std::string codigoBarra;
    std::string categoria;
    std::string fechaExpiracion;
    std::string marca;
    double precio;
    int stock;

public:
    Producto();
    Producto(const std::string &_nombre,const std::string &_codigoBarra, const std::string &_categoria, const std::string &_fechaExpiracion, const std::string &_marca, double _precio, int _stock);

    /*Metodos getter */
    std::string getNombre() const;
    std::string getCodigoBarra() const;
    std::string getCategoria()const ;
    std::string getFechaExpiracion()const ;
    std::string getMarca() const;
    double getPrecio() const;
    int getStock() const;

    /*Metodos setter */
    void setNombre(const std::string &_nombre);
    void setCodigoBarra(const std::string &_codigoBarra);
    void setCategoria(const std::string &_categoria);
    void setFechaExpiracion(const std::string &_fechaExpiracion);
    void setMarca(const std::string &_marca);
    void setPrecio(double _precio);
    void setStock(int _stock);
    std::string getToString() const;

};

#endif // PRODUCTO_H
