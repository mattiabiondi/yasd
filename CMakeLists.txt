cmake_minimum_required(VERSION 3.5.0)

project(yasd
        VERSION 0.0.1)

add_compile_options(-D_FORTIFY_SOURCE=2 -O2 -Wall -pedantic)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Minimum Versions
set(QT_MINIMUM_VERSION "5.9.0")

add_subdirectory(src)
