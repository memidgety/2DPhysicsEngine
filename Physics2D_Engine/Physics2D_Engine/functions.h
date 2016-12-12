#pragma once
#include "body.h"
#include<cmath>

using namespace std;

vector<Body> Objects;
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

void AABBVsAABB(Body& a, Body& b) {

	vector<Position*> aPos = a.getPositions();
	vector<Position*> bPos = b.getPositions();

	Position aCenter = a.getCenter();
	Position bCenter = b.getCenter();

	Position rVel = b.getVelocity() - a.getVelocity();

	float j = rVel.x;
	float k = rVel.y;

	Position impulse;
	impulse.x = normal.x * j;
	impulse.y = normal.y  * k;

	Position negimpulse;
	negimpulse.x = normal.x * -j;
	negimpulse.y = normal.y  * -k;

	a.setVelocityWithBounce(negimpulse);
	//b.setVelocityWithBounce(impulse);

}

void CircleVsCircle(Body& c, Body& d) {

}

void AABBVsCircle(Body& c, Body& d) {

}

void applyVelocity(Body& a, Body& b) {

	if ((a.getType() == "AABB") && (b.getType() == "AABB")) {
		AABBVsAABB(a, b);
	}

	if ((a.getType() == "Circle") && (a.getType() == "Circle")) {
		CircleVsCircle(a, b);
	}

	if (((a.getType() == "Circle") && (a.getType() == "AABB")) || ((a.getType() == "AABB") && (b.getType() == "Circle"))) {
		if (a.getType() == "Circle") {
			AABBVsCircle(b, a);
		}
		if (a.getType() == "AABB") {
			AABBVsCircle(a,b);
		}
	}

	//if ((a.getType() == "Circle") && (a.getType() == "Triangle")) {}
	//if ((a.getType() == "AABB") && (a.getType() == "Triangle")) {}
	//if ((a.getType() == "Triangle") && (a.getType() == "Triangle")) {}


}



// ------------
bool collisionDetection(Body& a, Body& b) {

	vector<Position*> aPos = a.getPositions();
	vector<Position*> bPos = b.getPositions();

	if (a.getType() == "AABB" && b.getType() == "AABB") { // __________________________AABB_AABB

		Position  aPosMin;
		Position  aPosMax;
		Position  bPosMin;
		Position  bPosMax;

		aPosMin = *aPos.at(0);
		aPosMax = *aPos.at(1);
		bPosMin = *bPos.at(0);
		bPosMax = *bPos.at(1);

		//cout << aPosMax.y << endl;

		// --- Detects for collision via Seperating Axis - Theorem
		if ((aPosMax.x < bPosMin.x) || (aPosMin.x > bPosMax.x))
			return false;
		if ((aPosMax.y < bPosMin.y) || (aPosMin.y > bPosMax.y))
			return false;

		// --- set the normal of the collision
		//Position normalA = normalizeVector(a.getVelocity());
		//Position normalB = normalizeVector(b.getVelocity());
		Position n = b.getCenter() - a.getCenter();

		normal = n;
		// --- find half of width for both shapes.
		float aExtent = (aPosMax.x - aPosMin.x) / 2;
		float bExtent = (bPosMax.x - bPosMin.x) / 2;

		// --- calculate overlap
		float xOverlap = (aExtent + bExtent) - abs(n.x);
		
		if (xOverlap > 0) {
			// --- check for y overlap
			float aExtent = (aPosMax.y - aPosMin.y) / 2;
			float bExtent = (bPosMax.y - bPosMin.y) / 2;
			float yOverlap = (aExtent + bExtent) - abs(n.y);

			if (yOverlap > 0) {		// check if object is colliding with top or bottom of AABB
				if (xOverlap > yOverlap) { // if xOverlap is greater, object is colliding Horizontally
					if (n.x < 0) { cout << "case 1" << endl; normal.x = 1; normal.y = -1; } // underside positive x
					else { cout << "case 2" << endl; normal.x = 1; normal.y = -1; } // underside negative x
					applyVelocity(a, b);
					return true;
				}
			}
			else {
				if (n.y < 0) { cout << "case 3" << endl; normal.x = 1; normal.y = 1;}
				else { cout << "case 4" << endl; normal.x = 1; normal.y = 1; }
				applyVelocity(a, b);
				return true;
			}
		}

		applyVelocity(a, b);
		return true;
	}
	if (a.getType() == "Circle" && b.getType() == "Circle") { // ________________________Circle_Circle

		Position  aCenter;
		Position  bCenter;

		aCenter = *aPos.at(0);
		bCenter = *bPos.at(0);

		float r = a.getRadius() + b.getRadius();
		float distance = (pow(bCenter.x - aCenter.x, 2)) + (pow(bCenter.y - aCenter.y, 2));
		if ((pow(r,2)) < distance ) {
			return false;
		}
		return true;
	}
	if (a.getType() == "AABB" && b.getType() == "Circle") { // __________________________AABB_Cricle
		float sqDist = 0.0f;
		float minX, minY, maxX, maxY;

		//initialize a.min and a.max
		Position  aPosMin = *aPos.at(0);
		Position  aPosMax = *aPos.at(1);

		Position AABBCenter = a.getCenter();

		Position circleCenter = *bPos.at(0);

		float width = aPosMax.x - aPosMin.x;
		float hieght = aPosMax.y - aPosMin.y;

		minX = AABBCenter.x - (width / 2);
		maxX = AABBCenter.x + (width / 2);

		minY = AABBCenter.y - (hieght / 2);
		maxY = AABBCenter.y + (hieght / 2);

		if (circleCenter.x < minX) 
			sqDist += (minX - circleCenter.x) * (minX - circleCenter.x);
		if (circleCenter.x > maxX)
			sqDist += (circleCenter.x - maxX) * (circleCenter.x - maxX);

		if (circleCenter.y < minY)
			sqDist += (minY - circleCenter.y) * (minY - circleCenter.y);
		if (circleCenter.y > maxY)
			sqDist += (circleCenter.y - maxY) * (circleCenter.y - maxY);

		if (pow(b.getRadius(), 2) < sqDist)
			return false;

		return true;
	}
	return false;
}