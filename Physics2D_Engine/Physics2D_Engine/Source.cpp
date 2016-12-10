#include <iostream>
#include <thread>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"
#include "functions.h"

Position pos1(100, 100);
Position pos2(100, -200);

Position sqMin(-30,-30);
Position sqMax(-60,-60);

Position pos6(-240, 100);
Position pos7(-260, 0);
Position pos8(-220, 0);

Position gMin(-400, -400);
Position gMax(400,-350);


//______________________Collision Test__________
//bool collision(AABB& a, AABB& b) {
//
//	Position  aPosMin;
//	Position  aPosMax;
//	Position  bPosMin;
//	Position  bPosMax;
//
//	aPosMin = a.getPosition1();
//	aPosMax = a.getPosition2();
//	bPosMin = b.getPosition1();
//	bPosMax = b.getPosition2();
//
//	if ((aPosMin.x < bPosMin.x) || (aPosMin.x > bPosMax.x))
//		return false;
//	if ((aPosMax.y < bPosMin.y) || (aPosMin.y > bPosMax.y))
//		return false;
//	else return true;
//}


int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;
	
	int screenWidth = 800;
	int screenHieght = 800;

	Circle c1(pos1, 100);
	Circle c2(pos2, 50);
	AABB sq1(sqMin,sqMax);
	AABB ground(gMin, gMax);
	Triangle T1(pos6, pos7, pos8);

	Display display(screenWidth, screenHieght, "HelloWorld");

	Shader shader("./res/basicShader");



	while (!display.getIsClosed()) {	
		//std::cout << "0";
		display.fill(.1f, .1f, .1f, 1);

		cout << collisionDetection(ground, c1);

		ground.draw(display);

		c2.draw(display);
		c1.draw(display);
		c1.Force();

		sq1.draw(display);
	    sq1.Force();

		T1.draw(display);
		T1.Force();

		shader.Bind();

		//collision(sq1, ground);
		//std::cout << collision(sq1, ground);

		display.Update();

		//display.setIsClosed(true);
	}
	return 0;
}