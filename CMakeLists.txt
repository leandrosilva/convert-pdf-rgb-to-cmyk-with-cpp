cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(poc-gerar-pdf VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(deps/include)
link_directories(deps/lib/ghostscript)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(rgb-to-cmyk ${SRC_FILES})

target_link_libraries(rgb-to-cmyk -lgpdf)

target_compile_options(rgb-to-cmyk PRIVATE
    "-fPIC"
    "-Wall"
    "-Wextra"
    "-Wshadow")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
