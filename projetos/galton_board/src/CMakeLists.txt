# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(galton_board C CXX ASM)

pico_sdk_init()

add_executable(galton_board
    app/main.c
    hal/ssd1306.c
)

pico_set_program_name(galton_board "galton_board")
pico_set_program_version(galton_board "0.1")

pico_enable_stdio_uart(galton_board 0)
pico_enable_stdio_usb(galton_board 1)

target_link_libraries(galton_board
    pico_stdlib
    pico_rand
    hardware_i2c
)

target_include_directories(galton_board PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

pico_add_extra_outputs(galton_board)