##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## ia/tests/CMakeLists.txt
##

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/ia/src/*.cpp")

list(APPEND TEST_SRC ${SRC})
list(FILTER TEST_SRC EXCLUDE REGEX "main.c")

add_compile_options(--coverage)

add_executable(unit_test_ia_zappy ${TEST_SRC})

set_target_properties(unit_test_server_zappy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_include_directories(unit_test_server_zappy PRIVATE ${CMAKE_SOURCE_DIR}/ia/include)

target_link_libraries(unit_test_server_zappy PRIVATE criterion)
