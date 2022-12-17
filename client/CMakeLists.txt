cmake_minimum_required(VERSION 3.2)

project(client)

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIR})
include_directories("../common/")

add_executable(client main.cpp)

set_target_properties(client PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(client
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )