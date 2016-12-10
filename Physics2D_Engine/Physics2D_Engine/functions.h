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
		float sqDist = 0.0f;
		float minX, minY, maxX, maxY;

		Position  aPosMin = *aPos.at(0);
		Position  aPosMax = *aPos.at(1);

		Position AABBCenter;

		Position circleCenter = *bPos.at(0);

		float width = aPosMax.x - aPosMin.x;
		float hieght = aPosMax.y - aPosMin.y;
		
		AABBCenter.x = ((aPosMax.x + aPosMin.x) / 2);
		AABBCenter.y = ((aPosMax.y + aPosMin.y) / 2);

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
}