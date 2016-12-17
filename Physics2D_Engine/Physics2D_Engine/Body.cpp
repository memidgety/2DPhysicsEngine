#include "body.h"

Position::Position() { //default constructor
	x = 0;
	y = 0;
};

Position::Position(float x, float y){
	this->x = x;
	this->y = y;
};

//Operator Overloads to compare, add, and subtract positions
Position& Position::operator= (const Position& p) { 
	this->x = p.x;
	this->y = p.y;
	return *this;
};

Position& Position::operator+ (const Position& p) {
	this->x += p.x;
	this->y += p.y;
	return *this;
};

Position& Position::operator- (const Position& p) {
	this->x -= p.x;
	this->y -= p.y;
	return *this;
};

Body::Body(){
	gravity.first = 0;
	gravity.second = -1;
};

Body::~Body() {};

void Body::Force() { //used to move objects around the screen
	for (std::size_t i = 0; i < positions.size(); ++i)
	{
		Position * s = positions[i]; //create temporary position for each position an object has, add to it, set new positions
		s->x += velocity.x;
		s->y += velocity.y;
		positions[i] = s;
	}
};

Circle::Circle(Position pos1, float radius, int num_segments, float mass) {

	this->radius = radius;
	this->num_segments = num_segments;
	this->pos1 = pos1;
	positions.push_back((&this->pos1));
	this->mass = mass;
};

Circle::~Circle() {};

void Circle::draw(const Display& screenSize) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

		float x = (radius / screenSize.hieght)* cosf(theta);//calculate the x component
		float y = (radius / screenSize.hieght)* sinf(theta);//calculate the y component

		glVertex2f(x + (pos1.x / screenSize.width), y + (pos1.y / screenSize.hieght));//output vertex

	}
	glEnd();
};

AABB::AABB(Position& pos1, Position& pos2, float mass) { // Min , max
	this->pos1 = pos1;//min
	this->pos2 = pos2;//max
	this->pos3.x = pos2.x;
	this->pos3.y = pos1.y;//end pos 3
	this->pos4.x = pos1.x;
	this->pos4.y = pos2.y;//end point 4

	this->mass = mass;

	positions.push_back((&this->pos1));
	positions.push_back((&this->pos2));
	positions.push_back((&this->pos3));
	positions.push_back((&this->pos4));
}

AABB::~AABB() {};

void AABB::draw(const Display& screenSize) {
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
};

Position AABB::getCenter() {
	Position center;
	center.x = (pos1.x + pos2.x) / 2;
	center.y = (pos1.y + pos2.y) / 2;
	return center;
};

Triangle::Triangle(Position& pos1, Position& pos2, Position& pos3) {
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;

	positions.push_back((&this->pos3));
	positions.push_back((&this->pos2));
	positions.push_back((&this->pos1));
};

Triangle::~Triangle() {
};

void Triangle::draw(const Display& screenSize) {

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