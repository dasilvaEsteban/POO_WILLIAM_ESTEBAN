#ifndef TRAFFIC_LIGHT_DRAWABLE_HPP
#define TRAFFIC_LIGHT_DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include "traffic_light.hpp" // Pour l'�num�ration Traffic_color

class TrafficLightDrawable {
private:
    sf::RectangleShape body;       // Bo�tier du feu tricolore
    sf::CircleShape redLight;      // Lumi�re rouge
    sf::CircleShape orangeLight;   // Lumi�re orange
    sf::CircleShape greenLight;    // Lumi�re verte

public:
    // Constructeur : Initialise le feu � une position donn�e
    TrafficLightDrawable(float x, float y, bool z);

    // Met � jour la couleur active du feu tricolore
    void setColor(Traffic_color color);

    // Dessine le feu dans la fen�tre SFML
    void draw(sf::RenderWindow& window);

};

#endif // TRAFFIC_LIGHT_DRAWABLE_HPP
