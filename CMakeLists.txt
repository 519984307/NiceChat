cmake_minimum_required(VERSION 3.14)

project(NiceChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_DIR_PATH ${PROJECT_SOURCE_DIR}/third)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR} CACHE PATH "Install path prefix" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQ_IS_DEBUG)
endif()

add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QuickControls2 WebEngine Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 WebEngine Multimedia REQUIRED)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")

add_subdirectory(src)
