#include "bus.hpp"
#include "car.hpp"
#include "pieton.hpp"

Bus::Bus(float x, float y, float angle, float speed, float patern)
    : x(x), y(y), angle(angle), speed(speed), patern(patern), initangle(angle)
{}

float Bus::getX() const {
    return x;
}

float Bus::getY() const {
    return y;
}

float Bus::getAngle() const {
    return angle;
}

float Bus::getinitAngle() const {
    return initangle;
}

float Bus::getSpeed() const {
    return speed;
}

float Bus::getPatern() const {
    return patern;
}

void Bus::move() {
    // D�place le bus en fonction de son angle et de sa vitesse
    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
}

void Bus::turnLeft() {
    // Diminue l'angle pour effectuer un virage � gauche
    angle -= speed / 4.2f; // Virage � gauche ajust� selon la vitesse
    if (angle >= initangle - 91 && angle <= initangle - 90) {
        angle = initangle - 90; // Limite pour un virage � gauche
    }
}

void Bus::turnRight() {
    // Augmente l'angle pour effectuer un virage � droite
    angle += speed / 1.8f; // Virage � droite plus rapide
    if (angle <= initangle + 91 && angle >= initangle + 90) {
        angle = initangle + 90; // Limite pour un virage � droite
    }
}

void Bus::speedUp() {
    // Augmente la vitesse du bus jusqu'� une limite sup�rieure
    if (speed < 2.0f)
        speed += 0.1f;
}

void Bus::speedDown() {
    // R�duit la vitesse du bus, sans descendre en dessous de z�ro
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}

float Bus::distanceTo(const Bus& other) const {
    // Calcul des distances entre deux bus
    float dx = other.x - x;
    float dy = y - other.y;

    // D�termine la direction actuelle du bus
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projette les coordonn�es sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Distance lat�rale � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Si le bus est derri�re (dotProduct < 10), retourne une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tol�rance pour la largeur de la trajectoire
    float trajectoryTolerance = 40.0f;

    // Retourne la distance frontale si le bus est sur la trajectoire
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourne une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Bus::distanceToPiet(const Pieton& other) const {
    // Calcul de la distance entre le bus et un pi�ton
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // D�termine la direction actuelle du bus
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projette les coordonn�es sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Distance lat�rale � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Si le pi�ton est derri�re le bus, retourne une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Largeur tol�r�e pour consid�rer que le pi�ton est sur la trajectoire
    float trajectoryTolerance = 40.0f;

    // Si le pi�ton est sur la trajectoire, retourne la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourne une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Bus::distanceToCar(const Car& other) const {
    // Calcul de la distance entre le bus et une voiture
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // D�termine la direction actuelle du bus
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projette les coordonn�es sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Distance lat�rale � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);

    // Si la voiture est derri�re le bus, retourne une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Largeur tol�r�e pour consid�rer que la voiture est sur la trajectoire
    float trajectoryTolerance = 40.0f;

    // Si la voiture est sur la trajectoire, retourne la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourne une distance infinie
    return std::numeric_limits<float>::infinity();
}