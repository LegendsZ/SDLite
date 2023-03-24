cmake_minimum_required(VERSION 3.24)
project(SDLite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Find the SDL2 code on the system, will define path variables
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(OBJECT_SOURCES SDLiteMain Window Text Rect FRect Button Audio)

foreach(_OBJECT_ ${OBJECT_SOURCES})
    # Declare a new object that should be built ...
    add_library(${_OBJECT_} OBJECT "${CMAKE_SOURCE_DIR}/src/${_OBJECT_}.cpp")
    target_include_directories(${_OBJECT_} PUBLIC "${CMAKE_SOURCE_DIR}/include"
            $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:SDL2_image::SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:SDL2_mixer::SDL2_mixer,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:SDL2_ttf::SDL2_ttf,INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(${_OBJECT_} SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)
    # ... add the output object to `OBJECTS` list
    list(APPEND _OBJECTS_ $<TARGET_OBJECTS:${_OBJECT_}>)
endforeach()

add_library(SDLite "${CMAKE_SOURCE_DIR}/src/SDLiteMain.cpp")

target_include_directories(SDLite PUBLIC "${CMAKE_SOURCE_DIR}/include"
        $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:SDL2_image::SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:SDL2_mixer::SDL2_mixer,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:SDL2_ttf::SDL2_ttf,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(SDLite ${_OBJECTS_} SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)