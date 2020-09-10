cmake_minimum_required(VERSION 3.8)
project(SPACE_PONG)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "PredefinedTargets")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(CMAKE_CONFIGURATION_TYPES 
    Release 
    Debug 
    CACHE TYPE INTERNAL FORCE )

set(SOURCE_PROJECT_DIR Source) 
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/ThirdParty) 
set(BINARY_DIR ${CMAKE_BINARY_DIR}/Binaries)


# Project source files
set(PROJECT_SOURCE_FILES 
    "${SOURCE_PROJECT_DIR}/COGAIController.cpp"
    "${SOURCE_PROJECT_DIR}/COGAIController.h"
    "${SOURCE_PROJECT_DIR}/COGBounce.cpp"
    "${SOURCE_PROJECT_DIR}/COGBounce.h"
    "${SOURCE_PROJECT_DIR}/COGBoxShape.cpp"
    "${SOURCE_PROJECT_DIR}/COGBoxShape.h"
    "${SOURCE_PROJECT_DIR}/COGCircleShape.cpp"
    "${SOURCE_PROJECT_DIR}/COGCircleShape.h"
    "${SOURCE_PROJECT_DIR}/COGController.cpp"
    "${SOURCE_PROJECT_DIR}/COGController.h"
    "${SOURCE_PROJECT_DIR}/COGPhysics.cpp"
    "${SOURCE_PROJECT_DIR}/COGPhysics.h"
    "${SOURCE_PROJECT_DIR}/COGPlayerController.cpp"
    "${SOURCE_PROJECT_DIR}/COGPlayerController.h"
    "${SOURCE_PROJECT_DIR}/COGScore.cpp"
    "${SOURCE_PROJECT_DIR}/COGScore.h"
    "${SOURCE_PROJECT_DIR}/COGShape.cpp"
    "${SOURCE_PROJECT_DIR}/COGShape.h"
    "${SOURCE_PROJECT_DIR}/COGTransform.h"
    "${SOURCE_PROJECT_DIR}/COGTransform.cpp"
    "${SOURCE_PROJECT_DIR}/Component.h"
    "${SOURCE_PROJECT_DIR}/GameObject.h"
    "${SOURCE_PROJECT_DIR}/GameObject.cpp"
    "${SOURCE_PROJECT_DIR}/Game.cpp"
    "${SOURCE_PROJECT_DIR}/Game.h"
    "${SOURCE_PROJECT_DIR}/GameTypes.h"
    "${SOURCE_PROJECT_DIR}/GameInterface.h"
    "${SOURCE_PROJECT_DIR}/IPhysicsCollisionEvent.h"
    "${SOURCE_PROJECT_DIR}/Main.cpp"
    "${SOURCE_PROJECT_DIR}/World.cpp"
    "${SOURCE_PROJECT_DIR}/World.h"
)

# Organize filters based on directory structure
source_group( TREE ${CMAKE_SOURCE_DIR} FILES PROJECT_SOURCE_FILES)
# Set Debug binary files directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR}/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR}/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR}/Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR}/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR}/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR}/Debug)

add_executable(SpacePong WIN32 ${PROJECT_SOURCE_FILES})


target_link_libraries(
SpacePong 
    optimized
    "${THIRD_PARTY_DIR}/EngineX/lib/EngineX.lib"
    debug
    "${THIRD_PARTY_DIR}/EngineX/lib/EngineXd.lib"
    general
    "${THIRD_PARTY_DIR}/SDL/2.0.3/lib/x86/SDL2.lib"
    "${THIRD_PARTY_DIR}/SDL/gfx-1.0.1/lib/SDL2-gfx.lib"
    "${THIRD_PARTY_DIR}/SDL/ttf-2.0.12/lib/SDL2-ttf.lib"
    winmm.lib
    
)

target_include_directories(
SpacePong
    PUBLIC
        ${SOURCE_PROJECT_DIR}
        "${THIRD_PARTY_DIR}/EngineX/include"
        "${THIRD_PARTY_DIR}/SDL/2.0.3/include"
        "${THIRD_PARTY_DIR}/SDL/gfx-1.0.1"
        "${THIRD_PARTY_DIR}/SDL/ttf-2.0.12/include"
)

set_property(TARGET SpacePong PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:SpacePong>)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SpacePong)

add_custom_command(
TARGET SpacePong 
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${THIRD_PARTY_DIR}/SDL/2.0.3/lib/x86/SDL2.dll"
        "${THIRD_PARTY_DIR}/SDL/gfx-1.0.1/lib/SDL2-gfx.dll"
        "${THIRD_PARTY_DIR}/SDL/ttf-2.0.12/lib/SDL2-ttf.dll"
        "${THIRD_PARTY_DIR}/FreeType/lib/libfreetype-6.dll"
        "${THIRD_PARTY_DIR}/ZLib/lib/zlib1.dll"
    $<TARGET_FILE_DIR:SpacePong>)

    
add_custom_command( TARGET SpacePong  PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets/Fonts/
    $<TARGET_FILE_DIR:SpacePong>)