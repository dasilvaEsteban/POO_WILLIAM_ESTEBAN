#include "bus.hpp"
#include "car.hpp"
#include "pieton.hpp"

Bus::Bus(float x, float y, float angle, float speed, float patern)
    : x(x), y(y), angle(angle), speed(speed), patern(patern), initangle(angle)
{}

float
Bus::getX() const
{
    return x;
}

float
Bus::getY() const
{
    return y;
}

float
Bus::getAngle() const
{
    return angle;
}

float
Bus::getinitAngle() const
{
    return initangle;
}

float
Bus::getSpeed() const
{
    return speed;
}

float
Bus::getPatern() const
{
    return patern;
}


void
Bus::move()
{
    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
}

void
Bus::turnLeft()
{
    angle -= speed / 4.2f;
    if (angle >= initangle - 91 and angle <= initangle - 90) {
        angle = initangle - 90;
    }
}

void
Bus::turnRight()
{
    angle += speed / 1.8f;
    if (angle <= initangle + 91 and angle >= initangle + 90) {
        angle = initangle + 90;
    }
}

void
Bus::speedUp()
{
    if (speed < 2.0f)
        speed += 0.1f;
}

void
Bus::speedDown()
{
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}


float Bus::distanceTo(const Bus& other) const {
    // Calcul des diff�rences de position
    float dx = other.x - x;
    float dy = y - other.y;


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projet� est derri�re (dotProduct < 0) avec une limite d'imprecision, retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tol�rance pour consid�rer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en lat�ral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}

float Bus::distanceToPiet(const Pieton& other) const {
    // Calcul des diff�rences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projet� est derri�re (dotProduct < 0), retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tol�rance pour consid�rer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en lat�ral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}


float Bus::distanceToCar(const Car& other) const {
    // Calcul des diff�rences de position
    float dx = other.getX() - x;
    float dy = y - other.getY();


    // Direction de la voiture actuelle
    float directionX = cos(angle * M_PI / 180.0);
    float directionY = -sin(angle * M_PI / 180.0);


    // Projection du vecteur (dx, dy) sur la direction
    float dotProduct = dx * directionX + dy * directionY;



    // Calcul de la distance perpendiculaire � la trajectoire
    float crossProduct = dx * directionY - dy * directionX;
    float lateralDistance = std::abs(crossProduct);



    // Si le point projet� est derri�re (dotProduct < 0) avec une limite d'imprecision, retournez une distance infinie
    if (dotProduct < 10) {
        return std::numeric_limits<float>::infinity();
    }

    // Tol�rance pour consid�rer qu'une voiture est "sur la trajectoire"
    float trajectoryTolerance = 40.0f; // Ajustez en fonction de la largeur acceptable

    // Si la voiture est sur la trajectoire (proche en lat�ral), retournez la distance frontale
    if (lateralDistance <= trajectoryTolerance) {
        return dotProduct;
    }
    // Sinon, retournez une distance infinie
    return std::numeric_limits<float>::infinity();
}