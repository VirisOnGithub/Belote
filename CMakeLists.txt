cmake_minimum_required(VERSION 3.12)
project(Belote)

set(CMAKE_CXX_STANDARD 14)

# Add your source files here
set(SOURCES
    src/main.cpp
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
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

add_executable(Belote ${SOURCES})

# Add your include directories here
target_include_directories(Belote PRIVATE src)

