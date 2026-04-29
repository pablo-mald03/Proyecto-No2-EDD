cmake_minimum_required(VERSION 3.19)
project(ProyectoNo1-EDD LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(FRONTEND_SOURCES

    main.cpp
    src/frontend/mainwindow.cpp
    src/frontend/pantallaprincipal.cpp
    src/frontend/pantallaagregar.cpp
    src/frontend/controlador.cpp
    src/frontend/pantallabuscarporcategoria.cpp
    src/frontend/pantallabuscarpornombre.cpp
    src/frontend/pantallabuscarrango.cpp
    src/frontend/pantallalistarnombre.cpp
    src/frontend/pantallaeliminarproducto.cpp

    src/frontend/pantallaverarboles.cpp

    src/frontend/pantallaarbolavl.cpp
    src/frontend/pantallaarbolb.cpp
    src/frontend/pantallaarbolbmas.cpp
    src/frontend/graphicsviewzoom.cpp

)

set(FRONTEND_HEADERS

    include/frontend/mainwindow.h
    include/frontend/pantallaprincipal.h
    include/frontend/pantallaagregar.h
    include/frontend/controlador.h
    include/frontend/pantallabuscarporcategoria.h
    include/frontend/pantallabuscarpornombre.h
    include/frontend/pantallabuscarrango.h
    include/frontend/pantallalistarnombre.h
    include/frontend/pantallaeliminarproducto.h

    include/frontend/pantallaverarboles.h
    include/frontend/graphicsviewzoom.h

    include/frontend/pantallaarbolavl.h
    include/frontend/pantallaarbolb.h
    include/frontend/pantallaarbolbmas.h
)


set(UI_FILES

    ui/mainwindow.ui
    ui/pantallaprincipal.ui
    ui/pantallaagregar.ui
    ui/pantallabuscarporcategoria.ui
    ui/pantallabuscarpornombre.ui
    ui/pantallabuscarrango.ui
    ui/pantallalistarnombre.ui
    ui/pantallaeliminarproducto.ui

    ui/pantallaverarboles.ui

    ui/pantallaarbolavl.ui
    ui/pantallaarbolb.ui
    ui/pantallaarbolbmas.ui

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


qt_add_executable(ProyectoNo1-EDD
    WIN32 MACOSX_BUNDLE
    ${FRONTEND_SOURCES}
    ${FRONTEND_HEADERS}
    ${BACKEND_SOURCES}
    ${BACKEND_HEADERS}
    ${EXCEPTIONS_SOURCES}
    ${EXCEPTIONS_HEADERS}
    ${UI_FILES}
    recursos.qrc

)

target_include_directories(ProyectoNo1-EDD PRIVATE
    include/frontend
    include/backend
    include/exceptions
)


target_link_libraries(ProyectoNo1-EDD
    PRIVATE
        Qt::Core
        Qt::Widgets
)


if(NOT APPLE AND NOT LINUX OR QT_VERSION GREATER_EQUAL 6.3)
    include(GNUInstallDirs)

    install(TARGETS ProyectoNo1-EDD
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    if(COMMAND qt_generate_deploy_app_script)
        qt_generate_deploy_app_script(
            TARGET ProyectoNo1-EDD
            OUTPUT_SCRIPT deploy_script
            NO_UNSUPPORTED_PLATFORM_ERROR
        )
        install(SCRIPT ${deploy_script})
    endif()
endif()
