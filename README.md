# ProyectoNo1-EDD

## Descripcion

Este es mi primer proyecto de mi tan esperado curso de EDD :)
En el cual se pidio hacer un gestor de productos para poder almacenar productos y generar busquedas e inserciones de la manera 
como lo hacen las grandes bases de datos.
En el Framework QT Creator que me permitio desarrollar una interfaz grafica. QT es un Framework de de C++ que posee la caracteristica de ser multiplataforma, sin embargo tambien 
para futuros programadores de este proyecto se debe de saber como poder compilar este archivo.

Por lo tanto aca les dejo las instrucciones para poder generar el ejecutable de mi proyecto. Que fue muy interesante de programar :) 

## Requisitos

- Qt 6 o superior
- CMake 3.19 o superior
- Compilador C++ (GCC / MinGW / MSVC)


## Instrucciones de compilacion

Aca les dejo un Scriptcito para que puedan generar el ejecutable en linux.

### Script build.sh

Crear un archivo llamado `build.sh` en la raiz del proyecto con el siguiente contenido:

```bash
#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}====================================${NC}"
echo -e "${GREEN}   Compilando Proyecto :) (Qt6 + CMake)${NC}"
echo -e "${GREEN}====================================${NC}"

if [ ! -f "CMakeLists.txt" ]; then
    echo -e "${RED}Error: No se encontró CMakeLists.txt en esta carpeta.${NC}"
    exit 1
fi

echo "Limpiando versiones anteriores..."
rm -rf build
mkdir build
cd build

echo "Generando proyecto con CMake..."

#Si lo instalaste desde apt puede usar el comando 
# Si quieres forzar tu ruta local de Qt, descomenta la linea de abajo y comenta la de arriba.
cmake ..

# Si falla el anterior (porque Qt6 no está en el PATH), podrías usar:
# cmake -DCMAKE_PREFIX_PATH=/ruta/a/tu/qt/6.x.x/gcc_64 ..

if [ $? -ne 0 ]; then
    echo -e "${RED}Error en configuracion CMake. Verifica que Qt6 este instalado.${NC}"
    exit 1
fi

echo "Compilando con $(nproc) núcleos..."
cmake --build . --parallel $(nproc)

if [ $? -ne 0 ]; then
    echo -e "${RED}Error en compilación.${NC}"
    exit 1
fi

echo -e "${GREEN}------------------------------------${NC}"
echo -e "${GREEN} Compilación exitosa.${NC}"
echo -e " El ejecutable está en: ${GREEN}$(pwd)${NC}"
echo -e "${GREEN}------------------------------------${NC}"

```

## Luego de copiar el script o si usas el del repositorio:

Abre tu terminal en el directorio donde clonaste mi repositorio 
y ejecuta:

```
chmod +x build.sh

./build.sh
```

## Si no tienes QT en tu pc sigue los pasos:

Debido a que mi proyecto esta en QT este pide que este instalado, entonces sigue los siguientes pasos:

## Compilacion en linux:

```
sudo apt update

sudo apt install qt6-base-dev qt6-base-dev-tools cmake build-essential

qmake6 --version 

cmake --version

```

## Compilación en Windows

### Opcion 1: Recomendada

1. Instalar Qt desde:
   https://www.qt.io/download

2. Abrir Qt Creator.
3. Abrir el proyecto. Dar click en (CMakeLists.txt).
4. Seleccionar el Kit adecuado, (Ejemplo: Qt 6.x MinGW 64-bit)..
5. Presionar Build.

---

### Opción 2 (Terminal Qt)

Instalar Qt con MinGW.

1. Qt => Qt 6.x for Desktop (MinGW 64-bit)    (No usar PowerShell normal.)

2. Ir Qt Command Prompt (MinGW)

3. Ir a la ruta. Ejemplo: `cd ruta\al\proyecto`

4. Crear la carpeta build:
`mkdir build
cd build`

Luego ejecutar:

`cmake -G "MinGW Makefiles" `..
Por ultimo:
`cmake --build .`

### Espero sea de su ayuda y les guste mi proyecto :)

