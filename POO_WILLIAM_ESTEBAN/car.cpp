#include "car.hpp"
#include "bus.hpp"
#include "pieton.hpp"

Car::Car(float x, float y, float angle, float speed, float patern)
    : x(x), y(y), angle(angle), speed(speed), patern(patern), initangle(angle)
{}

float Car::getX() const {
    return x;
}

float Car::getY() const {
    return y;
}

float Car::getAngle() const {
    return angle;
}

float Car::getSpeed() const {
    return speed;
}

float Car::getPatern() const {
    return patern;
}

float Car::getinitAngle() const {
    return initangle;
}

void Car::speedUp() {
    // Augmente la vitesse de la voiture si elle est en dessous de 3.0
    if (speed < 3.0f)
        speed += 0.1f;
}

void Car::speedDown() {
    // Diminue la vitesse, mais ne permet pas de descendre en dessous de 0
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}

void Car::turnLeft() {
    // Tourne la voiture � gauche proportionnellement � la vitesse
    angle -= speed / 3.0f;
    if (angle >= initangle - 91 && angle <= initangle - 90) {
        angle = initangle - 90; // Limite maximale pour un virage � gauche
    }
}

void Car::turnRight() {
    // Tourne la voiture � droite proportionnellement � la vitesse
    angle += speed / 3.0f;
    if (angle <= initangle + 91 && angle >= initangle + 90) {
        angle = initangle + 90; // Limite maximale pour un virage � droite
    }
}

void Car::move() {
    // D�place la voiture selon son angle et sa vitesse
    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
}

float Car::distanceTo(const Car& other) const {
    // Calcule la distance entre cette voiture et une autre voiture
    float dx = other.x - x;
    float dy = y - other.y;

    // D�termine la direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Distance lat�rale par rapport � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Si l'autre voiture est derri�re avec une tol�rance, retourne une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // V�rifie si l'autre voiture est dans une tol�rance d�finie pour la trajectoire
    float trajectoryTolerance = 40.0f;

    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct; // Distance frontale si sur la trajectoire
    }

    return std::numeric_limits<float>::infinity(); // Sinon, distance infinie
}

float Car::distanceToPiet(const Pieton& other) const {
    // Mesure la distance entre la voiture et un pi�ton
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // Direction de la voiture
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection pour mesurer la distance frontale
    float dotProduct = dx * directionX + dy * directionY;

    // Calcul de la distance lat�rale
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Retourne une distance infinie si le pi�ton est derri�re
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tol�rance pour consid�rer que le pi�ton est sur la trajectoire
    float trajectoryTolerance = 40.0f;

    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    return std::numeric_limits<float>::infinity();
}

float Car::distanceToBus(const Bus& other) const {
    // Calcule la distance entre la voiture et un bus
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // Direction actuelle de la voiture
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection du vecteur pour mesurer la distance
    float dotProduct = dx * directionX + dy * directionY;

    // Calcul de la distance lat�rale
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Si le bus est derri�re, retourne une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // V�rifie si le bus est dans la tol�rance pour la trajectoire
    float trajectoryTolerance = 40.0f;

    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct; // Distance frontale si sur la trajectoire
    }

    return std::numeric_limits<float>::infinity();
}
