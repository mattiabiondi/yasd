cmake_minimum_required(VERSION 3.5.0)

project(yasd
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-D_FORTIFY_SOURCE=2 -O2 -Wall -pedantic)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

# Minimum Versions
set(QT_MINIMUM_VERSION "5.14.0")

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)

add_subdirectory(src)
