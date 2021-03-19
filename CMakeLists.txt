#################################################
# IKSDL - C++ wrapper for SDL
# Copyright (C) 2021 InternationalKoder
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#################################################

cmake_minimum_required(VERSION 3.12)

project(iksdl VERSION 1.0 LANGUAGES CXX)
set(CMAKE_DEBUG_POSTFIX -d)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Project files
set(SOURCE_FILES
    src/iksdl/AbstractRectangle.cpp
    src/iksdl/AbstractRectangleArray.cpp
    src/iksdl/Channels.cpp
    src/iksdl/Event.cpp
    src/iksdl/FillRectangle.cpp
    src/iksdl/FillRectangleArray.cpp
    src/iksdl/Font.cpp
    src/iksdl/Keyboard.cpp
    src/iksdl/KeyboardEvent.cpp
    src/iksdl/Line.cpp
    src/iksdl/LineArray.cpp
    src/iksdl/Mouse.cpp
    src/iksdl/MouseButtonEvent.cpp
    src/iksdl/MouseMotionEvent.cpp
    src/iksdl/MouseWheelEvent.cpp
    src/iksdl/Music.cpp
    src/iksdl/Point.cpp
    src/iksdl/PointArray.cpp
    src/iksdl/Rectangle.cpp
    src/iksdl/RectangleArray.cpp
    src/iksdl/Renderer.cpp
    src/iksdl/Sound.cpp
    src/iksdl/Sprite.cpp
    src/iksdl/Text.cpp
    src/iksdl/Texture.cpp
    src/iksdl/Window.cpp
    src/iksdl/WindowEvent.cpp
)

set(INCLUDE_FILES
    include/iksdl.hpp
    include/iksdl/common.hpp
    include/iksdl/iksdl_export.hpp
    include/iksdl/AbstractEvent.hpp
    include/iksdl/AbstractRectangle.hpp
    include/iksdl/AbstractRectangleArray.hpp
    include/iksdl/Channels.hpp
    include/iksdl/Color.hpp
    include/iksdl/Drawable.hpp
    include/iksdl/Event.hpp
    include/iksdl/EventHandler.hpp
    include/iksdl/EventSupport.hpp
    include/iksdl/FillRectangle.hpp
    include/iksdl/FillRectangleArray.hpp
    include/iksdl/Font.hpp
    include/iksdl/InvalidParameterException.hpp
    include/iksdl/Keyboard.hpp
    include/iksdl/KeyboardEvent.hpp
    include/iksdl/Line.hpp
    include/iksdl/LineArray.hpp
    include/iksdl/Mouse.hpp
    include/iksdl/MouseButtonEvent.hpp
    include/iksdl/MouseMotionEvent.hpp
    include/iksdl/MouseWheelEvent.hpp
    include/iksdl/Music.hpp
    include/iksdl/Point.hpp
    include/iksdl/PointArray.hpp
    include/iksdl/Position.hpp
    include/iksdl/QuitEvent.hpp
    include/iksdl/Rect.hpp
    include/iksdl/Rectangle.hpp
    include/iksdl/RectangleArray.hpp
    include/iksdl/Renderer.hpp
    include/iksdl/RendererOptions.hpp
    include/iksdl/SdlException.hpp
    include/iksdl/Size.hpp
    include/iksdl/Sound.hpp
    include/iksdl/Sprite.hpp
    include/iksdl/Text.hpp
    include/iksdl/Texture.hpp
    include/iksdl/Window.hpp
    include/iksdl/WindowEvent.hpp
    include/iksdl/WindowOptions.hpp
)

# Dependencies
set(SDL2_BUILDING_LIBRARY TRUE)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Define library
add_library(iksdl SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(iksdl
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(iksdl PUBLIC SDL2::Core SDL2::Image SDL2::TTF SDL2::Mixer)

# Build options
target_compile_features(iksdl PRIVATE cxx_std_20)
set_target_properties(iksdl
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
  set_target_properties(iksdl PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Export symbols
include(GenerateExportHeader)
GENERATE_EXPORT_HEADER(iksdl
    BASE_NAME IKSDL
    EXPORT_MACRO_NAME IKSDL_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/iksdl/iksdl_export.hpp
    STATIC_DEFINE IKSDL_BUILT_AS_STATIC
)

# Install
include(GNUInstallDirs)
install(TARGETS iksdl
    EXPORT iksdl-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES
    cmake/FindSDL2.cmake
    cmake/FindSDL2_image.cmake
    cmake/FindSDL2_mixer.cmake
    cmake/FindSDL2_ttf.cmake
    DESTINATION cmake
)

install(EXPORT iksdl-targets
    FILE iksdlTargets.cmake
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/iksdlConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/iksdlConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/iksdlConfig.cmake
    INSTALL_DESTINATION cmake
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/iksdlConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/iksdlConfigVersion.cmake
    DESTINATION cmake
)

# Make the library available in the build tree
export(EXPORT iksdl-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/iksdlTargets.cmake
)

export(PACKAGE iksdl)
