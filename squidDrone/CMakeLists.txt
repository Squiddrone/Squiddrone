cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

set(APPLICATION_NAME SquidDrone)
project(${APPLICATION_NAME} LANGUAGES CXX C ASM)

#for debugging purposes turn this ON
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(ELF_FILE ${APPLICATION_NAME}.elf)
set(BIN_FILE ${APPLICATION_NAME}.bin)
set(HEX_FILE ${APPLICATION_NAME}.hex)
set(MAP_FILE ${APPLICATION_NAME}.map)
set(LSS_FILE ${APPLICATION_NAME}.lss)

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

add_custom_target(${ELF_FILE}-size DEPENDS ${ELF_FILE} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${ELF_FILE})
add_custom_target(${LSS_FILE} DEPENDS ${ELF_FILE} COMMAND ${CMAKE_OBJDUMP} -S ${ELF_FILE} > ${LSS_FILE})
add_custom_target(${HEX_FILE} DEPENDS ${ELF_FILE} COMMAND ${CMAKE_OBJCOPY} -O ihex ${ELF_FILE} ${HEX_FILE})
add_custom_target(${BIN_FILE} DEPENDS ${ELF_FILE} COMMAND ${CMAKE_OBJCOPY} -O binary ${ELF_FILE} ${BIN_FILE})
add_custom_target(${APPLICATION_NAME} ALL DEPENDS ${ELF_FILE}-size ${BIN_FILE} ${HEX_FILE} ${LSS_FILE})

