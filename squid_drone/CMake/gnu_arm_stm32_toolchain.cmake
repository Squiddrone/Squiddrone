set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_VERSION   1)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHARED_FLAGS "-mcpu=cortex-m4 -g3 --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")
set(ADDITIONAL_SHARED_COMPILE_FLAGS "-DSTM32G431xx -DUSE_HAL_DRIVER  -c -O0 -ffunction-sections -fdata-sections -fstack-usage -Wall")

set(LINKER_FILE "${CMAKE_SOURCE_DIR}/STM32G431KBTX_FLASH.ld")
set(ADDITIONAL_LINK_FLAGS "-T${LINKER_FILE} --specs=nosys.specs -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group")

set(LINK_FLAGS "${SHARED_FLAGS} ${ADDITIONAL_LINK_FLAGS}" CACHE INTERNAL "linker flags")
set(CMAKE_C_FLAGS "${SHARED_FLAGS} ${ADDITIONAL_SHARED_COMPILE_FLAGS} -std=gnu11" CACHE INTERNAL "C flags")
set(CMAKE_CXX_FLAGS "${SHARED_FLAGS} ${ADDITIONAL_SHARED_COMPILE_FLAGS} -std=gnu++14 -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wconversion" CACHE INTERNAL "C++ flags")
set(CMAKE_ASM_FLAGS "${SHARED_FLAGS} -c -x assembler-with-cpp " CACHE INTERNAL "Assembler flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

find_program(ARM_SIZE_EXECUTABLE arm-none-eabi-size)
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb)