cmake_minimum_required(VERSION 3.15)
project(TableTennisRobotInterface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

add_executable(tt_robot
    src/main.cpp
    src/routine_manager.cpp
    src/vision_pipeline.cpp
    src/trajectory.cpp
    src/robot_controller.cpp
)

target_include_directories(tt_robot PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(tt_robot PRIVATE ${OpenCV_LIBS})

if(MSVC)
    target_compile_options(tt_robot PRIVATE /W4)
else()
    target_compile_options(tt_robot PRIVATE -Wall -Wextra -Wpedantic)
endif()
