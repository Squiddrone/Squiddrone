
include(AddGoogleTest)
include(AddTestPackage)

add_subdirectory(com)
add_subdirectory(i2c)
add_subdirectory(imu)
add_subdirectory(propulsion)
add_subdirectory(spi)
add_subdirectory(types)
add_subdirectory(utilities)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest
    )
endif(CODE_COVERAGE)
