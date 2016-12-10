#pragma once
#include "body.h"
#include<cmath>

using namespace std;

vector<Body> Objects;

void AABBVsAABB(Body& c, Body& d) {

}

void CircleVsCircle(Body& c, Body& d) {

}

void AABBVsCircle(Body& c, Body& d) {

}

void applyVelocity(Body& a, Body& b) {

	//Position  aPosMin;
	//Position  aPosMax;
	//Position  bPosMin;
	//Position  bPosMax;

	//aPosMin = a.getPosition1();
	//aPosMax = a.getPosition2();
	//bPosMin = b.getPosition1();
	//bPosMax = b.getPosition2();

	//if ((aPosMin.x < bPosMin.x) || (aPosMin.x > bPosMax.x))
	//	return false;
	//if ((aPosMax.y < bPosMin.y) || (aPosMin.y > bPosMax.y))
	//	return false;
	//else return true;

	//cout << a.getType();
	

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

	if (a.getType() == "AABB" && b.getType() == "AABB") {

		Position  aPosMin;
		Position  aPosMax;
		Position  bPosMin;
		Position  bPosMax;

		aPosMin = *aPos.at(0);
		aPosMax = *aPos.at(1);
		bPosMin = *bPos.at(0);
		bPosMax = *bPos.at(1);

		cout << aPosMax.y << endl;

		if ((aPosMax.x < bPosMin.x) || (aPosMin.x > bPosMax.x))
			return false;
		if ((aPosMax.y < bPosMin.y) || (aPosMin.y > bPosMax.y))
			return false;

		return true;
	}
	if (a.getType() == "Circle" && b.getType() == "Circle") {

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
	if (a.getType() == "AABB" && b.getType() == "Circle") {

	}
}