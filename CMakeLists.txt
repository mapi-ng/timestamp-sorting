cmake_minimum_required(VERSION 3.23.2)
project(timestamp-sorting)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
message(STATUS "Fetching googletest")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME}
    src/FrameLoader.cpp
    src/EventSorter.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)

add_executable(${PROJECT_NAME}-app
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}-app
    ${PROJECT_NAME}
)

include(CTest)
add_subdirectory(test)