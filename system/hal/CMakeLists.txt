target_include_directories(${ELF_FILE} 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx_hal.c
)