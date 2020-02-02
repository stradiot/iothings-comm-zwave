cmake_minimum_required (VERSION 3.0)

project (iothings-zwave)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} libpaho-mqtt3as.so)
target_link_libraries(${PROJECT_NAME} libpaho-mqttpp3.so)
