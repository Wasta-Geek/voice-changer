# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("voice-changer")

include_directories(includes)
set(SOURCE_FILES
sources/main.cpp)

add_executable(${PROJECT_NAME}  ${SOURCE_FILES})

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