//2D Collision Engine written by Michael Kilmer and Norman Pham
#include <iostream>
#include <thread>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"
#include "functions.h"


int screenWidth = 800;
int screenHieght = 800;

Position pos1(-200, -200);
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

Position initialForce(-1.2, 0.6);
Position initialForce2(0, 0);
Position initialForce3(1, 0.2);
Position initialForce4(0.2, -0.8);

Position cf1(0.1, 0.1);
Position cf2(-0.2, -0.2);


Display display(screenWidth, screenHieght, "HelloWorld");

void printPos(Body& a) {
	Position center = a.getCenter();
	cout << center.x << "," << center.y << endl;
}

void drawObjects() {
	for (int i = 0; i < Objects.size(); i++) {
		Objects.at(i)->draw(display);
	}
}

void applyForce() {
	for (int i = 0; i < Objects.size(); i++) {
		Objects.at(i)->Force();
	}
}

void applyCollision() {
	for (int i = 0; i < Objects.size(); i++) {
		for (int j = i + 1; j < Objects.size(); j++) {
			collisionDetection(Objects.at(i), Objects.at(j));
		}
	}
}

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;

	Circle c1(pos1, 100);
	Circle c2(pos2, 100);
	AABB sq1(sqMin,sqMax);
	AABB sq2(sqMin1, sqMax1);
	AABB sq3(sqMin2, sqMax2);
	AABB ground (g1Min, g1Max, 1);
	AABB ground2 (g2Min, g2Max, 1);
	AABB ground3 (g3Min, g3Max, 1);
	AABB ground4 (g4Min, g4Max, 1);

	Triangle T1(pos6, pos7, pos8);


	Objects.push_back(&sq1);
	Objects.push_back(&sq2);
	Objects.push_back(&sq3);
	Objects.push_back(&ground);
	Objects.push_back(&ground2);
	Objects.push_back(&ground3);
	Objects.push_back(&ground4);
	Objects.push_back(&c1);
	Objects.push_back(&c2);

	Shader shader("./res/basicShader");

	sq1.setVelocity(initialForce3);
	sq2.setVelocity(initialForce);
	sq3.setVelocity(initialForce4);
	ground.setVelocity(initialForce2);

	c1.setVelocity(cf1);
	c2.setVelocity(cf2);

	while (!display.getIsClosed()) {	
		applyCollision();

		display.fill(.1f, .1f, .1f, 1);

		drawObjects();
		applyForce();
		shader.Bind();

		display.Update();
	}
	return 0;
}