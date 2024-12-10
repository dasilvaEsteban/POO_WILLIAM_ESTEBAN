# CMakeList.txt : projet CMake pour POO_WILLIAM_ESTEBAN, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (POO_WILLIAM_ESTEBAN "main.cpp"  "traffic_light.hpp" "traffic_light.cpp" "car.hpp" "car.cpp" "bus.cpp" "bus.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET POO_WILLIAM_ESTEBAN PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(POO_WILLIAM_ESTEBAN PRIVATE ${SFML_LIBS})
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
