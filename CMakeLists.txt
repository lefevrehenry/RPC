CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(prog)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# message("${CMAKE_CXX_FLAGS_DEBUG}")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address -fno-omit-frame-pointer")

set(HEADER_FILES
    client/client.h
    client/client_stub.h
    client/client_runtime.h

    server/server.h
    server/server_stub.h
    server/server_runtime.h

    common/commands.h
)

set(SOURCE_FILES
    client/client.cpp
    client/client_stub.cpp
    client/client_runtime.cpp

    server/server.cpp
    server/server_stub.cpp
    server/server_runtime.cpp

    common/commands.cpp
)

find_package(ZMQPP 4.2.0 MODULE REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES} ${HEADER_FILES})
add_executable(client_${PROJECT_NAME} client_main.cpp ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(client_${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE ZMQPP)
target_link_libraries(client_${PROJECT_NAME} PRIVATE ZMQPP)
