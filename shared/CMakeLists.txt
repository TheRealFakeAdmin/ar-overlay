add_library(shared
    geo_math.c
    logging.c
)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
