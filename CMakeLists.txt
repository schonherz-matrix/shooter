cmake_minimum_required(VERSION 3.16)

project(
  matrix-shooter
  HOMEPAGE_URL "kszk.bme.hu"
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(LIBMUEB_AS_DLL)

find_package(
  Qt5
  COMPONENTS Widgets Multimedia Gamepad
  REQUIRED)
find_package(SFML 2 COMPONENTS system window audio REQUIRED)
find_package(libmueb 2.0 REQUIRED)

add_subdirectory(extern/gainput)

add_executable(
  ${PROJECT_NAME}
  src/asteroid.cpp
  src/asteroid.h
  src/bar.cpp
  src/bar.h
  src/border.cpp
  src/border.h
  src/collidingitem.cpp
  src/collidingitem.h
  src/config.cpp
  src/config.h
  src/hitindicator.cpp
  src/hitindicator.h
  src/laser.cpp
  src/laser.hpp
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
  src/matrixscene.cpp
  src/matrixscene.h
  src/missile.cpp
  src/missile.h
  src/player.cpp
  src/player.h
  src/powerup.cpp
  src/powerup.h
  src/wreck.cpp
  src/wreck.h)

target_include_directories(${PROJECT_NAME} PRIVATE extern/gainput/lib/include/)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE Qt5::Widgets
          Qt5::Multimedia
          Qt5::Gamepad
          libmueb::muebtransmitter
          sfml-system
          sfml-window
          sfml-audio
          gainput)
