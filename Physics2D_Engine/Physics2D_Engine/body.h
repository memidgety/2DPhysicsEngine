#pragma once
#include <vector>

using namespace std;

class Body{
protected:
	vector <double> pos;
	virtual void draw() {};
};

//________________CIRCLE_________

class Circle : public Body{
public:
	Circle();
	~Circle();

	//______Getters______
	double getPos() { return pos.at(0), pos.at(1); };
	double getRadius() { return radius; };

	//______Setters______
	void setRadius(double r) {
		radius = r;
	};
	void setPos(double x, double y) {
		pos.at(0) = x;
		pos.at(1) = y;
	};

private:
	double radius;
	//vector <double> pos;

};

Circle::Circle() {
	setRadius(1);
	setPos(1, 1);
}

Circle::~Circle() {
}


//________________AABB_________

class AABB : public Body// Axis Aligned Bounding Box
{
public:
	AABB();
	~AABB();

	void setMin(double i) {
		min = i;
	};
	void setMax(double i) {
		max = i;
	};

	double getMin() { return min; };
	double getMax() { return max; };

private:
	double min, max;
};

AABB::AABB() { // Defaults to a Square
	setMax(1);
	setMin(1);
}

AABB::~AABB() {
}
