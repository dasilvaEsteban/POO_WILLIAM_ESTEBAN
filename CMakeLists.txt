# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("POO_WILLIAM_ESTEBAN")	

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




if(MSVC)
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/SFML/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
    add_compile_options(
    $<$<CONFIG:>:/MT> #---------|
    $<$<CONFIG:Debug>:/MTd> #---|--  Statically link the runtime libraries
    $<$<CONFIG:Release>:/MT> #--|
    )
endif()

find_package (Threads REQUIRED)
find_package(SFML 2.5 COMPONENTS window system graphics REQUIRED)

set(SFML_LIBS sfml-graphics sfml-window sfml-system Threads::Threads)


# Incluez les sous-projets.
add_subdirectory ("POO_WILLIAM_ESTEBAN")
