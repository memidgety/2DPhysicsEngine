#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "body.h"

//void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
//	int numberOfVertices = 361;
//
//	GLfloat twicePi = 2.0f * M_PI;
//
//	GLfloat circleVerticesX[361];
//	GLfloat circleVerticesY[361];
//	GLfloat circleVerticesZ[361];
//
//	circleVerticesX[0] = x;
//	circleVerticesY[0] = y;
//	circleVerticesZ[0] = z;
//
//	for (int i = 1; i < numberOfVertices; i++)
//	{
//		circleVerticesX[i] = x + (radius * cos(i *  twicePi / 360));
//		circleVerticesY[i] = y + (radius * sin(i * twicePi / 360));
//		circleVerticesZ[i] = z;
//	}
//
//	GLfloat allCircleVertices[(361) * 3];
//
//	for (int i = 0; i < numberOfVertices; i++)
//	{
//		allCircleVertices[i * 3] = circleVerticesX[i];
//		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
//		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
//	}
//
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 361);
//	glDisableClientState(GL_VERTEX_ARRAY);
//};

//float vertices[] =
//{
//	300, 300, 0.0, // top right corner
//	0, 300, 0.0, // top left corner
//	0, 0, 0.0, // bottom left corner
//	300, 0, 0.0 // bottom right corner
//};
//
//void drawSQ() {
//	glEnableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
//	glVertexPointer(3, GL_FLOAT, 0, vertices); // point to the vertices to be used
//	glDrawArrays(GL_QUADS, 0, 4); // draw the vertixes
//	glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex arrayattribute
//};

int main(int argc, char* args[]) {
	std::cout << "helloworld!" << std::endl;
	
	int screenWidth = 800;
	int screenHieght = 800;

	//Circle c1;
	AABB sq1;
	Triangle T1;
	Circle c1;
	Position pos1(0, 300);
	Position pos2(800, -600);
	Position pos3(-800, -600);

	Display display(screenWidth, screenHieght, "HelloWorld");

	Shader shader("./res/basicShader");

	while (!display.getIsClosed()) {
		display.fill(.1f, .1f, .1f,1);

		
		c1.DrawCircle(0, 0, 1, 360);
		//sq1.draw();
		//T1.draw(pos1, pos2, pos3, screenHieght, screenWidth);
		shader.Bind();


		display.Update();
	}
	return 0;
}

