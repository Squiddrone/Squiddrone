cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

set(APPLICATION_NAME SquidDrone)
project(${APPLICATION_NAME} LANGUAGES CXX C ASM)

#for debugging purposes turn this ON
set(CMAKE_VERBOSE_MAKEFILE OFF)

option(GOOGLE_TESTS "Build the Unittests" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(BUILD_DOC "Build documentation" OFF)

message(STATUS "Google Tests: ${GOOGLE_TESTS}")
message(STATUS "Coverage reporting: ${CODE_COVERAGE}")
message(STATUS "Generate documentation: ${BUILD_DOC}")
message(STATUS "Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# generate documentation
if(BUILD_DOC)
    include(doxygen)
endif()

if(NOT GOOGLE_TESTS)

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
            ARM_MATH_CM4
    )

    find_library(DSP_LIB arm_cortexM4lf_math
        REQUIRED
        HINTS "${CMAKE_CURRENT_SOURCE_DIR}/system/cmsis/dsp"
    )

    target_link_libraries(${ELF_FILE} "${DSP_LIB}")

    add_subdirectory(drivers)
    add_subdirectory(src)
    add_subdirectory(startup)
    add_subdirectory(system)

    add_custom_target(${ELF_FILE}-size DEPENDS ${ELF_FILE} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${ELF_FILE})
    add_custom_target(${LSS_FILE} DEPENDS ${ELF_FILE} COMMAND ${CMAKE_OBJDUMP} -S ${ELF_FILE} > ${LSS_FILE})
    add_custom_target(${HEX_FILE} DEPENDS ${ELF_FILE} COMMAND arm-none-eabi-objcopy -O ihex ${ELF_FILE} ${HEX_FILE})
    add_custom_target(${BIN_FILE} DEPENDS ${ELF_FILE} COMMAND arm-none-eabi-objcopy -O binary ${ELF_FILE} ${BIN_FILE})
    add_custom_target(${APPLICATION_NAME} ALL DEPENDS ${ELF_FILE}-size ${BIN_FILE} ${HEX_FILE} ${LSS_FILE})

else()
    if(CODE_COVERAGE)
        set(CMAKE_BUILD_TYPE "Debug")
        include(CodeCoverage)
        APPEND_COVERAGE_COMPILER_FLAGS()
    endif(CODE_COVERAGE)

    enable_testing()
    add_subdirectory(tests)
endif()