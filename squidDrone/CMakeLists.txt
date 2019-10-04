cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

set(APPLICATION_NAME SquidDrone)
project(${APPLICATION_NAME} LANGUAGES CXX C ASM)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ELF_FILE ${APPLICATION_NAME}.elf)

#all sources will be added with target_sources
add_executable(${ELF_FILE} "")

target_compile_definitions(${ELF_FILE}
    PRIVATE
        STM32G431xx
        USE_HAL_DRIVER
)

add_subdirectory(drivers)
add_subdirectory(src)
add_subdirectory(startup)
add_subdirectory(system)

