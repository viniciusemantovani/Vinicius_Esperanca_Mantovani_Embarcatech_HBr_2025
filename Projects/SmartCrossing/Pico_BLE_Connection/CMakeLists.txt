# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)

project(pico_ble_connection C CXX ASM)
pico_sdk_init()

add_executable(pico_ble_connection
    ble_connection.c
)

pico_set_program_name(pico_ble_connection "pico_ble_connection")
pico_set_program_version(pico_ble_connection "0.1")

# Habilita UART e USB para logs
pico_enable_stdio_uart(pico_ble_connection 1)
pico_enable_stdio_usb(pico_ble_connection 1)

target_compile_definitions(pico_ble_connection PRIVATE
    PICO_BOARD=\"pico_w\"
    CYW43_ENABLE_BLUETOOTH=1
)

target_link_libraries(pico_ble_connection
    pico_stdlib
    hardware_gpio
    pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
)

target_include_directories(pico_ble_connection PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico_ble_connection)
