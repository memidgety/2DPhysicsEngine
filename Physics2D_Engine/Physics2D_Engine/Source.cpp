#include <iostream>
#include <thread>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"
#include "functions.h"


Position pos1(100, 100);
Position pos2(400, 150);

Position sqMax(0,0);
Position sqMin(-60,-60);

Position sqMin1(30, 30);
Position sqMax1(90, 90);

Position sqMin2(200, 200);
Position sqMax2(260, 260);

Position pos6(-240, 100);
Position pos7(-260, 0);
Position pos8(-220, 0);

Position g1Max(600, 800);
Position g1Min(-600,600);

Position g2Max(600, -600);
Position g2Min(-600, -800);

Position g3Max(-600, 600);
Position g3Min(-800, -600);

Position g4Max(800, 600);
Position g4Min(600, -600);

Position initialForce(-6, 3);
Position initialForce2(0, 0);
Position initialForce3(5, 1);
Position initialForce4(1, -4);

Position cf1(1, .5);
Position cf2(-1, -.5);


void printPos(Body& a) {
	Position center = a.getCenter();
	cout << center.x << "," << center.y << endl;
}

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;
	
	int screenWidth = 800;
	int screenHieght = 800;

	Circle c1(pos1, 100);
	Circle c2(pos2, 100);
	AABB sq1(sqMin,sqMax);
	AABB sq2(sqMin1, sqMax1);
	AABB sq3(sqMin2, sqMax2);
	AABB ground(g1Min, g1Max);
	AABB ground2(g2Min, g2Max);
	AABB ground3(g3Min, g3Max);
	AABB ground4(g4Min, g4Max);

	Triangle T1(pos6, pos7, pos8);

	Display display(screenWidth, screenHieght, "HelloWorld");

	Shader shader("./res/basicShader");

	sq1.setVelocity(initialForce3);
	sq2.setVelocity(initialForce);
	sq3.setVelocity(initialForce4);
	ground.setVelocity(initialForce2);

	c1.setVelocity(cf1);
	c2.setVelocity(cf2);

	while (!display.getIsClosed()) {	
		//std::cout << "0";
		collisionDetection(sq1, ground);
		collisionDetection(sq1, ground2);
		collisionDetection(sq1, ground3);
		collisionDetection(sq1, ground4);

		collisionDetection(sq2, ground);
		collisionDetection(sq2, ground2);
		collisionDetection(sq2, ground3);
		collisionDetection(sq2, ground4);

		collisionDetection(sq3, ground);
		collisionDetection(sq3, ground2);
		collisionDetection(sq3, ground3);
		collisionDetection(sq3, ground4);

		collisionDetection(sq1, sq2);
		collisionDetection(sq1, sq3);
		collisionDetection(sq2, sq3);


		collisionDetection(c1, c2);

		display.fill(.1f, .1f, .1f, 1);

		

		ground.draw(display);
		ground2.draw(display);
		ground3.draw(display);
		ground4.draw(display);
		//ground.Force();

		c1.Force();
		c1.draw(display);
		c2.Force();
		c2.draw(display);

		sq3.Force();
		sq3.draw(display);

		sq2.Force();
		sq2.draw(display);

		sq1.Force();
		sq1.draw(display);

		shader.Bind();

		//printPos(sq1);
		//collision(sq1, ground);
		//std::cout << collision(sq1, ground);
		display.Update();

		//display.setIsClosed(true);
	}
	return 0;
}