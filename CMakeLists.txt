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
        RBTree.h RBTree.cpp
        RBNode.h RBNode.cpp
        ReferenceAttributes.h ReferenceAttributes.cpp
        ReferencePlanets.h ReferencePlanets.cpp
        Database.h Database.cpp
        hash_table.h hash_table.cpp
        List.h List.cpp
        parsers.h parsers.cpp
        utilities.h utilities.cpp
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

# Добавляем самодельные структуры данных
#add_subdirectory("Code")

#set(DATA_STRUCTURES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Code/Data Structures")
#set(HT_DIR "${DATA_STRUCTURES_DIR}/Hash Table")
#set(RB_TREE_DIR "${DATA_STRUCTURES_DIR}/RB Tree")
#set(LIST_DIR "${DATA_STRUCTURES_DIR}/Single Linked List")

#set(DATABASES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Code/Databases")

# Линкуем GUI с самодельными СД
#target_link_libraries(CourseWorkSem4 PUBLIC DatabaseLib)

#include_directories(${HT_DIR}
#        ${RB_TREE_DIR}
#        ${LIST_DIR})
#include_directories(${DATABASES_DIR})

target_link_libraries(CourseWorkSem4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CourseWorkSem4 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CourseWorkSem4)
endif()
