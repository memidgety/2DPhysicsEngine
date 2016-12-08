#include <iostream>
#include <thread>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"

Position pos1(100, 100);

Position pos2(-60, -30);
Position pos3(-60, -60);
Position pos4(-30, -60);
Position pos5(-30, -30);

Position pos6(-240, 100);
Position pos7(-260, 0);
Position pos8(-220, 0);


int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;
	
	int screenWidth = 800;
	int screenHieght = 800;

	Circle c1(pos1, 100);
	AABB sq1(pos2, pos3, pos4, pos5);
	Triangle T1(pos6, pos7, pos8);

	Display display(screenWidth, screenHieght, "HelloWorld");

	Shader shader("./res/basicShader");



	while (!display.getIsClosed()) {	
		std::cout << "0";
		display.fill(.1f, .1f, .1f, 1);

		c1.draw(display);
		c1.gravityScale();

		sq1.draw(display);
	    sq1.gravityScale();

		T1.draw(display);
		T1.gravityScale();

		shader.Bind();

		display.Update();

		//display.setIsClosed(true);
	}
	return 0;
}

