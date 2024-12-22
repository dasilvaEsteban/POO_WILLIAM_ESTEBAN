#include "feuxTricolor.hpp"

sf::Vector2f rotateVector(const sf::Vector2f& vec, float angleDegrees) {
    float angleRadians = angleDegrees * 3.141592653589793f / 180.0f; // Conversion degrés -> radians
    float cosTheta = std::cos(angleRadians);
    float sinTheta = std::sin(angleRadians);

    return sf::Vector2f(
        vec.x * cosTheta - vec.y * sinTheta,
        vec.x * sinTheta + vec.y * cosTheta
    );
}


// Constructeur
TrafficLightDrawable::TrafficLightDrawable(float x, float y, bool z) { // z pour l'orientation du feux (vertical = false, horizontal = true)
    if (z) {
        // Dimensions du boîtier
        body.setSize(sf::Vector2f(90, 30));
        body.setFillColor(sf::Color(20, 20, 20)); // Gris foncé pour le boîtier
        body.setPosition(x, y);

        // Lumières
        float radius = 10.0f;

        // Lumière rouge
        redLight.setRadius(radius);
        redLight.setFillColor(sf::Color(100, 0, 0)); // Lumière éteinte par défaut
        redLight.setPosition(x + 5, y + 5);

        // Lumière orange
        orangeLight.setRadius(radius);
        orangeLight.setFillColor(sf::Color(64, 32, 0)); // Lumière éteinte par défaut
        orangeLight.setPosition(x + 35, y + 5);

        // Lumière verte
        greenLight.setRadius(radius);
        greenLight.setFillColor(sf::Color(0, 100, 0)); // Lumière éteinte par défaut
        greenLight.setPosition(x + 65, y + 5);
    }
    else {
        // Dimensions du boîtier
        body.setSize(sf::Vector2f(30, 90));
        body.setFillColor(sf::Color(20, 20, 20)); // Gris foncé pour le boîtier
        body.setPosition(x, y);

        // Lumières
        float radius = 10.0f;

        // Lumière rouge
        redLight.setRadius(radius);
        redLight.setFillColor(sf::Color(100, 0, 0)); // Lumière éteinte par défaut
        redLight.setPosition(x + 5, y + 5);

        // Lumière orange
        orangeLight.setRadius(radius);
        orangeLight.setFillColor(sf::Color(64, 32, 0)); // Lumière éteinte par défaut
        orangeLight.setPosition(x + 5, y + 35);

        // Lumière verte
        greenLight.setRadius(radius);
        greenLight.setFillColor(sf::Color(0, 100, 0)); // Lumière éteinte par défaut
        greenLight.setPosition(x + 5, y + 65);
    }
}

// Méthode pour définir la couleur active
void TrafficLightDrawable::setColor(Traffic_color color) {
    // Tout éteindre par défaut
    redLight.setFillColor(sf::Color(100, 0, 0));
    orangeLight.setFillColor(sf::Color(64, 32, 0));
    greenLight.setFillColor(sf::Color(0, 100, 0));

    // Allumer la couleur correspondante
    if (color == Traffic_color::red) {
        redLight.setFillColor(sf::Color::Red);
    }
    else if (color == Traffic_color::orange) {
        orangeLight.setFillColor(sf::Color(255, 165, 0)); // Orange vif
    }
    else if (color == Traffic_color::green) {
        greenLight.setFillColor(sf::Color::Green);
    }
}



// Méthode pour dessiner le feu
void TrafficLightDrawable::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(redLight);
    window.draw(orangeLight);
    window.draw(greenLight);
}
