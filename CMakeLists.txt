cmake_minimum_required(VERSION 3.19)
project(ProyectoNo2-EDD LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/sucursales
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/inicio
)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(FRONTEND_SOURCES

    main.cpp
    src/frontend/mainwindow.cpp
    src/frontend/sucursales/pantallaprincipal.cpp
    src/frontend/sucursales/pantallaagregar.cpp
    src/frontend/sucursales/pantallabuscarporcategoria.cpp
    src/frontend/sucursales/pantallabuscarpornombre.cpp
    src/frontend/sucursales/pantallabuscarrango.cpp
    src/frontend/sucursales/pantallalistarnombre.cpp
    src/frontend/sucursales/pantallaeliminarproducto.cpp

    src/frontend/sucursales/pantallaverarboles.cpp

    src/frontend/sucursales/pantallaarbolavl.cpp
    src/frontend/sucursales/pantallaarbolb.cpp
    src/frontend/sucursales/pantallaarbolbmas.cpp
    src/frontend/sucursales/graphicsviewzoom.cpp

    src/frontend/pantallamain.cpp
    src/frontend/pantallagestion.cpp
    src/frontend/pantallasucursal.cpp
    src/frontend/pantallasistema.cpp


    src/frontend/inicio/pantallacargasucursales.cpp
    src/frontend/inicio/pantallacargaenvios.cpp
    src/frontend/inicio/pantallacargaproductos.cpp
    src/frontend/inicio/pantallaagregarsucursal.cpp
    src/frontend/inicio/pantallamodificarsucursal.cpp
    src/frontend/inicio/pantallaeliminarsucursal.cpp
    src/frontend/inicio/pantallaversucursales.cpp
    src/frontend/inicio/pantallaverenvios.cpp


)

set(FRONTEND_HEADERS

    include/frontend/mainwindow.h
    include/frontend/sucursales/pantallaprincipal.h
    include/frontend/sucursales/pantallaagregar.h
    include/frontend/sucursales/pantallabuscarporcategoria.h
    include/frontend/sucursales/pantallabuscarpornombre.h
    include/frontend/sucursales/pantallabuscarrango.h
    include/frontend/sucursales/pantallalistarnombre.h
    include/frontend/sucursales/pantallaeliminarproducto.h

    include/frontend/sucursales/pantallaverarboles.h
    include/frontend/sucursales/graphicsviewzoom.h

    include/frontend/sucursales/pantallaarbolavl.h
    include/frontend/sucursales/pantallaarbolb.h
    include/frontend/sucursales/pantallaarbolbmas.h

    include/frontend/pantallamain.h
    include/frontend/pantallasucursal.h
    include/frontend/pantallagestion.h
    include/frontend/pantallasistema.h

    include/frontend/inicio/pantallacargasucursales.h
    include/frontend/inicio/pantallacargaenvios.h
    include/frontend/inicio/pantallacargaproductos.h
    include/frontend/inicio/pantallaagregarsucursal.h
    include/frontend/inicio/pantallamodificarsucursal.h
    include/frontend/inicio/pantallaeliminarsucursal.h
    include/frontend/inicio/pantallaversucursales.h
    include/frontend/inicio/pantallaverenvios.h
)

set(CONTROLADORES_SOURCES

    src/controladores/controlador.cpp
    src/controladores/controladornegocio.cpp
    src/controladores/controladorsucursal.cpp
)

set(CONTROLADORES_HEADERS
    include/controladores/controlador.h
    include/controladores/controladornegocio.h
    include/controladores/controladorsucursal.h
)



set(UI_FILES

    ui/mainwindow.ui
    ui/sucursales/pantallaprincipal.ui
    ui/sucursales/pantallaagregar.ui
    ui/sucursales/pantallabuscarporcategoria.ui
    ui/sucursales/pantallabuscarpornombre.ui
    ui/sucursales/pantallabuscarrango.ui
    ui/sucursales/pantallalistarnombre.ui
    ui/sucursales/pantallaeliminarproducto.ui

    ui/sucursales/pantallaverarboles.ui

    ui/sucursales/pantallaarbolavl.ui
    ui/sucursales/pantallaarbolb.ui
    ui/sucursales/pantallaarbolbmas.ui

    ui/pantallamain.ui
    ui/pantallagestion.ui
    ui/pantallasucursal.ui
    ui/pantallasistema.ui

    ui/inicio/pantallacargasucursales.ui
    ui/inicio/pantallacargaenvios.ui
    ui/inicio/pantallacargaproductos.ui
    ui/inicio/pantallaagregarsucursal.ui
    ui/inicio/pantallamodificarsucursal.ui
    ui/inicio/pantallaeliminarsucursal.ui
    ui/inicio/pantallaversucursales.ui
    ui/inicio/pantallaverenvios.ui

)

set(BACKEND_SOURCES

    src/backend/gestorestructuras.cpp
    src/backend/listaenlazada.cpp
    src/backend/nodolista.cpp
    src/backend/producto.cpp
    src/backend/erroreslectura.cpp
    src/backend/nodoavl.cpp
    src/backend/arbolavl.cpp
    src/backend/nodob.cpp
    src/backend/arbolb.cpp
    src/backend/arbolbmas.cpp
    src/backend/nodobmas.cpp
)


set(BACKEND_HEADERS

    include/backend/gestorestructuras.h
    include/backend/listaenlazada.h
    include/backend/nodolista.h
    include/backend/producto.h
    include/backend/erroreslectura.h
    include/backend/nodoavl.h
    include/backend/arbolavl.h
    include/backend/nodob.h
    include/backend/arbolb.h
    include/backend/nodobmas.h
    include/backend/arbolbmas.h
)

set(EXCEPTIONS_SOURCES

    src/exceptions/readercsvexception.cpp
    src/exceptions/insertexception.cpp
    src/exceptions/deleteexception.cpp
)

set(EXCEPTIONS_HEADERS

    include/exceptions/readercsvexception.h
    include/exceptions/insertexception.h
    include/exceptions/deleteexception.h
)


set(MODULES_SOURCES

    src/modules/nodografico.cpp
)

set(MODULES_HEADERS

    include/modules/nodografico.h
)


qt_add_executable(ProyectoNo2-EDD
    WIN32 MACOSX_BUNDLE
    ${CONTROLADORES_SOURCES}
    ${CONTROLADORES_HEADERS}
    ${FRONTEND_SOURCES}
    ${FRONTEND_HEADERS}
    ${BACKEND_SOURCES}
    ${BACKEND_HEADERS}
    ${EXCEPTIONS_SOURCES}
    ${EXCEPTIONS_HEADERS}
    ${MODULES_SOURCES}
    ${MODULES_HEADERS}
    ${UI_FILES}
    recursos.qrc

)

target_include_directories(ProyectoNo2-EDD PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/frontend
    ${CMAKE_CURRENT_SOURCE_DIR}/include/backend
    ${CMAKE_CURRENT_SOURCE_DIR}/include/frontend/sucursales
    ${CMAKE_CURRENT_SOURCE_DIR}/include/frontend/inicio
    ${CMAKE_CURRENT_SOURCE_DIR}/include/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/include/controladores
    ${CMAKE_CURRENT_SOURCE_DIR}/include/modules
    ${CMAKE_CURRENT_BINARY_DIR}
)


target_link_libraries(ProyectoNo2-EDD
    PRIVATE
        Qt::Core
        Qt::Widgets
)


if(NOT APPLE AND NOT LINUX OR QT_VERSION GREATER_EQUAL 6.3)
    include(GNUInstallDirs)

    install(TARGETS ProyectoNo2-EDD
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    if(COMMAND qt_generate_deploy_app_script)
        qt_generate_deploy_app_script(
            TARGET ProyectoNo2-EDD
            OUTPUT_SCRIPT deploy_script
            NO_UNSUPPORTED_PLATFORM_ERROR
        )
        install(SCRIPT ${deploy_script})
    endif()
    
endif()
