cmake_minimum_required(VERSION 3.16)

project(WMark VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES WMark_en_CA.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
)

# ✅ 先定义目标
qt_add_executable(WMark
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    logos.qrc
    ../Downloads/Fujifilm-logo.png ../Downloads/images.png ../Downloads/Leica_Camera_logo.svg.png ../Downloads/logo.html
)
# 找 OpenCV
find_package(OpenCV REQUIRED)

# 包含 OpenCV 的头文件
include_directories(${OpenCV_INCLUDE_DIRS})

# 链接 OpenCV 库
target_link_libraries(WMark PRIVATE ${OpenCV_LIBS})

# ✅ 设置 libraw 与 exiv2 路径（Homebrew 默认路径）
target_include_directories(WMark PRIVATE /opt/homebrew/include)
target_link_libraries(WMark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    /opt/homebrew/lib/libraw.dylib
    /opt/homebrew/lib/libexiv2.dylib
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# ✅ macOS Bundle 设置
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WMark)
endif()
set_target_properties(WMark PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ✅ 安装与打包设置
include(GNUInstallDirs)
install(TARGETS WMark
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WMark)
endif()
