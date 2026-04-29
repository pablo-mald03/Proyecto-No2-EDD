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

# Intentamos primero la configuración estándar (si instalaron con apt)
# Si tú quieres forzar tu ruta local de Qt, descomenta la línea de abajo y comenta la de arriba.
cmake ..

# Si falla el anterior (porque Qt6 no está en el PATH), podrías usar:
# cmake -DCMAKE_PREFIX_PATH=/ruta/a/tu/qt/6.x.x/gcc_64 ..

if [ $? -ne 0 ]; then
    echo -e "${RED}Error en configuración CMake. Verifica que Qt6 esté instalado.${NC}"
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
