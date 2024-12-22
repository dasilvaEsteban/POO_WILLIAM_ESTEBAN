#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <iostream>

class Pieton;
class Bus;


class Car {
private:
	float x, y;
	float angle;
	float speed;
	float patern;
	float initangle;
public:
	Car(const float x, const float y, const float angle, const float speed, const float patern);

	float getX() const;
	float getY() const;
	float getinitAngle() const;
	float getAngle() const;
	float getSpeed() const;
	float getPatern() const;
	float distanceTo(const Car& other) const;
	float distanceToPiet(const Pieton& other) const;
	float distanceToBus(const Bus& other) const;


	void move();
	void turnLeft();
	void turnRight();
	void speedUp();
	void speedDown();
};