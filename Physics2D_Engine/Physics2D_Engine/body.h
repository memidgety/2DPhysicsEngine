#pragma once
#include <vector>
#include "mesh.h"
#include "display.h"

using namespace std;


class Position {
public:
	Position();

	Position(float x, float y);
	~Position() {};

	Position& operator= (const Position& p);
	Position& operator+ (const Position& p);

	Position& operator- (const Position& p);

	//Position& operator* (const float& s) { // s for scalar
	//	this->x = s * this->x;
	//	this->y = s * this->y;
	//	return *this;
	//}

	float x;
	float y;
private:

};

class Body{
public:
	Body();
	~Body();
	void Force();

	//---Getters
	Position getVelocity() {  return velocity; }
	bool getIsColliding() { return isColliding; };
	virtual string getType() { return "IM a boody"; };
	virtual Position getCenter() { return center; }
	virtual vector<Position*> getPositions() { return positions; };
	virtual float getRadius() { return radius; };
	virtual float getMass() { return mass; }

	//---Setters
	void setIsColliding(bool coll) { isColliding = coll; };
	void setVelocity( Position imp) { velocity.x += imp.x; velocity.y += imp.y; } // if both objects have force, they will bounce / if only one object has a force it will stop
	void setVelocityWithBounce(Position imp) { velocity.x = imp.x; velocity.y = imp.y; } //if only one object has a force it will bounce

	virtual void draw(const Display& screenSize) {};
protected:
	float radius;
	vector <Position*> positions;
	Position velocity;
	Position center;
	float mass;
	bool isColliding;
	
private:
	string Type;
	std::pair <float, float> gravity;
};

//________________CIRCLE__________________________________________________________________________________________________________C

class Circle : public Body{
public:
	Circle(Position pos1, float radius, int num_segments = 36, float mass = 0);
	~Circle();

	void draw(const Display& screenSize) override;

	//______Getters______
	string getType() override { return Type; }
	float getRadius() override { return radius; }
	float getMass() override { return mass; }

private:
	string Type = "Circle";
	float radius;
	float mass;
	int num_segments;
	Position pos1;
};

//________________AABB__________________________________________________________________________________________________________AABB

class AABB : public Body// Axis Aligned Bounding Box
{
public:
	AABB(Position& min, Position& max, float mass = 0);
	~AABB();

	void draw(const Display& screenSize) override;

	Position getPosition1() { return pos1; }
	Position getPosition2() { return pos2; }
	Position getPosition3() { return pos3; }
	Position getPosition4() { return pos4; }
	Position getCenter() override;

	string getType() override { return Type; }
	float getMass() override { return mass; }
private:
	string Type = "AABB";
	Position pos1;
	Position pos2;
	Position pos3;
	Position pos4;
	float mass;
};

//_______________TRIANGLE_____________________________________________________________________________________________________T

class Triangle : public Body// Axis Aligned Bounding Box
{
public:
	Triangle(Position& pos1, Position& pos2, Position& pos3);
	~Triangle();

	void draw(const Display& screenSize) override;

	void setPosition1(Position pos) { pos1.x = pos.x; pos1.y = pos.y; };
	void setPosition2(Position pos) { pos2 = pos; };
	void setPosition3(Position pos) { pos3 = pos; };

	Position getPosition1() { return pos1; }
	Position getPosition2() { return pos2; }
	Position getPosition3() { return pos3; }

	string getType() override { return Type; }
private:
	string Type = "Triangle";
	Position pos1;
	Position pos2;
	Position pos3;
};