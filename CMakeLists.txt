cmake_minimum_required (VERSION 3.0)

project (iothings-zwave)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(SOURCES src/main.cpp src/mqtt_client.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} libpaho-mqtt3as.so)
target_link_libraries(${PROJECT_NAME} libpaho-mqttpp3.so)
