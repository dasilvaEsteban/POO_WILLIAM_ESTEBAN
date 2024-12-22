#include "car.hpp"
#include "bus.hpp"
#include "pieton.hpp"

Car::Car(float x, float y, float angle, float speed, float patern)
    : x(x), y(y), angle(angle), speed(speed), patern(patern), initangle(angle)
{}

float
Car::getX() const
{
    return x;
}

float
Car::getY() const
{
    return y;
}

float
Car::getAngle() const
{
    return angle;
}

float
Car::getinitAngle() const
{
    return initangle;
}

float
Car::getSpeed() const
{
    return speed;
}

float
Car::getPatern() const
{
    return patern;
}


void
Car::move()
{
    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
}

void
Car::turnLeft()
{
    angle -= speed / 3.0f;
    if (angle >= initangle - 91 and angle <= initangle - 90) {
        angle = initangle - 90;
    }
}

void
Car::turnRight()
{
    angle += speed / 3.0f;
    if (angle <= initangle + 91 and angle >= initangle + 90) {
        angle = initangle + 90;
    }
}

void
Car::speedUp()
{
    if (speed < 3.0f)
        speed += 0.1f;
}

void
Car::speedDown()
{
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}


float Car::distanceTo(const Car& other) const {
    // Calcul des différences de position
    float dx = other.x - x;
    float dy = y - other.y;


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projeté est derrière (dotProduct < 0) avec une limite d'imprecision, retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Car::distanceToPiet(const Pieton& other) const {
    // Calcul des différences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projeté est derrière (dotProduct < 0), retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Car::distanceToBus(const Bus& other) const {
    // Calcul des différences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire à la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projeté est derrière (dotProduct < 0) avec une limite d'imprecision, retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tolérance pour considérer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en latéral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}