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

set(GRAPHIQUES
    src/Affichage.cpp
    src/Aff-static.cpp
    src/Affichage.h
    src/mainGraphique.cpp
    src/TableG.cpp
    src/CarteG.cpp
    src/MainJoueurG.cpp
    src/Affichage-bot.cpp
)

set(IMGUI
    src/imgui-master/imgui.cpp
    src/imgui-master/imgui.h
    src/imgui-master/imgui_draw.cpp
    src/imgui-master/imgui_widgets.cpp
    src/imgui-master/imgui_demo.cpp
    src/imgui-master/imgui_tables.cpp
    src/imgui-sfml/imgui-SFML.cpp
    src/imgui-sfml/imgui-SFML.h
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

add_executable(Belote ${SOURCES} src/main.cpp)
add_executable(Graphique ${SOURCES} ${IMGUI} ${GRAPHIQUES})

# Add your include directories here
target_include_directories(Belote PRIVATE src)
target_include_directories(Graphique PRIVATE src)

find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Link required libraries for Graphique executable
target_link_libraries(Graphique sfml-graphics sfml-audio OpenGL::GL)
target_link_libraries(Belote sfml-graphics sfml-audio)

