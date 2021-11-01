cmake_minimum_required(VERSION 3.14)

project(testingNoForms LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(gui)
add_subdirectory(test)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

file(GLOB_RECURSE SRCS
        gui/*.h
        gui/*.cpp
        )
add_executable(testingNoForms
        ${SRCS}
)

target_link_libraries(testingNoForms Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt5::PrintSupport)
