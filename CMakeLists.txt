cmake_minimum_required(VERSION 3.12)
project(MyGame)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra \
-I${PROJECT_SOURCE_DIR}/Common/ \
-I${PROJECT_SOURCE_DIR}/GameObjects/FinalObjects \
-I${PROJECT_SOURCE_DIR}/GameObjects/FunctionalClasses \
-I${PROJECT_SOURCE_DIR}/GameObjects/MainSuperclass \
-I${PROJECT_SOURCE_DIR}/GameObjects/PseudoInterfaces \
-I${PROJECT_SOURCE_DIR}/GameObjects")

link_directories(/usr/local/lib/)

set(EXECUTABLE_NAME "MyGame")
add_executable(${EXECUTABLE_NAME} main.cpp Common/err_codes.h Common/RadVec.h Common/proj_macros.h GameEngine/GameEngine.cpp GameEngine/GameEngine.h GameObjects/characters.h GameObjects/MainSuperclass/GameObject.cpp GameObjects/MainSuperclass/GameObject.h GameObjects/FunctionalClasses/DrawableObject.cpp GameObjects/FunctionalClasses/DrawableObject.h GameObjects/FunctionalClasses/PhysicalObject.cpp GameObjects/FunctionalClasses/PhysicalObject.h GameObjects/PseudoInterfaces/StaticDrawObject.cpp GameObjects/PseudoInterfaces/StaticDrawObject.h GameObjects/FunctionalClasses/MoveableObject.cpp GameObjects/FunctionalClasses/MoveableObject.h GameObjects/PseudoInterfaces/PlayerableObject.cpp GameObjects/PseudoInterfaces/PlayerableObject.h GameObjects/FinalObjects/Bench.cpp GameObjects/FinalObjects/Bench.h GameObjects/FinalObjects/MainPlayer.cpp GameObjects/FinalObjects/MainPlayer.h GameObjects/FunctionalClasses/WithTargetObject.cpp GameObjects/FunctionalClasses/WithTargetObject.h GameObjects/PseudoInterfaces/EnemyObject.cpp GameObjects/PseudoInterfaces/EnemyObject.h)

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} -lsfml-graphics -lsfml-window -lsfml-system)

#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#find_package(SFML 2 REQUIRED system window graphics network audio)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
#endif()