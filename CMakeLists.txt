cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(NefaryousGameApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

qt6_policy(SET QTP0001 NEW)

set(RESOURCE_FILES resources.qrc)
qt_add_resources(RESOURCE_ADDED ${RESOURCE_FILES})

qt_add_executable(NefaryousGameApp src/Controller/main.cpp
        src/Model/Entity.cpp
        src/Model/Entity.h
        src/Model/Exit.cpp
        src/Model/Exit.h
        src/Model/Room.cpp
        src/Model/Room.h
        src/Controller/Game.h
        src/Controller/Game.h
        src/Controller/Game.cpp
        src/Controller/Game.cpp
        src/Controller/Game.cpp
        src/Model/Item.h
        src/Model/Weapon.cpp
        src/Model/Weapon.h
        content/images/pxArt.png
        ${RESOURCE_FILES}
        src/Model/Inventory.h
        src/Model/InventoryBase.h
        src/Model/Player.cpp
        src/Model/Player.h
        src/Model/Key.h
        src/Model/Key.cpp
)

qt_add_resources(NefaryousGameApp "configuration"
        PREFIX "/"
        FILES
        qtquickcontrols2.conf
)




target_link_libraries(NefaryousGameApp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
        CACHE STRING "Import paths for Qt Creator's code model"
        FORCE
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS NefaryousGameApp
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
        "Path to the custom QML components defined by the project")

