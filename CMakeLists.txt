cmake_minimum_required(VERSION 3.12)
project(Belote)

set(CMAKE_CXX_STANDARD 14)

# Add your source files here
set(SOURCES
    src/Carte.cpp
    src/Carte.h
    src/Joueur.cpp
    src/Joueur.h
    src/Table.cpp
    src/Table.h
    src/Equipe.cpp
    src/Equipe.h
    src/PaquetDeCarte.cpp
    src/PaquetDeCarte.h
    src/MainJoueur.cpp
    src/MainJoueur.h
    src/enums.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

add_executable(Belote ${SOURCES} src/main.cpp)
add_executable(Graphique ${SOURCES} src/mainGraphique.cpp)

# Add your include directories here
target_include_directories(Belote PRIVATE src)
target_include_directories(Graphique PRIVATE src)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Link required libraries for Graphique executable
target_link_libraries(Graphique sfml-graphics sfml-audio)
target_link_libraries(Belote sfml-graphics sfml-audio)

