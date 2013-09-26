cmake_minimum_required(VERSION 2.6)
#Déclaration du projet
project(bgs-dev)
#Génération de la liste des fichiers sources
file(GLOB_RECURSE

source_files

src/*

)
#Déclaration de l'exécutable
include_directories(${SFML_INCLUDE_DIR})
add_executable(bgs ${source_files})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics)
target_link_libraries(bgs ${SFML_LIBRARIES})