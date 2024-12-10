//#include "car.hpp"
//
//Car::Car(float x, float y, float angle, float speed, float patern)
//    : x(x), y(y), angle(angle), speed(speed), patern(patern)
//{}
//
//float
//Car::getX() const
//{
//    return x;
//}
//
//float
//Car::getY() const
//{
//    return y;
//}
//
//float
//Car::getAngle() const
//{
//    return angle;
//}
//
//float
//Car::getSpeed() const
//{
//    return speed;
//}
//
//float
//Car::getPatern() const
//{
//    return patern;
//}
//
//
//void
//Car::move()
//{
//    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
//    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
//}
//
//void
//Car::turnLeft()
//{
//    angle -= 2.f;
//}
//
//void
//Car::turnRight()
//{
//    angle += 2.f;
//}
//
//void
//Car::speedUp()
//{
//    if (speed < 3.f)
//        speed += 0.1f;
//}
//
//void
//Car::speedDown()
//{
//    if (speed > 0.f)
//        speed -= 0.1f;
//    else
//        speed = 0;
//}


#include "car.hpp"
#include <cmath> // Pour cos et sin
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Car::Car(float x, float y, float angle, float speed, float patern)
    : x(x), y(y), angle(angle), speed(speed), patern(patern),
    gen(std::random_device{}()), dist(0, 4), turn_direction(0) // Initialise les membres aléatoires
{}

float Car::getX() const { return x; }
float Car::getY() const { return y; }
float Car::getAngle() const { return angle; }
float Car::getSpeed() const { return speed; }
float Car::getPatern() const { return patern; }

void Car::move() {
    x += static_cast<float>(cos(angle * M_PI / 180.0) * speed);
    y += static_cast<float>(sin(angle * M_PI / 180.0) * speed);
}

void Car::turnLeft() {
    angle -= 2.f;
}

void Car::turnRight() {
    angle += 2.f;
}

void Car::speedUp() {
    if (speed < 3.f)
        speed += 0.1f;
}

void Car::speedDown() {
    if (speed > 0.f)
        speed -= 0.1f;
    else
        speed = 0;
}

bool Car::shouldTurn() {
    // Détermine si la voiture doit tourner (1 fois sur 5)
    if (dist(gen) == 0) { // 20% de chance
        turn_direction = (dist(gen) % 2) + 1; // 1 pour gauche, 2 pour droite
        return true;
    }
    return false;
}

int Car::getTurnDirection() const {
    return turn_direction;
}