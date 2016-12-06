#pragma once
#include <vector>
#include "mesh.h"


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

	void draw(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
		int numberOfVertices = 361;

		GLfloat twicePi = 2.0f * M_PI;

		GLfloat circleVerticesX[361];
		GLfloat circleVerticesY[361];
		GLfloat circleVerticesZ[361];

		circleVerticesX[0] = x;
		circleVerticesY[0] = y;
		circleVerticesZ[0] = z;

		for (int i = 1; i < numberOfVertices; i++)
		{
			circleVerticesX[i] = x + (radius * cos(i *  twicePi / 360));
			circleVerticesY[i] = y + (radius * sin(i * twicePi / 360));
			circleVerticesZ[i] = z;
		}

		GLfloat allCircleVertices[(361)* 3];

		for (int i = 0; i < numberOfVertices; i++)
		{
			allCircleVertices[i * 3] = circleVerticesX[i];
			allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
			allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
		glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
		glDisableClientState(GL_VERTEX_ARRAY);
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

	void draw();

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

void AABB::draw() {
	float vertices[] =
	{
		300, 300, 0.0, // top right corner
		0, 300, 0.0, // top left corner
		0, 0, 0.0, // bottom left corner
		300, 0, 0.0 // bottom right corner
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

	//void setPos1(float i) {
	//	pos1 = i;
	//};
	//void setPos2(float i) {
	//	pos2 = i;
	//};
	//void setPos3(float i) {
	//	pos3 = i;
	//};

	void draw(Position pos1, Position pos2, Position pos3, int hieght, int width);

	//float getPos1() { return pos1; };
	//float getPos2() { return pos2; };
	//float getPos3() { return pos3; };

private:
	//float pos1, pos2, pos3;
};

Triangle::Triangle() { // 
}

Triangle::~Triangle() {
}

void Triangle::draw(Position pos1, Position pos2, Position pos3, int hieght, int width) {

	float vertices[] = {
		pos1.x / width, pos1.y / hieght, 0,
		pos2.x / width, pos2.y / hieght, 0,
		pos3.x / width, pos3.y / hieght, 0
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	/*Vertex vertices[] = { Vertex(glm::vec3(pos1.x / screenSize.width ,pos1.y / screenSize.hieght,0)),
	Vertex(glm::vec3(pos2.x / screenSize.width,pos2.y / screenSize.hieght,0)),
	Vertex(glm::vec3(pos3.x / screenSize.width,pos3.y / screenSize.hieght,0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	mesh.Draw();*/
};
