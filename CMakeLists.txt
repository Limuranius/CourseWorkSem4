cmake_minimum_required(VERSION 3.5)

project(CourseWorkSem4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        planetaddwindow.h planetaddwindow.cpp planetaddwindow.ui
        attributeaddwindow.h attributeaddwindow.cpp attributeaddwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CourseWorkSem4
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CourseWorkSem4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CourseWorkSem4 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CourseWorkSem4
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CourseWorkSem4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Добавляю свои структуры данных
add_library(ListLib List.cpp)
add_library(HashTableLib HashTable.cpp)
add_library(RBTreeLib RBTree.cpp RBNode.cpp)
target_link_libraries(RBTreeLib ListLib)

add_library(StructuresLib Structures.cpp)

add_library(ParserLib Parsers.cpp)
target_link_libraries(ParserLib StructuresLib)

add_library(ToStringLib ToString.cpp)
target_link_libraries(ToStringLib StructuresLib)
add_library(ToIntLib ToInt.cpp)
target_link_libraries(ToIntLib StructuresLib)

add_library(PlanetsLib Planets.cpp)
target_link_libraries(PlanetsLib HashTableLib RBTreeLib StructuresLib ParserLib ToStringLib ToIntLib)
add_library(AttributesLib Attributes.cpp)
target_link_libraries(AttributesLib HashTableLib RBTreeLib StructuresLib ParserLib ToStringLib ToIntLib)

add_library(DatabaseLib Database.cpp)
target_link_libraries(DatabaseLib PlanetsLib AttributesLib)

target_link_libraries(CourseWorkSem4 PRIVATE DatabaseLib)


set_target_properties(CourseWorkSem4 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CourseWorkSem4)
endif()
