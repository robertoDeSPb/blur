cmake_minimum_required(VERSION 3.14)

project(blur_effect LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(blur_effect
  main.cpp
)
target_link_libraries(blur_effect Qt5::Core Qt5::Widgets)
