#ifndef TRAFFIC_LIGHT_DRAWABLE_HPP
#define TRAFFIC_LIGHT_DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include "traffic_light.hpp" // Pour l'énumération Traffic_color

class TrafficLightDrawable {
private:
    sf::RectangleShape body;       // Boîtier du feu tricolore
    sf::CircleShape redLight;      // Lumière rouge
    sf::CircleShape orangeLight;   // Lumière orange
    sf::CircleShape greenLight;    // Lumière verte

public:
    // Constructeur : Initialise le feu à une position donnée
    TrafficLightDrawable(float x, float y, bool z);

    // Met à jour la couleur active du feu tricolore
    void setColor(Traffic_color color);

    // Dessine le feu dans la fenêtre SFML
    void draw(sf::RenderWindow& window);

};

#endif // TRAFFIC_LIGHT_DRAWABLE_HPP
