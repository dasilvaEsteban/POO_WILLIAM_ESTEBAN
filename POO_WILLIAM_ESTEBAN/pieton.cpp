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


void Pieton::move() {
    // Déplacer le piéton dans la direction de son angle
    x += speed * std::cos(angle * M_PI / 180.0f); // Conversion de l'angle en radians
    y += speed * std::sin(angle * M_PI / 180.0f);
}

void Pieton::speedUp() {
    if (speed < 2.f)
        speed += 0.1f;
}

void Pieton::speedDown() {
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}



float Pieton::distanceTo(const Pieton& other) const {
    // Calcul des différences de position
    float dx = other.x - x;
    float dy = y - other.y;


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;



    // Si le point projeté est derrière (dotProduct < 0), retournez une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 10.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Pieton::distanceToCar(const Car& other) const {
    // Calcul des différences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;



    // Si le point projeté est derrière (dotProduct < 0), retournez une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 15.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Pieton::distanceToBus(const Bus& other) const {
    // Calcul des différences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY + dy * directionX;
    float lateralDistance = std::abs(crossProduct) - 18;



    // Si le point projeté est derrière (dotProduct < 0), retournez une distance infinie
    if (dotProduct < 0) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 15.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}