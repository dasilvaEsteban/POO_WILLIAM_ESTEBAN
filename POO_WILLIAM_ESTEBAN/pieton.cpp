#include "pieton.hpp"
#include "bus.hpp"
#include "car.hpp"

Pieton::Pieton(const float x, const float y, const float angle, const float speed)
    : x(x), y(y), angle(angle), speed(speed) {}

float Pieton::getX() const {
    return x;
}

float Pieton::getY() const {
    return y;
}

float Pieton::getAngle() const {
    return angle;
}

float Pieton::getSpeed() const {
    return speed;
}

void Pieton::speedUp() {
    // Augmente la vitesse du piéton si elle est inférieure à 2
    if (speed < 2.f)
        speed += 0.1f;
}

void Pieton::speedDown() {
    // Réduit la vitesse du piéton jusqu'à un minimum de 0
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}

void Pieton::move() {
    // Déplace le piéton en fonction de son angle et de sa vitesse
    x += speed * std::cos(angle * M_PI / 180.0f); // Conversion de l'angle en radians
    y += speed * std::sin(angle * M_PI / 180.0f);
}

float Pieton::distanceTo(const Pieton& other) const {
    // Calcul des différences de position entre les piétons
    float dx = other.x - x;
    float dy = y - other.y;

    // Calcul de la direction actuelle du piéton
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Calcul de la distance latérale par rapport à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;

    // Si le point projeté est derrière, retourner une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'un piéton est sur la trajectoire
    float trajectoryTolerance = 10.0f;

    // Si le piéton est sur la trajectoire, retourner la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourner une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Pieton::distanceToCar(const Car& other) const {
    // Calcul des différences de position entre le piéton et la voiture
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // Calcul de la direction actuelle du piéton
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Calcul de la distance latérale par rapport à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;

    // Si le point projeté est derrière, retourner une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est sur la trajectoire
    float trajectoryTolerance = 15.0f;

    // Si la voiture est sur la trajectoire, retourner la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourner une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Pieton::distanceToBus(const Bus& other) const {
    // Calcul des différences de position entre le piéton et le bus
    float dx = other.getX() - x;
    float dy = y - other.getY();

    // Calcul de la direction actuelle du piéton
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);

    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;

    // Calcul de la distance latérale par rapport à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;

    // Si le point projeté est derrière, retourner une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'un bus est sur la trajectoire
    float trajectoryTolerance = 15.0f;

    // Si le bus est sur la trajectoire, retourner la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }

    // Sinon, retourner une distance infinie
    return std::numeric_limits<float>::infinity();
}
