cmake_minimum_required(VERSION 3.12)
project(MyGame)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -I${PROJECT_SOURCE_DIR}/Common/ -I${PROJECT_SOURCE_DIR}/VectorUtils/ -I${PROJECT_SOURCE_DIR}/Exception/ -I${PROJECT_SOURCE_DIR}/Common/Memcheck -I${PROJECT_SOURCE_DIR}/Common/Print -I${PROJECT_SOURCE_DIR}/VectorUtils/VectorBool")

set(EXECUTABLE_NAME "MyGame")
add_executable(${EXECUTABLE_NAME} main.cpp VectorUtils/vector.h VectorUtils/vector.hpp VectorUtils/VectorBool/vector_bool.h VectorUtils/VectorBool/vector_bool.cpp Common/err_codes.h Common/Memcheck/memleakdiag.cpp Common/Memcheck/memleakdiag.h Exception/MyExcp.cpp Exception/MyExcp.h Common/Print/print.h Common/Print/print.hpp Common/Print/print.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()