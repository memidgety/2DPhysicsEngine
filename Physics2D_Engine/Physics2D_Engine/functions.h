#pragma once
#include "body.h"
#include <math.h>
#include <cmath>
using namespace std;

vector<Body*> Objects;
Position normal;

float DotProduct(Position& a, Position& b ) {
	return ((a.x * b.x) + (a.y * b.y));
}

Position normalizeVector(Position& a) {
	float mag = sqrt(pow(a.x, 2) + pow(a.y, 2));
	a.x = a.x / mag;
	a.y = a.y / mag;
	return a;
}

void AABBvsAABB(Body* a, Body* b) {

	cout << "Boop" << endl;

	vector<Position*> aPos = a->getPositions();
	vector<Position*> bPos = b->getPositions();

	Position aCenter = a->getCenter();
	Position bCenter = b->getCenter();

	Position rVel = b->getVelocity() - a->getVelocity();

	float j = rVel.x;
	float k = rVel.y;

	if (b->getMass() > 0) {
		Position impulse;
		impulse.x = normal.x * j;
		impulse.y = normal.y  * k;

		Position negimpulse;
		negimpulse.x = normal.x * -j;
		negimpulse.y = normal.y  * -k;

		a->setVelocityWithBounce(negimpulse);
	}
	else {

		Position tempVela = a->getVelocity();
		Position tempVelb = b->getVelocity();

		Position rVel = b->getVelocity() - a->getVelocity();

		j = rVel.x;
		k = rVel.y;

		Position impulse;
		impulse.x = normal.x * j;
		impulse.y = normal.y  * -k;

		Position negimpulse;
		negimpulse.x = normal.x * -j;
		negimpulse.y = normal.y  * k;

		a->setVelocityWithBounce(tempVelb);
		b->setVelocityWithBounce(tempVela);
	}
	
	

}

void CircleVsCircle(Body* a, Body* b) { // check resolveCollision
	Position tempVela = a->getVelocity();
	Position tempVelb = b->getVelocity();

	Position rVel = b->getVelocity() - b->getVelocity() - a->getVelocity();

	float j = rVel.x;
	float k = rVel.y;

	Position impulse;
	impulse.x = k;
	impulse.y = -j;

	Position negimpulse;
	negimpulse.x = -k;
	negimpulse.y = j;

	a->setVelocityWithBounce(negimpulse);
	b->setVelocityWithBounce(impulse);
}

void AABBvsCircle(Body& c, Body& d) {

}

void applyVelocity(Body* a, Body* b) {

	if ((a->getType() == "AABB") && (b->getType() == "AABB")) {
		AABBvsAABB(a, b);
	}

	if ((a->getType() == "Circle") && (a->getType() == "Circle")) {
		CircleVsCircle(a, b);
	}

	//if (((a->getType() == "Circle") && (a->getType() == "AABB")) || ((a->getType() == "AABB") && (b->getType() == "Circle"))) {
	//	if (a->getType() == "Circle") {
	//		AABBvsCircle(b, a);
	//	}
	//	if (a->getType() == "AABB") {
	//		AABBvsCircle(a,b);
	//	}
	//}
	//if ((a->getType() == "Circle") && (a->getType() == "Triangle")) {}
	//if ((a->getType() == "AABB") && (a->getType() == "Triangle")) {}
	//if ((a->getType() == "Triangle") && (a->getType() == "Triangle")) {}
}



// ------------
bool collisionDetection(Body* a, Body* b) {

	normal.x = 0;
	normal.y = 0;

	vector<Position*> aPos = a->getPositions();
	vector<Position*> bPos = b->getPositions();

	if (a->getType() == "AABB" && b->getType() == "AABB") { // __________________________AABB_AABB

		Position  aPosMin;
		Position  aPosMax;
		Position  bPosMin;
		Position  bPosMax;

		aPosMin = *aPos.at(0);
		aPosMax = *aPos.at(1);
		bPosMin = *bPos.at(0);
		bPosMax = *bPos.at(1);

		// --- Detects for collision via Seperating Axis - Theorem
		if ((aPosMax.x < bPosMin.x) || (aPosMin.x > bPosMax.x))
			return false;
		if ((aPosMax.y < bPosMin.y) || (aPosMin.y > bPosMax.y))
			return false;

		// --- set the normal of the collision
		Position n = b->getCenter() - a->getCenter();
		float absX = abs(b->getCenter().x) - abs(a->getCenter().x);
		float absY = abs(b->getCenter().y) - abs(a->getCenter().y);

		/*float absX = abs(n.x);
		float absY = abs(n.y);*/

		if ((n.x < 0) && (n.y < 0)) {
			if ((absX) < (absY)) {  //case 1
				normal.x = 1; normal.y = -1;
			}
			else {					// case 2
				normal.x = -1; normal.y = 1;
			}
		}
		if ((n.x < 0) && (n.y > 0)) {
			if ((absX) > (absY)) {  //case 3
				normal.x = -1; normal.y = 1;
			}
			else {					//case 4
				normal.x = 1; normal.y = -1;
			}
		}
		if ((n.x > 0) && (n.y > 0)) {
			if ((absX) < (absY)) {  //case 5
				normal.x = 1; normal.y = -1;
			}
			else {					//case 6
				normal.x = -1; normal.y = 1;
			}
		}
		if ((n.x > 0) && (n.y < 0)) {
			if ((absX) > (absY)) {  //case 7
				normal.x = -1; normal.y = 1;
			}
			else {					//case 8
				normal.x = 1; normal.y = -1;
			}
		}
		applyVelocity(a, b);
		return true;
	}

	if (a->getType() == "Circle" && b->getType() == "Circle") { // ________________________Circle_Circle

		Position  aCenter;
		Position  bCenter;

		aCenter = *aPos.at(0);
		bCenter = *bPos.at(0);

		float r = a->getRadius() + b->getRadius();

		float distance = (pow(bCenter.x - aCenter.x, 2)) + (pow(bCenter.y - aCenter.y, 2));
		if ((pow(r,2)) < distance ) {
			return false;
		}
		//cout << "colliding C" << endl; Norman Pham and Michael Kilmer's Code.
		Position n;// (bCenter - aCenter); // vector from b to a; use dx=x2-x1 and dy=y2-y1, then the normals are (-dy, dx) and (dy, -dx).
		
		n.x = bCenter.x - aCenter.x;
		n.y = bCenter.y - aCenter.y;

		normal.x = -n.y;
		normal.y = n.x;

		applyVelocity(a, b);
		return true;
	}
	if (a->getType() == "AABB" && b->getType() == "Circle") { // __________________________AABB_Cricle
		float sqDist = 0.0f;
		float minX, minY, maxX, maxY;

		//initialize a.min and a.max
		Position  aPosMin = *aPos.at(0);
		Position  aPosMax = *aPos.at(1);

		Position AABBCenter = a->getCenter();

		Position circleCenter = *bPos.at(0);

		float width = aPosMax.x - aPosMin.x;
		float hieght = aPosMax.y - aPosMin.y;

		minX = AABBCenter.x - (width / 2);
		maxX = AABBCenter.x + (width / 2);

		minY = AABBCenter.y - (hieght / 2);
		maxY = AABBCenter.y + (hieght / 2);

		if (circleCenter.x < minX) 
			sqDist += (minX - circleCenter.x) * (minX - circleCenter.x); //add get normals from aabb v aabb
		if (circleCenter.x > maxX)
			sqDist += (circleCenter.x - maxX) * (circleCenter.x - maxX);

		if (circleCenter.y < minY)
			sqDist += (minY - circleCenter.y) * (minY - circleCenter.y);
		if (circleCenter.y > maxY)
			sqDist += (circleCenter.y - maxY) * (circleCenter.y - maxY);

		if (pow(b->getRadius(), 2) < sqDist)
			return false;

		return true;
	}
	return false;
}

