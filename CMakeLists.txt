#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(myproject)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
cmake_minimum_required(VERSION 2.6)
#Déclaration du projet
project(bgs-dev)
#Génération de la liste des fichiers sources
file(GLOB_RECURSE

source_files

src/*

)
#Déclaration de l'exécutable
include_directories(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
add_executable(bgs ${source_files})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics)
find_package(Boost COMPONENTS system filesystem serialization REQUIRED)
target_link_libraries(bgs ${SFML_LIBRARIES} ${Boost_LIBRARIES})
