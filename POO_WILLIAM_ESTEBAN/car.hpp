//#pragma once
//#define _USE_MATH_DEFINESlll
//#include <cmath>
//
//class Car{
//private:
//	float x, y;
//	float angle;
//	float speed;
//	float patern;
//public:
//	Car(const float x, const float y, const float angle, const float speed, const float patern);
//
//	float getX() const;
//	float getY() const;
//	float getAngle() const;
//	float getSpeed() const;
//	float getPatern() const;
//
//	void move();
//	void turnLeft();
//	void turnRight();
//	void speedUp();
//	void speedDown();
//};
#include <random>

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>

class Car {
private:
    float x, y;
    float angle;
    float speed;
    float patern;

    std::mt19937 gen; // Générateur aléatoire
    std::uniform_int_distribution<> dist; // Distribution pour déterminer si la voiture tourne
    int turn_direction; // 0 = tout droit, 1 = gauche, 2 = droite

public:
    Car(const float x, const float y, const float angle, const float speed, const float patern);

    float getX() const;
    float getY() const;
    float getAngle() const;
    float getSpeed() const;
    float getPatern() const;

    void move();
    void turnLeft();
    void turnRight();
    void speedUp();
    void speedDown();

    bool shouldTurn(); // Vérifie si la voiture doit tourner
    int getTurnDirection() const; // Retourne la direction de la rotation
};



