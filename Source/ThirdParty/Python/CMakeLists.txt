cmake_minimum_required(VERSION 3.22)
project(Python)

set(CMAKE_CXX_STANDARD 14)


add_library(Python SHARED PythonLibrary.h PythonLibrary.cpp)

target_include_directories(Python PUBLIC ${CMAKE_SOURCE_DIR}/Win64/include)
target_link_libraries(Python ${CMAKE_SOURCE_DIR}/Win64/lib/python3.lib ${CMAKE_SOURCE_DIR}/Win64/lib/python39.lib)

add_custom_command(TARGET Python POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Python> ${CMAKE_SOURCE_DIR}/../../../Binaries/ThirdParty/PythonScriptLibrary/Win64/Python.dll
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:Python>/Python.lib ${CMAKE_SOURCE_DIR}/Win64/lib/Python.lib
        )


