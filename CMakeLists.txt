cmake_minimum_required(VERSION 4.4)

project(
    CPUPathTracing
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/rapidobj EXCLUDE_FROM_ALL)
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML/CMakeLists.txt")
    set(SFML_BUILD_WINDOW ON CACHE BOOL "" FORCE)
    set(SFML_BUILD_GRAPHICS ON CACHE BOOL "" FORCE)
    set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/freetype-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_FREETYPE "${CMAKE_BINARY_DIR}/_deps/freetype-src" CACHE PATH "" FORCE)
    endif()
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/harfbuzz-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_HARFBUZZ "${CMAKE_BINARY_DIR}/_deps/harfbuzz-src" CACHE PATH "" FORCE)
    endif()
    if (EXISTS "${CMAKE_BINARY_DIR}/_deps/sheenbidi-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_SHEENBIDI "${CMAKE_BINARY_DIR}/_deps/sheenbidi-src" CACHE PATH "" FORCE)
    endif()
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
    add_subdirectory(thirdparty/SFML EXCLUDE_FROM_ALL)
endif()
add_subdirectory(source)
