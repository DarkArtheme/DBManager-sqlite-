cmake_minimum_required(VERSION 3.5)

project(Sqlite3QT LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets LinguistTools Sql REQUIRED)
#option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include_directories(libs)

set(TS_FILES Sqlite3QT_ru_RU.ts)

set(PROJECT_SOURCES
        adminwindow.h
        adminwindow.cpp
        adminwindow.ui
        dbmanager.cpp
        dbmanager.h
        loginwindow.h
        loginwindow.cpp
        loginwindow.ui
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)


add_executable(Sqlite3QT ${PROJECT_SOURCES})


qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})




target_link_libraries(Sqlite3QT PRIVATE
    Qt5::Widgets
    Qt5::Sql)
