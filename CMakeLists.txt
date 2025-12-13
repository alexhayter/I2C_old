cmake_minimum_required(VERSION 3.13)
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(pio_i2c_bus_scan C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(pio_i2c_bus_scan)

pico_generate_pio_header(pio_i2c_bus_scan ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

target_sources(pio_i2c_bus_scan PRIVATE
        i2c_bus_scan.c
        #i2c_bus_scan.hpp
        pio_i2c.c
        pio_i2c.h
        )

target_link_libraries(pio_i2c_bus_scan PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_i2c_bus_scan)

# add url via pico_set_program_url
#example_auto_set_url(pio_i2c_bus_scan)