##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## ia/CMakeLists.txt
##

cmake_minimum_required(VERSION 3.12)
project(Zappy
        HOMEPAGE_URL "https://github.com/Bqleine/zappy-ai"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE IA_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(zappy_ai ${IA_SRC_FILES})

set_target_properties(zappy_ai PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_include_directories(zappy_ai
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(zappy_ai PRIVATE sodium)

# Unit tests
file(GLOB_RECURSE IA_TEST_SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
list(APPEND IA_TEST_SRC_FILES ${IA_SRC_FILES})
list(FILTER IA_TEST_SRC_FILES EXCLUDE REGEX "main.cpp")

add_executable(zappy_ai_tests ${IA_TEST_SRC_FILES})

target_include_directories(zappy_ai_tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(zappy_ai_tests PRIVATE criterion sodium)
