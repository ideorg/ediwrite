cmake_minimum_required(VERSION 3.5)

project(editwrite VERSION 0.5 LANGUAGES CXX)

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-Werror=return-type")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
else()
    add_definitions(-DUSE64bit=true)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# SingleApplication base class
set(QAPPLICATION_CLASS QApplication)
add_subdirectory(SingleApplication)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS Core REQUIRED)

set(PROJECT_SOURCES
       main.cpp
        codeeditor.cpp
        MainWindow.cpp MainWindow.h
        UntitleCounter.cpp UntitleCounter.h
	    raise.cpp raise.h
        )


if(${QT_DEFAULT_MAJOR_VERSION} GREATER_EQUAL 6)
    qt_add_executable(editwrite
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET editwrite APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(editwrite SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(editwrite
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_include_directories(editwrite PRIVATE
        /usr/include/KF5/KSyntaxHighlighting)
target_link_libraries(${PROJECT_NAME} SingleApplication::SingleApplication
         KF5SyntaxHighlighting
	 X11)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(editwrite)
endif()