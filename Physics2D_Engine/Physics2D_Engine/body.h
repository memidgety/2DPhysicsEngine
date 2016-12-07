#pragma once
#include <vector>
#include "mesh.h"
#include "display.h"


using namespace std;

class Position {
public:
	Position(float x, float y) : x(x), y(y) {};
	~Position() {};
	float x;
	float y;
private:

};


class Body{
protected:
	vector <float> pos;
	virtual void draw() {};
};

//________________CIRCLE_________

class Circle : public Body{
public:
	Circle();
	~Circle();

	//______Getters______
	float getPos() { return pos.at(0), pos.at(1); };
	float getRadius() { return radius; };

	//______Setters______
	void setRadius(float r) {
		radius = r;
	};
	void setPos(float x, float y) {
		pos.at(0) = x;
		pos.at(1) = y;
	};

	void DrawCircle(Position pos, float radius, int num_segments, const Display& screenSize)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < num_segments; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

			float x = radius * cosf(theta);//calculate the x component
			float y = radius * sinf(theta);//calculate the y component

			glVertex2f(x + (pos.x / screenSize.width), y + (pos.y / screenSize.hieght));//output vertex

		}
		glEnd();
	}

private:
	const float DEG2RAD = 3.14159 / 180;
	float radius;
	vector <float> pos;

};

Circle::Circle() {
	pos.push_back(0);
	pos.push_back(0);
	pos.at(0) = .5;
	pos.at(1) = .5;
	radius = 1;
}

Circle::~Circle() {
}


//________________AABB_________

class AABB : public Body// Axis Aligned Bounding Box
{
public:
	AABB();
	~AABB();

	void setMin(float i) {
		min = i;
	};
	void setMax(float i) {
		max = i;
	};

	void draw(Position pos1, Position pos2, Position pos3, Position pos4, const Display& screenSize);

	float getMin() { return min; };
	float getMax() { return max; };

private:
	float min, max;
};

AABB::AABB() { // Defaults to a Square
	setMax(1);
	setMin(1);
}

AABB::~AABB() {
}

void AABB::draw(Position pos1, Position pos2, Position pos3, Position pos4, const Display& screenSize) {
	float vertices[] =
	{
		pos1.x / screenSize.width, pos1.y / screenSize.hieght, 0,// top right corner
		pos2.x / screenSize.width, pos2.y / screenSize.hieght, 0,// top left corner
		pos3.x / screenSize.width, pos3.y / screenSize.hieght, 0,// bottom left corner
		pos4.x / screenSize.width, pos4.y / screenSize.hieght, 0// bottom right corner
	};
	glEnableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
	glVertexPointer(3, GL_FLOAT, 0, vertices); // point to the vertices to be used
	glDrawArrays(GL_QUADS, 0, 4); // draw the vertixes
	glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex arrayattribute
}


//_______________TRIANGLE____________

class Triangle : public Body// Axis Aligned Bounding Box
{
public:
	Triangle();
	~Triangle();

	void draw(Position pos1, Position pos2, Position pos3 , const Display& screenSize);

private:

};

Triangle::Triangle() { // 
}

Triangle::~Triangle() {
}

void Triangle::draw(Position pos1, Position pos2, Position pos3, const Display& screenSize) {

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
