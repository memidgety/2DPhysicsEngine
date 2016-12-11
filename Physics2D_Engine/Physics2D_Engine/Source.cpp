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

Position gMin(-400, 350);
Position gMax(400,400);

Position initialForce(2, 3);
Position initialForce2(0, 0);


void printPos(Body& a) {
	Position center = a.getCenter();
	cout << center.x << "," << center.y << endl;
}

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

	sq1.setVelocity(initialForce);
	ground.setVelocity(initialForce2);

	while (!display.getIsClosed()) {	
		//std::cout << "0";
		display.fill(.1f, .1f, .1f, 1);

		collisionDetection(sq1, ground);

		ground.draw(display);
		//ground.Force();

		sq1.draw(display);
	    sq1.Force();

		shader.Bind();

		printPos(sq1);
		//collision(sq1, ground);
		//std::cout << collision(sq1, ground);

		display.Update();

		//display.setIsClosed(true);
	}
	return 0;
}