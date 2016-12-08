#include <iostream>
#include <thread>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;
	
	int screenWidth = 800;
	int screenHieght = 800;

	//Circle c1;
	AABB sq1;
	Triangle T1;
	Circle c1;

	Position pos1(30, 30);
	Position pos2(60, 30);
	Position pos3(60, 60);
	Position pos4(30, 60);

	//Position pos2(800, -600);
	//Position pos3(-800, -600);

	Display display(screenWidth, screenHieght, "HelloWorld");

	Shader shader("./res/basicShader");

	while (!display.getIsClosed()) {
		display.fill(.1f, .1f, .1f,1);
		
		//c1.DrawCircle(pos1, .2, 36, display);
		sq1.draw(pos1, pos2, pos3, pos4, display);
		//T1.draw(pos1, pos2, pos3, display);
		shader.Bind();

		display.Update();
	}
	return 0;
}

