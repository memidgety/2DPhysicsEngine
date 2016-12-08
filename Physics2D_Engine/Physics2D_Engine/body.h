#pragma once
#include <vector>
#include "mesh.h"
#include "display.h"


using namespace std;

class Position {
public:
	Position() { 
		x = 0;
		y = 0;
	};

	Position(float x, float y) : x(x), y(y) {};

	~Position() {};

	Position& operator= (const Position& p) {
		this->x = p.x;
		this->y = p.y;
		return *this;
	}

	float x;
	float y;
private:

};

//Position& Position::operator= (const Position& p) {
//	
//};


class Body{
public:
	void gravityScale() {
		for (std::size_t i = 0; i < positions.size(); ++i) //for loop to go through accounts
		{
			Position * s = positions[i]; // set s to go through every account

			s->y -= 1;
			positions[i] = s;

		}
	};
protected:
	vector <float> pos;
	virtual void draw() {};
	vector <Position*> positions;
private:

};

//________________CIRCLE__________________________________________________________________________________________________________C

class Circle : public Body{
public:
	Circle(Position pos1, float radius, int num_segments = 36);
	~Circle();

	//______Getters______

	//______Setters______

	void draw(const Display& screenSize)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < num_segments; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

			float x = (radius / screenSize.hieght)* cosf(theta);//calculate the x component
			float y = (radius / screenSize.hieght)* sinf(theta);//calculate the y component

			glVertex2f(x + (pos1.x / screenSize.width), y + (pos1.y / screenSize.hieght));//output vertex

		}
		glEnd();
	};

private:
	float radius;
	int num_segments;
	Position pos1;
};

Circle::Circle(Position pos1, float radius, int num_segments) {

	this->radius = radius;
	this->num_segments = num_segments;
	this->pos1 = pos1;
	positions.push_back((&this->pos1));
}

Circle::~Circle() {
}

//________________AABB__________________________________________________________________________________________________________AABB

class AABB : public Body// Axis Aligned Bounding Box
{
public:
	AABB(Position& min, Position& max);
	~AABB();

	//void setMin(float i) {
	//	min = i;
	//};
	//void setMax(float i) {
	//	max = i;
	//};

	void draw(const Display& screenSize) {
		float vertices[] =
		{
			pos1.x / screenSize.width, pos1.y / screenSize.hieght, 0,// top right corner
			pos3.x / screenSize.width, pos3.y / screenSize.hieght, 0,// bottom left corner
			pos2.x / screenSize.width, pos2.y / screenSize.hieght, 0,// top left corner
			pos4.x / screenSize.width, pos4.y / screenSize.hieght, 0// bottom right corner
		};
		glEnableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
		glVertexPointer(3, GL_FLOAT, 0, vertices); // point to the vertices to be used
		glDrawArrays(GL_QUADS, 0, 4); // draw the vertixes
		glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex arrayattribute
	}

	Position getPosition1() { return pos1; }
	Position getPosition2() { return pos2; }
	Position getPosition3() { return pos3; }
	Position getPosition4() { return pos4; }


private:
	Position pos1;
	Position pos2;
	Position pos3;
	Position pos4;
};

AABB::AABB(Position& pos1, Position& pos2) { // Min , max
	this->pos1 = pos1;//min
	this->pos2 = pos2;//max
	this->pos3.x = pos2.x;
	this->pos3.y = pos1.y;//end pos 3
	this->pos4.x = pos1.x;
	this->pos4.y = pos2.y;//end point 4

	positions.push_back((&this->pos4));
	positions.push_back((&this->pos3));
	positions.push_back((&this->pos2));
	positions.push_back((&this->pos1));
}

AABB::~AABB() {
}

//_______________TRIANGLE_____________________________________________________________________________________________________T

class Triangle : public Body// Axis Aligned Bounding Box
{
public:
	Triangle(Position& pos1, Position& pos2, Position& pos3);
	~Triangle();

	void draw(const Display& screenSize) {

		float vertices[] = {
			pos1.x / screenSize.width, pos1.y / screenSize.hieght, 0,
			pos2.x / screenSize.width, pos2.y / screenSize.hieght, 0,
			pos3.x / screenSize.width, pos3.y / screenSize.hieght, 0
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);
	};

	void setPosition1(Position pos) { pos1.x = pos.x; pos1.y = pos.y; };
	void setPosition2(Position pos) { pos2 = pos; };
	void setPosition3(Position pos) { pos3 = pos; };

	Position getPosition1() { return pos1; }
	Position getPosition2() { return pos2; }
	Position getPosition3() { return pos3; }

private:
	Position pos1;
	Position pos2;
	Position pos3;
};

Triangle::Triangle(Position& pos1, Position& pos2, Position& pos3) { 
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;

	positions.push_back((&this->pos3));
	positions.push_back((&this->pos2));
	positions.push_back((&this->pos1));
}

Triangle::~Triangle() {
}


