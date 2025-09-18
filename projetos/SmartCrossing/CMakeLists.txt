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
set(PICO_BOARD pico_w CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName smart_light)

# Set any variables required for importing libraries
SET(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)

message("FreeRTOS Kernel located in ${FREERTOS_PATH}")

# Import those libraries
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName} C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${ProjectName}
   core/main.c
   utilities/neopixel.c
   utilities/ssd1306.c
   utilities/dhcp_server.c
   utilities/udp_util.c
   utilities/ble_connection.c
   utilities/traffic_light_control.c
   utilities/cpp_vl53l0x/VL53L0X.cpp
   utilities/cpp_vl53l0x/vl53l0x_wrapper.cpp
   tasks/traffic_lights_task.c
   tasks/sensor_task.c
   tasks/display_task.c
   tasks/ap_task.c
   tasks/sta_task.c
   tasks/ble_task.c
)
 
pico_generate_pio_header(smart_light ${CMAKE_CURRENT_LIST_DIR}/utilities/include/ws2812b.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${ProjectName} 0)
pico_enable_stdio_usb(${ProjectName} 1)

target_include_directories(${ProjectName} PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}
   ${CMAKE_CURRENT_LIST_DIR}/inc
   ${CMAKE_CURRENT_LIST_DIR}/core
   ${CMAKE_CURRENT_LIST_DIR}/utilities/include
   ${CMAKE_CURRENT_LIST_DIR}/utilities/cpp_vl53l0x
   ${FREERTOS_PATH}/include
   ${FREERTOS_PATH}/include/fonts
   ${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040
)

pico_set_program_name(${ProjectName} "smart_light")
pico_set_program_version(${ProjectName} "0.1")

target_compile_definitions(${ProjectName} PRIVATE
    PICO_BOARD=\"pico_w\"
    CYW43_ENABLE_BLUETOOTH=1
)

target_link_libraries(${ProjectName}
   pico_stdlib
   hardware_gpio
   FreeRTOS-Kernel-Heap4
   pico_stdlib
   pico_rand
   pico_lwip
   hardware_adc
   hardware_pwm 
   hardware_gpio
   hardware_i2c
   hardware_pio
   hardware_clocks
   pico_btstack_cyw43
   pico_btstack_ble
   pico_cyw43_arch_lwip_threadsafe_background
)

pico_configure_ip4_address(${ProjectName} PRIVATE
   CYW43_DEFAULT_IP_AP_ADDRESS 192.168.4.1
)

pico_add_extra_outputs(${ProjectName})

