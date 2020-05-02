cmake_minimum_required(VERSION 3.5)

project(chtholly LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    SET(GUI_TYPE WIN32)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(chtholly
    ${GUI_TYPE}

    mainwindow.cpp
    mainwindow.h
    main.cpp

    mainwindow.ui)

target_link_libraries(chtholly PRIVATE Qt5::Widgets)

