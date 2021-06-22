#set(CMAKE_PREFIX_PATH  "E:\\Qt\\5.15.2\\mingw81_64")
#set(CMAKE_PREFIX_PATH  "C:\\Qt\\5.15.1\\mingw81_64")
cmake_minimum_required(VERSION 3.5)

project(Barybians-Desktop-Client LANGUAGES CXX)
find_package( Qt5Core REQUIRED)
find_package( Qt5Widgets REQUIRED)
find_package( Qt5Gui REQUIRED )
find_package( Qt5Network REQUIRED )
find_package( Qt5OpenGL REQUIRED )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



        # QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets QuickControls2 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
    add_library(Barybians-Desktop-Client SHARED
            cpp/main.cpp
            )
else()
    add_executable(Barybians-Desktop-Client
            cpp/main.cpp
            cpp/windows/mainwindow.cpp
            headers/windows/mainwindow.h
            cpp/webconnector.cpp
            headers/webconnector.h
            cpp/data.cpp
            headers/data.h
            headers/windows/loginwindow.h
            cpp/windows/loginwindow.cpp
            res.qrc
            cpp/windows/userpage.cpp headers/windows/userpage.h cpp/windows/feedpage.cpp headers/windows/feedpage.h cpp/models/userfeed.cpp headers/models/userfeed.h cpp/windows/dialogwindow.cpp headers/windows/dialogwindow.h cpp/models/messagecard.cpp headers/models/messagecard.h cpp/models/navigationbar.cpp headers/models/navigationbar.h cpp/models/feedlistmodel.cpp headers/models/feedlistmodel.h)
endif()

target_link_libraries(Barybians-Desktop-Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Barybians-Desktop-Client PRIVATE Qt${QT_VERSION_MAJOR}::Network)
