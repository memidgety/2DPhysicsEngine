#pragma once
#include <vector>

using namespace std;

class Circle : public Body
{
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
	vector <double> pos;

};

Circle::Circle() {
	setRadius(1);
	setPos(1, 1);
}

Circle::~Circle() {
}

