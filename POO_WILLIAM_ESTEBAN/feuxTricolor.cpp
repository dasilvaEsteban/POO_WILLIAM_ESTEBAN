#include "feuxTricolor.hpp"

sf::Vector2f rotateVector(const sf::Vector2f& vec, float angleDegrees) {
    float angleRadians = angleDegrees * 3.141592653589793f / 180.0f; // Conversion degr�s -> radians
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
        // Dimensions du bo�tier
        body.setSize(sf::Vector2f(90, 30));
        body.setFillColor(sf::Color(20, 20, 20)); // Gris fonc� pour le bo�tier
        body.setPosition(x, y);

        // Lumi�res
        float radius = 10.0f;

        // Lumi�re rouge
        redLight.setRadius(radius);
        redLight.setFillColor(sf::Color(100, 0, 0)); // Lumi�re �teinte par d�faut
        redLight.setPosition(x + 5, y + 5);

        // Lumi�re orange
        orangeLight.setRadius(radius);
        orangeLight.setFillColor(sf::Color(64, 32, 0)); // Lumi�re �teinte par d�faut
        orangeLight.setPosition(x + 35, y + 5);

        // Lumi�re verte
        greenLight.setRadius(radius);
        greenLight.setFillColor(sf::Color(0, 100, 0)); // Lumi�re �teinte par d�faut
        greenLight.setPosition(x + 65, y + 5);
    }
    else {
        // Dimensions du bo�tier
        body.setSize(sf::Vector2f(30, 90));
        body.setFillColor(sf::Color(20, 20, 20)); // Gris fonc� pour le bo�tier
        body.setPosition(x, y);

        // Lumi�res
        float radius = 10.0f;

        // Lumi�re rouge
        redLight.setRadius(radius);
        redLight.setFillColor(sf::Color(100, 0, 0)); // Lumi�re �teinte par d�faut
        redLight.setPosition(x + 5, y + 5);

        // Lumi�re orange
        orangeLight.setRadius(radius);
        orangeLight.setFillColor(sf::Color(64, 32, 0)); // Lumi�re �teinte par d�faut
        orangeLight.setPosition(x + 5, y + 35);

        // Lumi�re verte
        greenLight.setRadius(radius);
        greenLight.setFillColor(sf::Color(0, 100, 0)); // Lumi�re �teinte par d�faut
        greenLight.setPosition(x + 5, y + 65);
    }
}

// M�thode pour d�finir la couleur active
void TrafficLightDrawable::setColor(Traffic_color color) {
    // Tout �teindre par d�faut
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



// M�thode pour dessiner le feu
void TrafficLightDrawable::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(redLight);
    window.draw(orangeLight);
    window.draw(greenLight);
}
