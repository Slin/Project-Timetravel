cmake_minimum_required(VERSION 3.4)
project(Timetravel)
set(EXECUTABLE_NAME "Corra")

option(IOS "Create project for iOS (ON).")
set(SFML_ROOT "" CACHE STRING "Path to a folder containing the SFML libs.")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

if(UNIX AND (NOT APPLE))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(IOS)
    set(CMAKE_OSX_SYSROOT "iphoneos")
    set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")

    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.slindev.\${PRODUCT_NAME:identifier}")
    set(APP_TYPE MACOSX_BUNDLE)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11")
endif()

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
        source/ShroomDustParticle.cpp
        source/ShroomDustParticle.h
        source/Widget.h source/GUIManager.cpp source/GUIManager.h source/ContactListener.cpp source/ContactListener.h source/ContactListener.cpp source/NPC.cpp source/NPC.h source/Altar.cpp source/Altar.h source/ActorEmitter.cpp source/ActorEmitter.h source/PulsatingLight.cpp source/PulsatingLight.h source/Cutscene.cpp source/Cutscene.h source/FakeCharacter.cpp source/FakeCharacter.h source/Bookshelf.cpp source/Bookshelf.h source/Portal.cpp source/Portal.h)

if(IOS)
    add_executable(${EXECUTABLE_NAME} ${APP_TYPE} ${SOURCE_FILES} "other/Launch Screen.storyboard")
else()
    add_executable(${EXECUTABLE_NAME} ${APP_TYPE} ${SOURCE_FILES})
endif()

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
if(APPLE AND IOS)
    set(SFML_STATIC_LIBRARIES TRUE)
    find_package(SFML 2 REQUIRED main system window graphics audio)
else()
    find_package(SFML 2 REQUIRED system window graphics audio)
endif()
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
    if(NOT IOS)
        SET(CMAKE_EXE_LINKER_FLAGS "-w")
    else()
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES RESOURCE "${PROJECT_SOURCE_DIR}/other/Launch Screen.storyboard")
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/other/Info.plist")

        # Copy resources into the app bundle
        set(APP_NAME \${TARGET_BUILD_DIR}/\${FULL_PRODUCT_NAME}/assets)
        set(RES_DIR ${PROJECT_SOURCE_DIR}/assets)
        add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND cmake -E copy_directory ${RES_DIR} ${APP_NAME})
    endif()
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
