cmake_minimum_required(VERSION 3.12)
project(MyGame)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra \
-I${PROJECT_SOURCE_DIR}/Common/ \
-I${PROJECT_SOURCE_DIR}/GameObjects")

link_directories(/usr/local/lib/)

set(EXECUTABLE_NAME "MyGame")
add_executable(${EXECUTABLE_NAME} main.cpp Common/err_codes.h GameObjects/CharacterObject.h Common/RadVec.h GameObjects/Player.cpp GameObjects/Player.h GameObjects/TrainInspector.cpp GameObjects/TrainInspector.h GameObjects/CharacterObject.cpp Common/proj_macros.h GameObjects/Passenger.cpp GameObjects/Passenger.h GameEngine/GameEngine.cpp GameEngine/GameEngine.h GameObjects/characters.h GameObjects/GameObject.cpp GameObjects/GameObject.h GameObjects/DrawableObject.cpp GameObjects/DrawableObject.h GameObjects/PhysicalObject.cpp GameObjects/PhysicalObject.h GameObjects/StaticDrawObject.cpp GameObjects/StaticDrawObject.h GameObjects/MoveableObject.cpp GameObjects/MoveableObject.h GameObjects/PlayerableObject.cpp GameObjects/PlayerableObject.h GameObjects/Bench.cpp GameObjects/Bench.h)

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} -lsfml-graphics -lsfml-window -lsfml-system)

#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#find_package(SFML 2 REQUIRED system window graphics network audio)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
#endif()