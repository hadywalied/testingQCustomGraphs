cmake_minimum_required(VERSION 3.14)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Charts REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

include_directories(${CMAKE_INCLUDE_CURRENT_DIR})

file(GLOB_RECURSE SRCS
        *.cpp
        *.h
        reusableComponents/*.cpp
        reusableComponents/*.h
        dataModels/*.cpp
        dataModels/*.h)

add_library(gui ${SRCS})

target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(gui testNoFrams)