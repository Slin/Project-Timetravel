cmake_minimum_required(VERSION 3.4)
project(Timetravel)

set(EXECUTABLE_NAME "Timetravel")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11")

set(SOURCE_FILES
        source/main.cpp
        source/EntityManager.cpp
        source/EntityManager.h
        source/Entity.h
        source/World.cpp
        source/World.h
        source/ParticleEmitter.cpp
        source/ParticleEmitter.h
        source/TexturePool.cpp
        source/TexturePool.h
        source/SoundPool.cpp
        source/SoundPool.h
        source/PlayerEntity.cpp
        source/PlayerEntity.h
        source/Math.h
        source/Math.cpp
        source/Dialog.h
        source/Dialog.cpp
        source/KeyEntity.h
        source/KeyEntity.cpp
        source/Actor.cpp
        source/Actor.h
        source/Background.h
        source/Background.cpp
        source/Clouds.cpp
        source/Clouds.h
        source/LoadingScreen.cpp
        source/LoadingScreen.h
        source/Widget.h source/GUIManager.cpp source/GUIManager.h source/ContactListener.cpp source/ContactListener.h source/ContactListener.cpp source/NPC.cpp source/NPC.h source/Altar.cpp source/Altar.h source/ActorEmitter.cpp source/ActorEmitter.h source/PulsatingLight.cpp source/PulsatingLight.h)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Detect and add BOX2D
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARIES})
endif()

if(APPLE)
    SET(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -w")
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
