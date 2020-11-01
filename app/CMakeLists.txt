# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("voice-changer")

include_directories(includes)

set(SOURCE_FILES
sources/main.cpp
sources/VoiceChangerApp.cpp
sources/PortAudioWrapper.cpp
sources/HotKeyManager.cpp
sources/FilePlayerManager.cpp)

set(INCLUDE_FILES
includes/VoiceChangerApp.hpp
includes/PortAudioWrapper.hpp
includes/HotKeyManager.hpp
includes/AvailableEffects.hpp
includes/FilePlayerManager.hpp "includes/FileFormats.hpp")

add_executable(${PROJECT_NAME}  ${SOURCE_FILES} ${INCLUDE_FILES})

set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../resources)
set(DEPENDENCIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

# PortAudio
set(PORTAUDIO_DIR_NAME "PortAudio")

include_directories(${DEPENDENCIES_PATH}/${PORTAUDIO_DIR_NAME}/includes)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_PATH}/${PORTAUDIO_DIR_NAME}/lib/portaudio_x64.lib)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${DEPENDENCIES_PATH}/${PORTAUDIO_DIR_NAME}/lib/portaudio_x64.dll
                ${CMAKE_CURRENT_BINARY_DIR}/portaudio_x64.dll)

# Libsndfile
set(LIBSNDFILE_DIR_NAME "libsndfile")


include_directories(${DEPENDENCIES_PATH}/${LIBSNDFILE_DIR_NAME}/includes)
target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES_PATH}/${LIBSNDFILE_DIR_NAME}/lib/libsndfile-1.lib)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${DEPENDENCIES_PATH}/${LIBSNDFILE_DIR_NAME}/lib/libsndfile-1.dll
                ${CMAKE_CURRENT_BINARY_DIR}/libsndfile-1.dll)

add_definitions(-DRESOURCES_FOLDER_PATH="${RESOURCES_PATH}")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
