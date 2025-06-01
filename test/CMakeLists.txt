cmake_minimum_required(VERSION 3.23.2)
project(SortingUnitTest)
include(CTest)

add_executable(${PROJECT_NAME}
    SortingUnitTest.cpp
)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    gtest_main
    timestamp-sorting
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/raw_data.dat
        ${CMAKE_CURRENT_SOURCE_DIR}/sorted_events.tsv
        $<TARGET_FILE_DIR:${PROJECT_NAME}>

)