#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <iostream>

class Car;
class Bus;

class Pieton {
private:
	float x, y;
	float angle;
	float speed;
public:
	Pieton(const float x, const float y, const float angle, const float speed);

	float getX() const;
	float getY() const;
	float getAngle() const;
	float getSpeed() const;
	float distanceTo(const Pieton& other) const;
	float distanceToCar(const Car& other) const;
	float distanceToBus(const Bus& other) const;


	void move();
	void speedUp();
	void speedDown();
};
