add_executable(ground_station
    src/main.c
    src/sensors/gps_fake.c
    src/render/overlay.c
)

target_link_libraries(ground_station
    raylib
    shared
    m
)

target_include_directories(ground_station PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/shared
)
