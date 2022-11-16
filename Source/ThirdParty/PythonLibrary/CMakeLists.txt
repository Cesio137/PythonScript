cmake_minimum_required(VERSION 3.22)
project(PythonLibrary)

set(CMAKE_CXX_STANDARD 14)


add_library(PythonLibrary SHARED PythonLibrary.h PythonLibrary.cpp)

target_include_directories(PythonLibrary PUBLIC ${CMAKE_SOURCE_DIR}/Win64/include)
target_link_libraries(PythonLibrary ${CMAKE_SOURCE_DIR}/Win64/lib/python3.lib ${CMAKE_SOURCE_DIR}/Win64/lib/python39.lib)

add_custom_command(TARGET PythonLibrary POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PythonLibrary> ${CMAKE_SOURCE_DIR}/../../../Binaries/ThirdParty/PythonScriptLibrary/Win64/PythonLibrary.dll
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:PythonLibrary>/PythonLibrary.lib ${CMAKE_SOURCE_DIR}/Win64/lib/PythonLibrary.lib
        )


