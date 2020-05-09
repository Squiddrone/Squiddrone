
target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cmsis_os2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/croutine.c
        ${CMAKE_CURRENT_SOURCE_DIR}/event_groups.c
        ${CMAKE_CURRENT_SOURCE_DIR}/list.c
        ${CMAKE_CURRENT_SOURCE_DIR}/queue.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stream_buffer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tasks.c
        ${CMAKE_CURRENT_SOURCE_DIR}/timers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/port.c
        ${CMAKE_CURRENT_SOURCE_DIR}/heap_4.c
)

target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)